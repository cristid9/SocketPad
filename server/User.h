//
// Created by cristi on 25.01.17.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <vector>
#include <string>
#include <soci/soci.h>

using namespace soci;

class User
{
private:
    std::string username;
    std::string db_path;
    unsigned int id;

public:
    /**
     * @brief Manages the user-related actions
     *
     * @param pth Path to the `SQLite` file.
     * @param username The username of this user.
     */
    User(std::string pth, std::string username);

    /**
     * Inserts a new user in to the database
     *
     * @param username The username of the newly created user
     * @param password The password of the newly created user
     */
    static void create(std::string db_path, std::string username, std::string password);

    /**
     * Retrieves the files created by this user or the files to which
     * this user contributed to.
     *
     * @return A list of file names
     */
    std::vector<std::string> get_files() const;

    /**
     * @brief Checks if the password for this user is right.
     *
     * @param password The candidate password.
     * @param db_path The path to the `SQLite` database.
     * @return true if this is the matching password for this user.
     */
    static bool check_password(std::string db_path, std::string username, std::string password);

    /**
     * @brief Checks if this user exits.
     *
     * @param username The targeted user.
     * @param db_path The path to the `SQLite` database.
     * @return true if it exists
     */
    static bool load(std::string db_path, std::string username);

    /**
     * @brief Retrieved the user's id from the data base.
     *
     * @param db_pth Path to the sqlile file.
     * @param The targeted user.
     * @return The id of the user in the database.
     */
    static unsigned int get_id(std::string db_pth, std::string username);

    /**
     * @brief Getter for the `username` field.
     *
     * @return Returns the `username` stored in the current instance.
     */
    std::string get_username() const;

    /**
     * @brief Getter for the `id` field.
     *
     * @return Returns the `id` of the current instance.
     */
    unsigned int get_id() const;

    /**
     * @brief Gets the username of the user with this id.
     */
    static std::string get_username(std::string db_path, unsigned int id);
};

#endif //SERVER_USER_H
