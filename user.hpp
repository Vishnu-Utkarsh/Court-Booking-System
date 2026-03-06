#ifndef USER
#define USER

#include "Template.hpp"

// User Status
enum userStatus
{   FREE, BOOKED, BANNED };

std::ostream& operator<<(std::ostream& os, userStatus currState)
{
    switch (currState)
    {
        case userStatus::FREE:      os << "FREE";       break;
        case userStatus::BOOKED:    os << "BOOKED";     break;
        case userStatus::BANNED:    os << "BANNED";     break;
        default:                    os << "UNKNOWN";    break;
    }
    return os;
}

class User
{
private:
    userStatus currState;
    std::string username, password;

public:
    // constructor
    User();
    User(const std::string &name, const std::string &pass);
    User(const std::string &name, const std::string &pass, const userStatus newState);

    // getters
    std::string getUsername();
    std::string getPassword();
    userStatus getStatus();

    // authentication
    bool checkPassword(const std::string &password);
    void Login(const std::string &password);

    // switch userStatus
    void switchStatus(const userStatus newStatus);

    // save file
    string saveFile();

    // output operator (<<)
    friend std::ostream &operator<<(std::ostream &os, const User &user)
    {
        os << "username: " << user.username << "\t\t";
        os << "userStatus: " << user.currState << "\t\t";
        return os;
    }
};

// forward declaration
User::User() {}
User::User (const std::string &name, const std::string &pass) : username(name), password(pass), currState(FREE) {}
User::User (const std::string &name, const std::string &pass, const userStatus newState) : username(name), password(pass), currState(newState) {}

std::string User::getUsername() { return username; }
std::string User::getPassword() { return password; }
userStatus User::getStatus() { return currState; }

bool User::checkPassword(const std::string &password) { return password == this -> password; }

void User::switchStatus(const userStatus newStatus) { currState = newStatus; }


void _print(User &user)
    {   cerr << user.getUsername() << " : " << user.getPassword() << " - " << boolalpha << user.getStatus(); }
void print(User user)
    {   cout << user << endl; }

#endif