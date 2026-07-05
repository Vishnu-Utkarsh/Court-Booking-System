#ifndef USER_HPP
#define USER_HPP

#include "storage.hpp"

// User Status
enum userStatus
{   AUTHORIZED, BANNED };
std::ostream &operator<<(std::ostream &os, userStatus currState)
{
    switch (currState)
    {
    case userStatus::AUTHORIZED:    os << "AUTHORIZED"; break;
    case userStatus::BANNED:        os << "BANNED";     break;
    default:    os << "UNKNOWN";    break;
    }
    return os;
}

class User
{
private:
    userStatus currState;
    std::string username, password;

    // Account Settings
    void changePassword();

    // Booking
    void showBookings() const;
    void book() const;
    void cancelBooking() const;

public:
    // constructor
    User();
    User(const std::string &name, const std::string &pass);
    User(const std::string &name, const std::string &pass, const userStatus newState);

    // authentication & Login
    void Login(const std::string &password);

    // switch userStatus
    void switchStatus(const userStatus newStatus);

    // save file
    std::string saveFile();

    // output operator (<<)
    friend std::ostream &operator<<(std::ostream &os, const User &user)
    {
        os << "username: " << std::setw(20) << user.username << "\t\t";
        os << "userStatus: " << user.currState << "\t\t";
        return os;
    }
};

#endif