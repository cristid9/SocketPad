#include "FilesManager.h"
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <glog/logging.h>

using namespace soci;

std::string FilesManager::storage_path = "";

void FilesManager::load_values(std::string storage_pth)
{
    FilesManager::storage_path = storage_pth;
}

std::string FilesManager::load_file_text(std::string username, std::string filename)
{
    std::string path = storage_path + "/" + username + "/" + filename;

    std::ifstream in_file(path);
    std::stringstream str_stream;

    str_stream << in_file.rdbuf();
    std::string text = str_stream.str();

    LOG(INFO) << "[STORAGE ACCESS] Loaded text for the file "
              << path;

    return text;
}

std::string FilesManager::create_empty_file(std::string username, std::string filename)
{

    std::string file_path = storage_path + "/" + username + "/" + filename;

    if (!FilesManager::check_storage_exists(username))
    {
        FilesManager::add_user_directory(username);
    }

    if (!FilesManager::check_file_exists(username, filename))
    {
        creat(file_path.c_str(), 0700);
    }

    return file_path;
}

bool FilesManager::check_file_exists(std::string username, std::string filename)
{
    std::string candidate_path = storage_path + "/" + username + "/" + filename;

    struct stat st = {0};

    if (stat(candidate_path.c_str(), &st) == -1)
        return false;
    return true;
}

bool FilesManager::check_storage_exists(std::string username)
{
    std::string candidate_path = storage_path + "/" + username;

    struct stat st = {0};

    if (stat(candidate_path.c_str(), &st) == -1)
        return false;
    return true;
}

void FilesManager::add_user_directory(std::string username)
{
    std::string candidate_path = storage_path + "/" + username;
    mkdir(candidate_path.c_str(), 0700);
}

void FilesManager::update_content(std::string username, std::string filename, std::string value)
{
    std::string path = storage_path + "/" + username + "/" + filename;

    std::ofstream inFile(path);

    inFile << value;

    inFile.close();
}

FilesManager::FilesManager()
{
}
