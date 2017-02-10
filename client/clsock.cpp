#include "clsock.h"
#include <cstring>
#include <cstdlib>
#include <QDebug>
#include <QtGlobal>

using namespace std;

CLSock::CLSock(int p)
    : port(p)
{}

void CLSock::connect_serv()
{
    sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_descriptor == -1)
    {
        qCritical() << QString("[Sys call failed] error at creating the client sock");
        std::exit(1);
    }

    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = address;
    sock.sin_port = htons(port);

    int connect_status = connect(sock_descriptor, (struct sockaddr *) & sock,
                                 sizeof(struct sockaddr));
    if (connect_status == -1)
    {
        qCritical() << QString("[Sys call failed] failed on calling connect syc call");
        std::exit(1);
    }
}

bool CLSock::write_msg(std::string message)
{
    char raw_msg[1000];
    sprintf(raw_msg, "%010d%s", (int)message.length(), message.c_str());

    std::string a(raw_msg);

    qInfo() << QString(raw_msg) << QString("==") << a.length();

    int status = write(sock_descriptor, raw_msg, strlen(raw_msg));

    if ( status < 0)
    {
        qCritical() << QString("[Sys call failure] Failed on calling the sytem call write");
        std::exit(1);
    }

    if (status == 0)
        return false;
    return true;
}

std::string CLSock::read_msg()
{

    char raw_message_size[11];

    if (read(sock_descriptor, raw_message_size, 10) <= 0)
    {
        qCritical() << QString("[Sys call failure] Failed to read size of the message");
        std::exit(1);
    }

    int message_size = atoi(raw_message_size);

    qInfo()   << QString("[CN_SOCKET GET_MESSGAE]")
              << QString("length ")
              << message_size;

    // move dynamic allocation
    char content[1000];
    if (read(sock_descriptor, content, message_size) < 0)
    {
        qCritical() << QString("[Sys call failure] Failed to read the content of the message");
        std::exit(1);
    }

    content[message_size] = '\0';

    std::string converted(content);

    return converted;
}
