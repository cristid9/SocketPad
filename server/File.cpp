#include "File.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <glog/logging.h>

using namespace soci;

File::File()
{
}

File::File(std::string db_pth)
{
}

File::File(std::string db_pth, std::string vfile_path, std::string vfile_name, unsigned int vid)
    : db_path(db_pth), file_path(vfile_path), file_name(vfile_name), file_id(vid)
{
    author = get_author_username();
}

std::string File::get_author_username() const
{
    session sql(sqlite3, "dbname=" + db_path);

    unsigned int creator_id;

    sql << "SELECT creator_id FROM File WHERE id=:file_id",
        use(file_id), into(creator_id);

    return User::get_username(db_path, creator_id);
}

File File::create(std::string db_path, User *user, std::string filename, std::string path)
{
    session sql(sqlite3, "dbname=" + db_path);

    sql << "INSERT INTO File (name, path, creator_id) VALUES (:name, :path, :creator_id)",
            use(filename), use(path), use(user->get_id());

    LOG(INFO) << "[DB ACCESS] Inserted new file in the database";

    // replace later
    File fl("dummy");
    return fl;
}

File& File::load(std::string db_path, User user, std::string filename)
{
    // same as above
}

File& File::load(std::string db_path, unsigned int file_id)
{
    // same as above
}


std::vector<File> File::get_user_files(std::string db_path, std::string username)
{
    session sql(sqlite3, "dbname=" + db_path);

    unsigned int id = User:: get_id(db_path, username);

    std::vector<File> files;

    soci::rowset<soci::row> files_list = (
            sql.prepare << "SELECT path, name, id FROM File WHERE creator_id=" << id);

    for (soci::rowset<soci::row>::iterator it = files_list.begin(); it != files_list.end(); ++it)
    {
        std::string pth, name;
        unsigned int id;

        pth = (*it).get<std::string>(0);
        name = (*it).get<std::string>(1);
        id = (*it).get<int>(2);

        File f(db_path, pth, name, id);

        files.push_back(f);
    }

    LOG(INFO)  << "[DB ACCESS]"
               << " Retrieved list of created files for the user "
               << username;

    return files;
}

unsigned int File::get_id() const
{
    return file_id;
}

std::string File::get_name() const
{
    return file_name;
}

std::string File::get_path() const
{
    return file_path;
}

unsigned int File::get_id(std::string db_path, std::string filename, std::string author)
{
    session sql(sqlite3, "dbname=" + db_path);

    unsigned int user_id = User::get_id(db_path, author);

    unsigned int id;

    sql << "SELECT id FROM File WHERE name=:name AND creator_id=:user_id",
        use(filename), use(user_id), into(id);

    LOG(INFO) << "[DB ACCESS] Retrived id for file "
              << filename;

    return id;
}

std::string File::get_author() const
{
    return author;
}

std::string File::get_filename(std::string db_path, unsigned int id)
{
    session sql(sqlite3, "dbname=" + db_path);

    std::string filename;
    sql << "SELECT name FROM File WHERE id=:id",
        use(id), into(filename);

    return filename;
}

std::string File::get_author(std::string db_path, unsigned int id)
{
    session sql(sqlite3, "dbname=" + db_path);

    std::string author;

    unsigned int author_id;

    sql << "SELECT creator_id FROM File WHERE id=:id",
        use(id), into(author_id);

    author = User::get_username(db_path, author_id);

    return author;
}