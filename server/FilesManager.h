//
// Created by cristi on 26.01.17.
//

#ifndef SERVER_FILESMANAGER_H
#define SERVER_FILESMANAGER_H

#include <string>
#include <vector>
#include "User.h"

class FilesManager
{
private:
    /**
     * @brief Initialized with a dummy value. You must call `load_values` before using any other
     *        methods that rely on this member.
     */
    static std::string storage_path;

    /**
     * @brief Helper that checks if the storage dir for this user exists.
     *
     * @param username The user whose storage dir we are targeting.
     * @return `true` if it exists, `false` otherwise.
     */
    static bool check_storage_exists(std::string username);


public:

    FilesManager();

    // move this to file.cpp

    /**
     * @brief Creates the file with `filename` name in the container associated with the
     *        user `username` on the disk.
     * @param username The `name` of the author.
     * @param filename The `name` of the file.
     * @return Returns a string representing the path to this file.
     */
    static std::string create_empty_file(std::string username, std::string filename);

    /**
     * @brief Check if a file is in the user's directory.
     *
     * @param username The targeted user.
     * @param filename The targeted file.
     * @return `true` if it exists or `false` if it doesn't.
     */
    static bool check_file_exists(std::string username, std::string filename);

    /**
     * @brief Creates a directory in the storage location for he specified user.
     *
     * @param username The `username` of the user.
     */
    static void add_user_directory(std::string username);


    /**
     * @brief You'll probably use this after you've loaded the config into a json
     *        object.
     *
     * @param storage_pth The pathe to the storage dir.
     */
    static void load_values(std::string storage_pth);

    /**
     * @brief Load the text of the file with id `id`.
     * @return The text of the targeted file.
     */
    static std::string load_file_text(std::string username, std::string filename);
};


#endif //SERVER_FILESMANAGER_H
