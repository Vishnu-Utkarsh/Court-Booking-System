#ifndef USER
#define USER

#include "Template.hpp"

class User
{
private:
    bool busy;
    std::string username, password;

public:
    // constructor
    User();
    User(const std::string &name, const std::string &pass);
    User(const std::string &name, const std::string &pass, const bool status);

    // getters
    std::string getUsername();
    std::string getPassword();
    bool getStatus();

    // authentication
    bool checkPassword(const std::string &password);

    // switch status
    void switchStatus();

    // save file
    string saveFile();

    // output operator (<<)
    friend std::ostream &operator<<(std::ostream &os, const User &user)
    {
        os << "username: " << user.username << "\t\t";
        os << "status: " << (user.busy ? "Booked" : "Not Booked") << "\t\t";
        return os;
    }
};

// forward declaration
User::User() {}
User::User (const std::string &name, const std::string &pass) : username(name), password(pass), busy(false) {}
User::User (const std::string &name, const std::string &pass, const bool status) : username(name), password(pass), busy(status) {}

std::string User::getUsername() { return username; }
std::string User::getPassword() { return password; }
bool User::getStatus() { return busy; }

bool User::checkPassword(const std::string &password) { return password == this -> password; }

void User::switchStatus() { busy ^= true; }


void _print(User &user)
    {   cerr << user.getUsername() << " : " << user.getPassword() << " - " << boolalpha << user.getStatus(); }
void print(User user)
    {   cout << user << endl; }

#endif