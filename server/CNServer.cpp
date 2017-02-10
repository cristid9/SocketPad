#include "CNServer.h"
#include "User.h"
#include "FilesManager.h"
#include "external_dependencies/json.hpp"
#include <glog/logging.h>

const std::string db_name = "/home/cristi/computer_networks/colaborative_notepad/server/db/cn.sql";

using json = nlohmann::json;

void CNServer::start_server()
{

    CNSocket sock(server_port, server_addr);
    sock.cnlisten();

    while (true)
    {

        FilesManager fmng(db_name);
        User usr(db_name);

        CNSocket cnclient = sock.cnaccept();

        std::thread client_thread(&CNServer::client_handler, this, cnclient, usr, fmng);
        client_thread.detach();
    }
 }

void CNServer::client_handler(CNSocket cnsock, User usr, FilesManager fmng)
{
    LOG(INFO) << "Waiting for a message from a client";

    std::string msg;

    while (true)
    {
        msg = cnsock.get_message();
        LOG(INFO) << "[DEBUG CLIENT_HANDLER]" << msg;

        if (msg == "REGISTER")
        {
            std::string username = cnsock.get_message();
            LOG(INFO) << "[DEBUG CLIENT_HANDLER]" << username;

            cnsock.get_message();
            std::string password = cnsock.get_message();

            LOG(INFO) << "[DEBUG CLIENT_HANDLER]" << password;

            if (!usr.load(username)) {
                cnsock.send_message("REGISTER_EXISTS");
            } else {
                cnsock.send_message("REGISTER_OK");
                usr.create(username, password);
            }
        }
        else if (msg == "LOGIN")
        {
            std::string username = cnsock.get_message();
            cnsock.get_message();
            std::string password = cnsock.get_message();

            if (usr.check_password(username, password))
            {
                cnsock.send_message("LOGIN_OK");
            }
            else
            {
                cnsock.send_message("LOGIN_FAIL");
            }
        }
        else if (msg == "LIST_FILES")
        {

            std::string username = cnsock.get_message();

            LOG(INFO) << "[SERVER REQUESTED FILES FOR]"
                      << username;

            std::vector<std::string> files = fmng.get_user_files(username);
            for (auto file : files)
            {
                cnsock.send_message("FILE_OK");
                cnsock.send_message(file);
                LOG(INFO) << "[SERVER SEND FILE]"
                          << "sending file"
                          << file;

            }
            cnsock.send_message("FILES_DONE");
        }
    }
}