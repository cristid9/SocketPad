#include "filechange.h"

FileChange::FileChange(unsigned int vpos, char vtarget, ChangeType vtype)
    : pos(vpos), target(vtarget), type(vtype)
{
}

unsigned int FileChange::get_pos() const
{
    return pos;
}

ChangeType FileChange::get_type() const
{
    return type;
}

char FileChange::get_target() const
{
    return target;
}

FileChange FileChange::detect_change(std::string str1, std::string str2)
{
    if (str1.size() == str2.size())
    {
        // replace

        int target_idx;

        for (std::string::size_type idx1 = 0, idx2 = 0; idx1 < str1.size() && idx2 < str2.size(); ++idx1, ++idx2)
        {
            if (str1[idx1] != str2[idx2])
            {
                target_idx = idx1;
                break;
            }
        }

        FileChange fl_change(target_idx, str1[target_idx], ChangeType::FILE_CHANGE_REPLACE);

        return fl_change;
    }
    else if (str1.size() < str2.size())
    {
        // insert

        int target_idx = str1.size();

        for (std::string::size_type idx1 = 0, idx2 = 0; idx1 < str1.size() && idx2 < str2.size(); ++idx1, ++idx2)
        {
            if (str1[idx1] != str2[idx2])
            {
                target_idx = idx1;
                break;
            }
        }

        FileChange fl_change(target_idx, str2[target_idx], ChangeType::FILE_CHANGE_INSERT);
        return fl_change;
    }
    else
    {
        // delete

        int target_idx = str2.size();

        for (std::string::size_type idx1 = 0, idx2 = 0; idx1 < str1.size() && idx2 < str2.size(); ++idx1, ++idx2)
        {
            if (str1[idx1] != str2[idx2])
            {
                target_idx = idx1;
                break;
            }
        }

        FileChange fl_change(target_idx, str1[target_idx], ChangeType::FILE_CHANGE_DELETE);
        return fl_change;
    }
}
