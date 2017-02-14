//
// Created by cristi on 24.01.17.
//

#ifndef SERVER_CNSOCKET_H
#define SERVER_CNSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <netinet/in.h>
#include <iostream>

class CNSocket
{
private:
    struct sockaddr_in sock;
    bool sock_server;
    int sock_descriptor;

    const int max_queue_size  = 50;

public:
    /**
     * Constructor for creating a socket server.
     *
     * @param port Port of the server
     * @param addr Address of the server
     */
    CNSocket(const int port, const long addr);

    /**
     * Build a CNSocket given a `socckaddr_in` structure and a
     * descriptor.
     *
     * @param sock_d The descriptor of the socket that we are about to create
     * @param sa The internal `sockaddr_in` structure
     */
    CNSocket(int sock_d, struct sockaddr_in sa);

    /**
     * @brief No-arguments constructor for `CNSocket`.
     */
    CNSocket();

    /**
     * Wrapper for `listen` sys call.
     */
    void cnlisten() const;

    /**
     * @brief Intended to be used with stl containers.
     */
    CNSocket &operator=(const CNSocket &cns);


    /**
     * High-level wrapper over the accept sys call
     *
     * @return An item from the server's queue
     */
    CNSocket cnaccept() const;

    /**
     * Extracts and returns the relevant value from a packet sent from one of clients
     *
     * @return The content of the message
     */
    std::string get_message() const;

    /**
     * Sends a message to a client. Wrapper method for internal sys calls over write.
     * @param msg The message that should be sent to the user.
     * @return True if the message was sent successfully, false otherwise.
     */
    bool send_message(std::string msg) const;

    /**
     * @brief Closes the socket.
     */
    void finalize();
};


#endif //SERVER_CNSOCKET_H
