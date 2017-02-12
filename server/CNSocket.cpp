//
// Created by cristi on 24.01.17.
//

#include <cstring>
#include "CNSocket.h"
#include <glog/logging.h>


CNSocket::CNSocket()
{
}

CNSocket::CNSocket(const int port, const long addr)
{
    sock_server = true;

    // creating the socket
    sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_descriptor == -1)
    {
        LOG(ERROR) << "[Sys call failure] Couldn't create socket ";
        std::exit(1);
    }

    int on = 1;
    setsockopt(sock_descriptor, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

    memset(&sock, sizeof(sock), 0);

    sock.sin_family      = AF_INET;
    sock.sin_addr.s_addr = htonl(addr);
    sock.sin_port        = htons(port);

    int bind_result = bind(sock_descriptor, (struct sockaddr *) &sock,
        sizeof (struct sockaddr));

    if (bind_result == -1)
    {
        LOG(ERROR) << "[Sys call failure] failed to bind the socket to a port";
        std::exit(1);
    }
}

void CNSocket::cnlisten() const
{
    // don't forget to throw exception here for sock type

    int listen_result = listen(sock_descriptor, max_queue_size);
    if (listen_result == -1)
    {
        LOG(ERROR) << "[Sys call failure] failed on call to listen";
        std::exit(1);
    }
}

CNSocket::CNSocket(int sock_d, struct sockaddr_in sa)
{
    sock_server = false;
    sock_descriptor = sock_d;
    sock = sa;
}

CNSocket CNSocket::cnaccept() const
{
    // don't forget to throw error here

    struct sockaddr_in from;
    socklen_t length = sizeof(from);
    int from_descriptor = accept(sock_descriptor, (struct sockaddr *) &from, &length);

    if (from_descriptor < 0)
    {
        LOG(ERROR) << "[Sys call failure] Failed to call accept sys call";
        std::exit(1);
    }

    CNSocket item(from_descriptor, from);
    return item;
}

std::string CNSocket::get_message() const
{
    char raw_message_size[11];


    if (read(sock_descriptor, raw_message_size, 10) <= 0)
    {
        LOG(ERROR) << "[Sys call failure] Failed to read size of the message";
        std::exit(1);
    }

    int message_size = atoi(raw_message_size);

    LOG(ERROR) << "[CN_SOCKET GET_MESSGAE]"
              << "length "
              << message_size;

    // move dynamic allocation
    char content[1000];
    if (read(sock_descriptor, content, message_size) < 0)
    {
        LOG(ERROR) << "[Sys call failure] Failed to read the content of the message";
        std::exit(1);
    }

    content[message_size] = '\0';

    std::string converted(content);

    return converted;
}

bool CNSocket::send_message(std::string msg) const
{
    char raw_msg[1000];
    sprintf(raw_msg, "%010d%s", (int)msg.length(), msg.c_str());

    int status = write(sock_descriptor, raw_msg, strlen(raw_msg));

    if (status < 0)
    {
        LOG(ERROR) << "[Sys call failure] Failed on calling the system call write";
        std::exit(1);
    }

    if (status == 0)
        return false;
    return true;
}