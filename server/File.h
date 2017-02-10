#ifndef SERVER_FILE_H
#define SERVER_FILE_H

#include <string>
#include "User.h"

/**
 * @brief Used to manage data related to a file
 *        inside the server instance.
 */
class File
{
private:
    /* specify file attributes here */
    std::string file_path;
    std::string file_name;

    /* find a way to keep track of links to the contributors... */
    /* how the hell am I going to do that */

public:
    /**
     * @brief Constructor for the `File` class.
     *
     * @param pth The path to the db file
     */
    File(std::string pth);

    /**
     * @brief Creates a new file (i.e. inserts a new record in the db)
     *
     * @param user The creator of this file
     * @param filename The name of this file
     * @return The in-app model of the just created entry.
     */
    static File& create(std::string db_path, User user, std::string filename);

    /**
     * @brief Loads the file created by the user `user` and with the name
     *        `filename`.
     * @param user The user who created this file.
     * @param filename The `name` of this file.
     * @return A `File` instance populated with the attributes related to the
     *         targeted file.
     */
    static File& load(std::string db_path, User user, std::string filename);

    /**
     * @brief Loads the file identified by the id `file_id`.
     *
     * @param file_id The `id` of this file.
     * @return A `File` instance populated with the attributes related to the
     *         targeted file.
     */
    static File& load(std::string db_path, unsigned int file_id);


    /**
     * @brief Loads the list with the user's files.
     *
     * @param username The targeted user.
     * @return A container with the file names created or edited by this user.
     */
    static std::vector<std::string> get_user_files(std::string db_path, std::string username);
};


#endif //SERVER_FILE_H
