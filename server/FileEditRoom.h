#ifndef SERVER_FILEEDITROOM_H
#define SERVER_FILEEDITROOM_H

#include <vector>
#include <utility>
#include <string>
#include "ContributorContainer.h"

class FileEditRoom
{
private:
    /**
     * @brief Container of contributors.
     */
    std::vector<ContributorContainer> contributors;

    /**
     * @brief The of the `filename`.
     */
    std::string filename;

    /**
     * @brief The `id` of the edited file.
     */
    unsigned int file_id;
public:

    /**
     * @param flnm `name` of the edited file.
     * @param fid `id` of the edited file
     */
    FileEditRoom(std::string flnm, unsigned int fid);

    /**
     * @brief No arguments constructor.
     */
    FileEditRoom();

    /**
     * @brief Setter for the `contributors` field.
     *
     * @param ctb A new contributor.
     */
    void add_contributor(ContributorContainer ctb);

    /**
     * @brief Removes a contributor from this room.
     *
     * @param id The `id` of the targeted contributor.
     */
    void remove_contributor(unsigned int id);

    /**
     * brief Propagates a change made by 1 contributor to the others.
     *
     * @param author_id Author of the change.
     * @param change Serialized json contining the
     */
    void propaget_change(unsigned int author_id, std::string change);
};


#endif //SERVER_FILEEDITROOM_H
