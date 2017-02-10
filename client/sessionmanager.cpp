#include "sessionmanager.h"
#include "clsock.h"

SessionManager::SessionManager()
{
}

void SessionManager::set_username(std::string usr)
{
    username = usr;
}

std::string SessionManager::get_username() const
{
    return username;
}

