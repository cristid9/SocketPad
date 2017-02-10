//
// Created by cristi on 26.01.17.
//

#include "FilesManager.h"
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace soci;

static std::string FilesManager::storage_path = nullptr;

static void FilesManager::load_values(std::string storage_pth)
{
    FilesManager::storage_path = storage_pth;
}

static std::string FilesManager::create_empty_file(std::string username, std::string filename)
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

static bool FilesManager::check_file_exists(std::string username, std::string filename)
{
    std::string candidate_path = storage_path + "/" + username + "/" + filename;

    struct stat st = {0};

    if (stat(candidate_path.c_str(), &st) == -1)
        return false;
    return true;
}

static bool FilesManager::check_storage_exists(std::string username)
{
    std::string candidate_path = storage_path + "/" + username;

    struct stat st = {0};

    if (stat(candidate_path.c_str(), &st) == -1)
        return false;
    return true;
}

static void FilesManager::add_user_directory(std::string username)
{
    std::string candidate_path = storage_path + "/" + username;
    mkdir(candidate_path.c_str(), 0700);
}


FilesManager::FilesManager()
{
}
