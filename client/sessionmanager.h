#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "clsock.h"

using namespace std;

class SessionManager
{
private:
    std::string username;
    unsigned int user_id;

public:

    /**
     * @brief SessionManager Constructor for the session manager. It is the internal daa structure
     *        used to maintain the logic of the application.
     */
    SessionManager();

    /**
     * @brief set_username Setter
     * @param username the userrname loggedin in the current session
     */
    void set_username(std::string username);

    /**
     * @brief get_username Getter for username
     * @return returns he username logged in in the current session
     */
    std::string get_username() const;

 };

#endif // SESSIONMANAGER_H
