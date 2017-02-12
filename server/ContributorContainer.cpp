#include "ContributorContainer.h"

ContributorContainer::ContributorContainer(unsigned int cid, std::string cusername, CNSocket csock)
    : id(cid), username(cusername), sock(csock)
{
}

unsigned int ContributorContainer::get_id() const
{
    return id;
}

std::string ContributorContainer::get_username() const
{
    return username;
}

CNSocket ContributorContainer::get_sock() const
{
    return sock;
}