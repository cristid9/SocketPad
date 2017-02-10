#include "File.h"
#include <soci/sqlite3/soci-sqlite3.h>

using namespace soci;

static File& File::create(std::string db_path, User user, std::string filename)
{
    session sql(sqlite3, "dbname=" + db_path);

    // insert an entry in to the database and, then, use the filesmanager to
    // create an empty file on the disk. I think it should be in reverse oorder


    // throw some exception here

}

static File& File::load(std::string db_path, User user, std::string filename)
{
    // same as above
}

static File& File::load(std::string db_path, unsigned int file_id)
{
    // same as above
}
