#include "File.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <glog/logging.h>

using namespace soci;

File& File::create(std::string db_path, User user, std::string filename)
{
    session sql(sqlite3, "dbname=" + db_path);

    // insert an entry in to the database and, then, use the filesmanager to
    // create an empty file on the disk. I think it should be in reverse oorder


    // throw some exception here

}

File& File::load(std::string db_path, User user, std::string filename)
{
    // same as above
}

File& File::load(std::string db_path, unsigned int file_id)
{
    // same as above
}


std::vector<std::string> File::get_user_files(std::string db_path, std::string username)
{
    session sql(sqlite3, "dbname=" + db_path);

    unsigned int id = User:: get_id(db_path, username);

    std::vector<std::string> files_list(100);

    sql << "SELECT name FROM File WHERE creator_id=:id",
        use(id), into(files_list);

    LOG(INFO)  << "[DB ACCESS]"
               << " Retrieved list of created files for the user "
               << username;

    return files_list;
}