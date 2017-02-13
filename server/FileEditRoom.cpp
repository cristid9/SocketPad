#include "FileEditRoom.h"
#include <algorithm>

FileEditRoom::FileEditRoom()
{
}

FileEditRoom::FileEditRoom(std::string flnm, unsigned int fid)
    : filename(flnm), file_id(fid)
{
}

void FileEditRoom::add_contributor(ContributorContainer ctb)
{
    contributors.push_back(ctb);
}

void FileEditRoom::remove_contributor(unsigned int id)
{
    for (auto it = contributors.begin(), end = contributors.end(); it != end; ++it)
    {
        if ((*it).get_id() == id)
        {
            contributors.erase(it);
            break;
        }
    }
}

void FileEditRoom::propaget_change(unsigned int author_id, std::string change)
{
    // Ideally each message should be sent in a different thread
    for (auto ctb : contributors)
    {
        if (ctb.get_id() != author_id)
        {
            ctb.get_sock().send_message(change);
        }
    }
}
