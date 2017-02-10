#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "clsock.h"

class UserManager
{
private:

public:
    /**
     * @brief UserManager Class that manages user activity in the application
     * @param clsock
     */
    UserManager();

    /**
     * @brief register_user Method called when a new user should be created.
     * @param username The username of the newly created user.
     * @param password The password of the newly created user.
     * @return False if the user already exists, true otherwise.
     */
    bool register_user(std::string username, std::string password);

    /**
     * @brief login_user Queris the server for the correctness of the
     *        username, password tuple.
     * @param username The candidate username
     * @param password The password for this username
     * @return True if the username exists and matches the password.
     */
    bool login_user(std::string username, std::string password);
};

#endif // USERMANAGER_H
