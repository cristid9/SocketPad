#ifndef CLSOCK_H
#define CLSOCK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <netinet/in.h>
#include <string>
#include <iostream>

using namespace std;

class CLSock
{
private:
    int port;
    long address = inet_addr("127.0.0.1");
    struct sockaddr_in sock;
    int sock_descriptor;

public:
    /**
     * @brief CLSock Wrapper for bsd-socket interface.
     *        Because of speed-related (of coding) reasons,
     *        the address of the server is hardcoded in this
     *        class
     *
     * @param port The port of the connection
     */
    CLSock(int port);

    /**
     * @brief connect The actual method that connects to the server socket.
     */
    void connect_serv();

    /**
     * @brief write_msg Wrapper method over the calls issued to `write` sys calls
     *       that we usually do when comunicatting with server.
     * @param message The message that should be sent to the server.
     * @return If the message was sent sucessfully `true` is returned.
     */
    bool write_msg(std::string message);

    /**
     * @brief read_msg Wrapper of the series of `read` syscalls performed when reading a message
     *        from a server.
     * @return The readed message.
     */
    std::string read_msg();
};

#endif CLSOCK_H
