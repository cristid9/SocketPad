#include "usermanager.h"
#include <QDebug>
#include "global_objs.h"

UserManager::UserManager()
{}

bool UserManager::register_user(string username, string password)
{
    clsock.write_msg("REGISTER");
    clsock.write_msg(username);
    clsock.write_msg("PASSWORD");
    clsock.write_msg(password);

    std::string msg = clsock.read_msg();
    if (msg == "REGISTER_OK")
    {
        qInfo() << QString("[USER MANAGER]")
                << QString("user registered succesfully");

        return true;
    }
    else if (msg == "REGISTER_EXISTS" )
    {
        qInfo() << QString("[USER MANAGER]")
                << QString("username exists, badluck");
    }

    return false;
}

bool UserManager::login_user(string username, string password)
{
    clsock.write_msg("LOGIN");
    clsock.write_msg(username);
    clsock.write_msg("PASSWORD");
    clsock.write_msg(password);

    std::string msg = clsock.read_msg();
    if (msg == "LOGIN_OK")
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
