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
    unsigned int file_id;

    /* find a way to keep track of links to the contributors... */
    /* how the hell am I going to do that */

public:
    /**
     * @brief Constructor for the `File` class.
     *
     * @param pth The path to the db file
     */
    File(std::string db_pth);

    /**
     * @brief No arguments constructor.
     */
    File();

    /**
     * @brief Use this container when you want this class to act as a container for those 3 fields.
     *
     * @param file_path Path to the file.
     * @param file_name Name of the file.
     * @param id Id of the file in db.
     */
    File(std::string file_path, std::string file_name, unsigned int id);

    /**
     * @brief Creates a new file (i.e. inserts a new record in the db)
     *
     * @param user The creator of this file
     * @param filename The name of this file
     * @param path The path to this file in the internal storage.
     *
     * @return The in-app model of the just created entry.
     */
    static File create(std::string db_path, User *user, std::string filename, std::string path);

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
    static std::vector<File> get_user_files(std::string db_path, std::string username);

    /**
     * @brief Getter for the `file_path` field.
     * @return Path to this file.
     */
    std::string get_path() const;

    /**
     * @brief Getter for `name` field.
     * @return Name of this file.
     */
    std::string get_name() const;

    /**
     * @brief Getter `id` field.
     * @return Id of this file.
     */
    unsigned int get_id() const;
};


#endif //SERVER_FILE_H
