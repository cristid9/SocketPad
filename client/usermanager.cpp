#include "usermanager.h"
#include <QDebug>
#include "global_objs.h"
#include "json.hpp"

using json = nlohmann::json;

UserManager::UserManager()
{}

bool UserManager::register_user(string username, string password)
{
    json client_request = {
        {"action", "REGISTER"},
        {"username", username.c_str()},
        {"password", password.c_str()}
    };

    clsock.write_msg(client_request.dump());

    std::string msg = clsock.read_msg();

    auto answer = json::parse(msg);

    if (answer["action"].get<std::string>() == "REGISTER_OK")
    {
        qInfo() << QString("[USER MANAGER]")
                << QString("user registered succesfully");

        return true;
    }
    else if (answer["action"].get<std::string>() == "REGISTER_EXISTS" )
    {
        qInfo() << QString("[USER MANAGER]")
                << QString("username exists, badluck");
    }

    return false;
}

bool UserManager::login_user(string username, string password)
{

    json client_request;
    client_request["action"] = "LOGIN";
    client_request["username"] = username;
    client_request["password"] = password;

    clsock.write_msg(client_request.dump());

    std::string msg = clsock.read_msg();
    auto server_answer = json::parse(msg);

    if (server_answer["action"].get<std::string>() == "LOGIN_OK")
    {
        qInfo() << QString("[USER MANAGER]")
                << QString("user logged in succesfully");

        return true;
    }
    else
    {
        qInfo()  << QString("[USER MANAGER]")
                 << QString("user or password wrong");

    }
    return false;
}
