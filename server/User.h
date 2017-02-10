//
// Created by cristi on 25.01.17.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <vector>
#include <string>
#include <soci/soci.h>

using namespace soci;
using namespace std;

class User
{
private:
    std::string username;
    std::string db_path;

public:
    User(std::string pth);

    /**
     * Inserts a new user in to the database
     *
     * @param username The username of the newly created user
     * @param password The password of the newly created user
     */
    void create(std::string username, std::string password);

    /**
     * Retrieves the files created by this user or the files to which
     * this user contributed to.
     *
     * @return A list of file names
     */
    std::vector<std::string> get_files() const;

    /**
     * Checks if the password for this user is right.
     *
     * @param password The candidate password.
     * @return true if this is the matching password for this user.
     */
    bool check_password(std::string username, std::string password) const;

    /**
     * Checks if this user exits.
     *
     * @param username
     * @return true if it exists
     */
    bool load(std::string username);
};

#endif //SERVER_USER_H
