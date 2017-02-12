#include "CNServer.h"
#include "User.h"
#include "FilesManager.h"
#include "external_dependencies/json.hpp"
#include "File.h"
#include <glog/logging.h>

// Replace with calls to the Helper
const std::string db_name = "/home/cristi/computer_networks/colaborative_notepad/server/db/cn.sql";

using json = nlohmann::json;

void CNServer::start_server()
{

    CNSocket sock(server_port, server_addr);
    sock.cnlisten();

    while (true)
    {

        User usr(db_name);

        CNSocket cnclient = sock.cnaccept();

        std::thread client_thread(&CNServer::client_handler, this, cnclient, usr);
        client_thread.detach();
    }
 }

void CNServer::client_handler(CNSocket cnsock, User usr)
{
    LOG(INFO) << "Waiting for a message from a client";

    std::string msg;

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

            if (!usr.load(username)) {
                json answer = {{"action", "REGISTER_EXISTS"}};
                cnsock.send_message(answer.dump());
            }
            else
            {
                json answer = {{"action", "REGISTER_OK"}};
                cnsock.send_message(answer.dump());
                usr.create(username, password);
            }
        }
        else if (client_request["action"].get<std::string>() == "LOGIN")
        {
            std::string username = client_request["username"].get<std::string>();
            std::string password = client_request["password"].get<std::string>();

            if (usr.check_password(username, password))
            {
                json answer = { {"action", "LOGIN_OK"} };
                cnsock.send_message(answer.dump());
            }
            else
            {
                json answer = { {"action", "LOGIN_FAIL"} };
                cnsock.send_message(answer.dump());
            }
        }
        else if (client_request["action"].get<std::string>() == "LIST_FILES")
        {

            std::string username = client_request["username"].get<std::string>();

            LOG(INFO) << "[SERVER REQUESTED FILES FOR]"
                      << username;

            std::vector<std::string> files = File::get_user_files(db_name, username);
            for (auto file : files)
            {
                json answer = {
                        {"action", "FILE_OK"},
                        {"item", file.c_str()}
                };

                cnsock.send_message(answer.dump());
                LOG(INFO) << "[SERVER SEND FILE]"
                          << "sending file"
                          << file;

            }

            json answer = {{"action", "FILES_DONE"}};

            cnsock.send_message(answer.dump());
        }
    }
}