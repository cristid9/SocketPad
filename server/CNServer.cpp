#include "CNServer.h"
#include "User.h"
#include "FilesManager.h"
#include "external_dependencies/json.hpp"
#include "File.h"
#include "FileEditRoom.h"
#include <glog/logging.h>
#include <map>
#include <mutex>

// Replace with calls to the Helper
const std::string db_name = "/home/cristi/computer_networks/colaborative_notepad/server/db/cn.sql";

using json = nlohmann::json;

void CNServer::start_server()
{

    CNSocket sock(server_port, server_addr);
    sock.cnlisten();

    while (true)
    {
        CNSocket cnclient = sock.cnaccept();

        std::thread client_thread(&CNServer::client_handler, this, cnclient);
        client_thread.detach();
    }
 }

void CNServer::client_handler(CNSocket cnsock)
{
    LOG(INFO) << "Waiting for a message from a client";

    std::string msg;
    User *session_user = nullptr;

    while (true)
    {
        msg = cnsock.get_message();

        auto client_request = json::parse(msg);

        LOG(INFO) << "[DEBUG CLIENT_HANDLER]" << msg;

        if (client_request["action"].get<std::string>() == "REGISTER")
        {
            std::string username = client_request["username"].get<std::string>();
            LOG(INFO) << "[DEBUG CLIENT_HANDLER]" << username;

            std::string password = client_request["password"].get<std::string>();

            LOG(INFO) << "[DEBUG CLIENT_HANDLER]" << password;

            if (!User::load(db_name, username)) {
                json answer = {{"action", "REGISTER_EXISTS"}};
                cnsock.send_message(answer.dump());
            }
            else
            {
                json answer = {{"action", "REGISTER_OK"}};
                cnsock.send_message(answer.dump());
                User::create(db_name, username, password);
            }
        }
        else if (client_request["action"].get<std::string>() == "LOGIN")
        {
            std::string username = client_request["username"].get<std::string>();
            std::string password = client_request["password"].get<std::string>();

            if (User::check_password(db_name, username, password))
            {
                json answer = { {"action", "LOGIN_OK"} };
                cnsock.send_message(answer.dump());
            }
            else
            {
                json answer = { {"action", "LOGIN_FAIL"} };
                cnsock.send_message(answer.dump());
            }

            session_user = new User(db_name, username);
        }
        else if (client_request["action"].get<std::string>() == "LIST_FILES")
        {

            std::string username = client_request["username"].get<std::string>();

            LOG(INFO) << "[SERVER REQUESTED FILES FOR]"
                      << username;

            std::vector<File> files = File::get_user_files(db_name, username);
            for (auto file : files)
            {
                json answer = {
                        {"action", "FILE_OK"},
                        {"filename",  file.get_name().c_str()},
                        {"author", file.get_author().c_str()}
                };

                answer["fileid"] = file.get_id();

                cnsock.send_message(answer.dump());
                LOG(INFO) << "[SERVER SEND FILE]"
                          << "sending file"
                          << file.get_name();

            }

            json answer = {{"action", "FILES_DONE"}};

            cnsock.send_message(answer.dump());
        }
        else if (client_request["action"].get<std::string>() == "CREATE_FILE") {
            if (FilesManager::check_file_exists(session_user->get_username(),
                                                client_request["filename"].get<std::string>()))
            {
                json answer = {{"action", "FILE_ALREADY_EXISTS"}};
                cnsock.send_message(answer.dump());
            } else {
                std::string pth = FilesManager::create_empty_file(session_user->get_username(),
                                                                  client_request["filename"].get<std::string>());

                FilesManager::update_content(session_user->get_username(),
                                             client_request["filename"].get<std::string>(), " ");

                File::create(db_name, session_user,
                             client_request["filename"].get<std::string>(), pth);

                json answer = {{"action", "FILE_CREATED_OK"}};
                cnsock.send_message(answer.dump());

            }
        }
        else if (client_request["action"].get<std::string>() == "INIT_PEER_EDIT_FILE")
        {
            std::string filename = client_request["filename"].get<std::string>();
            std::string author = client_request["author"].get<std::string>();
            std::string initer = client_request["username"].get<std::string>();
            unsigned int file_id = File::get_id(db_name, filename, author);

            rooms_mtx.lock();
            if (rooms.find(file_id) != rooms.end())
            {
                // return the id of the existing room
                json answer;
                answer["room_id"] = file_id;
                answer["action"] = "ROOM_EXISTS";

                ContributorContainer ctb(User::get_id(db_name, initer), initer, cnsock);

                rooms[file_id].add_contributor(ctb);

                cnsock.send_message(answer.dump());
            }
            else
            {
                // create the room
                ContributorContainer ctb(User::get_id(db_name, initer), initer, cnsock);


                rooms[file_id] = FileEditRoom(filename, file_id);
                rooms[file_id].add_contributor(ctb);

                json answer;
                answer["action"] = "ROOM_CREATED_SUCCESS";
                answer["room_id"] = file_id;

                cnsock.send_message(answer.dump());
            }
            rooms_mtx.unlock();
        }
        else if (client_request["action"].get<std::string>() == "GET_FILE_TEXT")
        {
            std::string author = client_request["author"].get<std::string>();
            std::string filename = client_request["filename"].get<std::string>();

            std::string file_text = FilesManager::load_file_text(author, filename);

            json answer;
            answer["action"] = "FILE_TEXT_RETRIEVED_OK";
            answer["text"] = file_text;

            cnsock.send_message(answer.dump());
        }
        else if (client_request["action"].get<std::string>() == "PEER_NOTIFY_FILE_CHANGE")
        {
            unsigned int file_id = client_request["file_id"].get<int>();
            std::string file_author = File::get_author(db_name, file_id);
            std::string file_name = File::get_filename(db_name, file_id);

            LOG(INFO) << "[ROOM ACCESS] Peer broadcasted change, author "
                      << session_user->get_username()
                      << " targeted file "
                      << file_id;

            client_request["action"] = "PEER_EDIT_PROPAGATION";

            FilesManager::update_content(file_author, file_name,
                                         client_request["new_text"].get<std::string>());

            rooms_mtx.lock();

            rooms[file_id].propagate_change(User::get_id(db_name, client_request["author"].get<std::string>()),
                                            client_request.dump());

            rooms_mtx.unlock();

            // don't forget to write changes on the disk
        }
        else if (client_request["action"].get<std::string>() == "JOIN_ROOM_INTENT")
        {
            LOG(INFO) << "[ROOM ACCESS] detected room join intent";

            unsigned int file_id = client_request["file_id"].get<int>();

            rooms_mtx.lock();

            if (rooms.find(file_id) == rooms.end())
            {
                json answer;
                answer["action"] = "ROOM_DOES_NOT_EXIST";
                cnsock.send_message(answer.dump());
            }
            else
            {
                std::string filename = File::get_filename(db_name, file_id);
                std::string author = File::get_author(db_name, file_id);

                json answer;
                answer["action"] = "ROOM_JOIN_INTENT_OK";
                answer["filename"] = filename;
                answer["author"] = author;

                cnsock.send_message(answer.dump());
            }

            rooms_mtx.unlock();
        }
        else if (client_request["action"].get<std::string>() == "QUIT")
        {

            if (session_user != nullptr)
            {
                LOG(INFO) << "[QUIT] User "
                          << session_user->get_username()
                          << " has quit ";

                rooms_mtx.lock();

                for (auto room : rooms)
                {
                    room.second.remove_contributor(session_user->get_id());
                }

                rooms_mtx.unlock();
            }
            else
            {
                LOG(INFO) << "[QUIT] Random client quit";

            }
            cnsock.finalize();

            return;
        }
    }
}