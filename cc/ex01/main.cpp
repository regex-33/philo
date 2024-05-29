#include "phonebook.hpp"



void PhoneBook::search(int index)
{
    for (int i = 0; i < this->size; i++)
    {
        if (i == index)
        {
            std::cout << "First Name: " << this->phonebook[i].getFirstName() << std::endl;
            std::cout << "Last Name: " << this->phonebook[i].getLastName() << std::endl;
            std::cout << "Nickname: " << this->phonebook[i].getNickname() << std::endl;
            std::cout << "Number: " << this->phonebook[i].getNumber() << std::endl;
            std::cout << "Secret: " << this->phonebook[i].getSecret() << std::endl;
            std::cout << std::endl;
            std::cout << "Contact found successfully" << std::endl;
        }
    }
}

void printSlashes()
{
    for (int i = 0; i < 65; i++)
        std::cout << "-";
    std::cout << std::endl;
}
void printScudeule()
{
    printSlashes();
    std::cout << std::setw(10) << "Index  " << "|";
    std::cout << std::setw(10) << "First Name" << "|";
    std::cout << std::setw(10) << "Last Name" << "|";
    std::cout << std::setw(10) << "Nickname " << "|";
    std::cout << std::setw(10) << "Number  " << "|";
    std::cout << std::setw(10) << "Secret  " << "|" << std::endl;
    printSlashes();

}

void displayEntry(const std::string& str, size_t width) {
    if (str.length() > width) {
        for (size_t i = 0; i < width - 1; ++i)
            std::cout << str[i];
        std::cout << ".";
    } else
        std::cout << std::setw(width) << std::right << str;
}

void PhoneBook::display() {
    printScudeule();
    for (int i = 0; i < this->size; i++) {
        std::cout << std::setw(10) << i << "|";
        displayEntry(this->phonebook[i].getFirstName(), 10);
        std::cout << "|";
        displayEntry(this->phonebook[i].getLastName(), 10);
        std::cout << "|";
        displayEntry(this->phonebook[i].getNickname(), 10);
        std::cout << "|";
        displayEntry(this->phonebook[i].getNumber(), 10);
        std::cout << "|";
        displayEntry(this->phonebook[i].getSecret(), 10);
        std::cout << "|" << std::endl;
        printSlashes();
    }
}

int checkinput(std::string temp)
{
    int i = 0;

    while (temp[i])
    {
        if (!isdigit(temp[i]))
            return -1;
        i++;
    }
    return std::atoi(temp.c_str());
}

int main(void)
{
    PhoneBook phonebook;
    Contact contact;
    std::string command;
    std::string temp;
    int index;

    while (1)
    {
        std::cout << "Enter command > ";
        std::cin >> command;
        if (command == "EXIT")
        {
            std::cout << "\ngoodbye" << std::endl;
            break;
        }
        else if (command == "ADD")
        {
            std::cout << "Enter first name: ";
            std::cin >> command;
            contact.setFirstName(command);
            std::cout << "Enter last name: ";
            std::cin >> command;
            contact.setLastName(command);
            std::cout << "Enter nickname: ";
            std::cin >> command;
            contact.setNickname(command);
            std::cout << "Enter number: ";
            std::cin >> command;
            contact.setNumber(command);
            std::cout << "Enter secret: ";
            std::cin >> command;
            contact.setSecret(command);
            phonebook.addContact(contact);
            std::cout << "\nContact added successfully\n" << std::endl; 
        }
        else if (command == "SEARCH")
        {
            phonebook.display();
            std::cout << "Enter index: ";
            std::cin >> temp;
            index = checkinput(temp);
            while (index < 0 || index >= phonebook.getSize())
            {
                std::cout << "Invalid index" << std::endl;
                std::cout << "Enter index: ";
                std::cin >> temp;
                index = checkinput(temp);
            }
            std::cout << "\nRequested contact info: " << std::endl;
            phonebook.search(index);
        }
    }
    return 0;
}