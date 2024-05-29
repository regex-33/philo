#include "phonebook.hpp"

std::string Contact::getFirstName()
{
    return this->first_name;
}
std::string Contact::getLastName()
{
    return this->last_name;
}

std::string Contact::getNickname()
{
    return this->nickname;
}

std::string Contact::getNumber()
{
    return this->number;
}

std::string Contact::getSecret()
{
    return this->secret;
}

int PhoneBook::getSize()
{
    return this->size;
}