#include "filesmanager.h"
#include "clsock.h"
#include <QDebug>
#include "global_objs.h"
#include "json.hpp"

using json = nlohmann::json;

FilesManager::FilesManager()
{
}

std::vector<std::string> FilesManager::get_user_files(string username)
{

    json request = {
        {"action", "LIST_FILES"},
        {"username", username.c_str()}
    };

    clsock.write_msg(request.dump());

    std::vector<std::string> files;

    std::string msg;

    while (true)
    {
        msg = clsock.read_msg();

        auto server_answer = json::parse(msg);

        if (server_answer["action"].get<std::string>() == "FILE_OK")
        {
            qDebug() << "[FILES MANAGER RETRIEVER]"
                     << "We got yet another ";

        }
        else if (server_answer["action"].get<std::string>() == "FILES_DONE")
        {
            break;
        }
        std::string file_name = server_answer["filename"].get<std::string>();
        std::string author = server_answer["author"].get<std::string>();

        std::string new_file = author + "/" + file_name;

        qDebug() << "[FILES MANAGER RETRIEVER]"
                 << "We got file with name ";

        files.push_back(new_file);
    }

    return files;
}

std::string FilesManager::load_file(std::string username, std::string filename)
{
    json request;
    request["action"] = "GET_FILE_TEXT";
    request["filename"] = filename;
    request["author"] = username;

    clsock.write_msg(request.dump());

    json answer = json::parse(clsock.read_msg());

    if (answer["action"].get<std::string>() == "FILE_TEXT_RETRIEVED_OK")
    {
        return answer["text"].get<std::string>();
    }

    return "";
}

bool FilesManager::create_new_file(std::string filename)
{
    json request = {
        {"action", "CREATE_FILE"},
        {"filename", filename.c_str()}
    };

    clsock.write_msg(request.dump());

    json answer = json::parse(clsock.read_msg());

    if (answer["action"].get<std::string>() == "FILE_CREATED_OK")
    {
        // here you should reload the list box with the file names

        return true;
    }

    return false;
}
