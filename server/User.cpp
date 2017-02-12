//
// Created by cristi on 25.01.17.
//

#include <soci/sqlite3/soci-sqlite3.h>
#include <iostream>
#include "User.h"
#include <glog/logging.h>

using namespace soci;

User::User(std::string db_p, std::string usrnm)
    : db_path(db_p), username(usrnm)
{
    id = User::get_id(db_path, username);
}

void User::create(std::string db_path, std::string username, std::string password)
{
    session sql(sqlite3, "dbname=" + db_path);


    sql << "insert into USER(username, password) values(:username, :password)",
        use(username), use(password);
}

bool User::load(std::string db_path, std::string username)
{
    session sql(sqlite3, "dbname=" + db_path);

    int count;
    sql << "select count(username) from User where username=:username",
        use(username), into(count);

    LOG(INFO) << "[USER QUERY] check existence of "
              << username
              << " got result "
              << count;

    if (count == 0)
        return true;
    return false;
}

bool User::check_password(std::string db_path, std::string username, std::string password)
{
    session sql(sqlite3, "dbname=" + db_path);

    std::string q_password;
    sql << "select password from User where username=:username",
        use(username), into(q_password);

    LOG(INFO) << "[USER CHECK PASSWD]"
              << " check "
              << password
              << " got result "
              << q_password;

    if (q_password == password)
    {
        return true;
    }
    return false;
}

unsigned int User::get_id(std::string db_pth, std::string username)
{
    session sql(sqlite3, "dbname=" + db_pth);

    unsigned int id;

    sql << "SELECT id FROM user WHERE username=:username",
        use(username), into(id);

    LOG(INFO) << "[DB ACCESS]"
              << " Retrieved id for "
              << username
              << " with value "
              << id;
    return id;
}

std::string User::get_username() const
{
    return username;
}

unsigned int User::get_id() const
{
    return id;
}