#include "phonebook.hpp"


Contact::Contact()
{
    this->first_name = "";
    this->last_name = "";
    this->nickname = "";
    this->number = "";
    this->secret = "";
}

PhoneBook::PhoneBook()
{
    int i = 0;

    while (i < 8)
    {
        this->phonebook[i] = Contact();
        i++;
    }
    this->size = 0;
}

