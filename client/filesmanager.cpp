#include "filesmanager.h"
#include "clsock.h"
#include <QDebug>
#include "global_objs.h"

FilesManager::FilesManager()
{
}

std::vector<std::string> FilesManager::get_user_files(string username)
{
    clsock.write_msg("LIST_FILES");
    clsock.write_msg(username);

    std::vector<std::string> files;

    std::string msg;

    while (true)
    {
        msg = clsock.read_msg();
        if (msg == "FILE_OK")
        {
            qDebug() << "[FILES MANAGER RETRIEVER]"
                     << "We got yet another ";

        }
        else if (msg == "FILES_DONE")
        {
            break;
        }
        std::string file_name = clsock.read_msg();

        qDebug() << "[FILES MANAGER RETRIEVER]"
                 << "We got file with name ";

        files.push_back(file_name);
    }

    return files;
}
