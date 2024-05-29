#ifndef phonebook_h
#define phonebook_h

#include <iostream>
#include <string>
#include <iomanip>




class Contact {
private:
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string number;
    std::string secret;
public:
    Contact();
    void setFirstName(std::string first_name);
    void setLastName(std::string last_name);
    void setNickname(std::string nickname);
    void setNumber(std::string number);
    void setSecret(std::string secret);
    std::string getFirstName();
    std::string getLastName();
    std::string getNickname();
    std::string getNumber();
    std::string getSecret();
};

class PhoneBook {
private:
    Contact phonebook[8];
    int size;
public:
    PhoneBook();
    void addContact(Contact contact);
    void search(int  index);
    int getSize();
    void display();
};

void   setFirstName(std::string first_name);
void   setLastName(std::string last_name);
void   setNickname(std::string nickname);
void   setNumber(std::string number);
void   setSecret(std::string secret);

std::string getFirstName();
std::string getLastName();
std::string getNickname();
std::string getNumber();
std::string getSecret();

void    display();
int getSize();
#endif