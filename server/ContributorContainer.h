
#ifndef SERVER_CONTRIBUTORCONTAINER_H
#define SERVER_CONTRIBUTORCONTAINER_H

#include "CNSocket.h"
#include <string>

class ContributorContainer
{
private:
    unsigned int id;
    std::string username;
    CNSocket sock;
public:

    /**
     * @param cid The `id` of the newly created contributor.
     * @param cusername The `username` of the newly created username.
     * @param csock Socket to the clinet opened by this contributor.
     */
    ContributorContainer(unsigned int cid, std::string cusername, CNSocket csock);

    /**
     * @brief No arguments container.
     */
    ContributorContainer();

    /**
     * @brief Getter for the `id` field.
     * @return The `id` of this contributor.
     */
    unsigned int get_id() const;

    /**
     * @brief Getter for `username` field.
     * @return The `username` of this contributor.
     */
    std::string get_username() const;

    /**
     * @brief Getter for `sock` field.
     * @return The socket connected to this user's client.
     */
    CNSocket get_sock() const;
};


#endif //SERVER_CONTRIBUTORCONTAINER_H
