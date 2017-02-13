//
// Created by cristi on 24.01.17.
//

#ifndef SERVER_CNSERVER_H
#define SERVER_CNSERVER_H

#include <thread>
#include <netinet/in.h>
#include "CNSocket.h"
#include "User.h"
#include "FilesManager.h"
#include "FileEditRoom.h"
#include <map>

class CNServer {
private:
    static const int server_port = 3131;
    static const long server_addr = INADDR_ANY;

    void client_handler(CNSocket cnsock, std::map<unsigned int, FileEditRoom>);

public:

    void start_server();
};


#endif //SERVER_CNSERVER_H
