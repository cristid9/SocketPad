//
// Created by cristi on 25.01.17.
//

#include <soci/sqlite3/soci-sqlite3.h>
#include <iostream>
#include "User.h"
#include <glog/logging.h>

using namespace soci;

User::User(std::string db_p)
    : db_path(db_p)
{
}

void User::create(std::string username, std::string password)
{
    session sql(sqlite3, "dbname=" + db_path);


    sql << "insert into USER(username, password) values(:username, :password)",
        use(username), use(password);
}

bool User::load(std::string username)
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

bool User::check_password(std::string username, std::string password) const
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


