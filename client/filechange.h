#ifndef FILECHANGE_H
#define FILECHANGE_H

#include <string>

enum ChangeType {
    FILE_CHANGE_INSERT,
    FILE_CHANGE_DELETE,
    FILE_CHANGE_REPLACE
};

/**
 * @brief Used to model a change by the user. A user can insert, delete or replace a character.
 */
class FileChange
{
private:
    unsigned int pos;
    char target;
    ChangeType type;

public:
    FileChange(unsigned int vpos, char vtarget, ChangeType vtype);

    /**
     * @brief Getter for `pos`.
     */
    unsigned int get_pos() const;

    /**
     * @brief Getter for `target`.
     */
    char get_target() const;

    /**
     * @brief Getter for `type`.
     */
    ChangeType get_type() const;

    /**
     * @brief Call this after the `textChanged` event, to get the change that the
     *        current user added.
     * @param str1 The text before the previous edit.
     * @param str2 The text after the user did the change.
     * @return
     */
    static FileChange detect_change(std::string str1, std::string str2);
};

#endif // FILECHANGE_H
