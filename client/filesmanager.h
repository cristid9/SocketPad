#ifndef FILESMANAGER_H
#define FILESMANAGER_H

#include <vector>
#include "clsock.h"

class FilesManager
{
private:
//    CLSock clsock;

public:
    /**
     * @brief FilesManager Handles the logics of action related to file operations
     *        like retreveing files for an user from the server for an user.
     */
    FilesManager();

    /**
     * @brief get_user_files Retrieves the list of file names associated to an user.
     * @param username The username of the use whose files we want
     * @return a vector of file names.
     */
    std::vector<std::string> get_user_files(std::string username);
};

#endif // FILESMANAGER_H
