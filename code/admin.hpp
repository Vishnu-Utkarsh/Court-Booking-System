#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "storage.hpp"

class Admin
{
private:
    std::string adminName;
    std::string adminPassword;

public:
    Admin(const std::string adminName, const std::string password);

    bool authenticate(const std::string &name, const std::string &password) const;
    void showAdminPanel(const std::string &name, const std::string &password);

    // User Management
    void banUser(const std::string &adminName);
    void unbanUser(const std::string &adminName);
    void displayAllUsers();

    // Court Management
    void changeCourtStatus();
    void displayAllCourts();
    void addCourt();
    void removeCourt();

    // Booking Management
    void displayAdaptiveBookingFilter();

    // Helper
    bool isValidCourt(int courtIndex) const;
} obj("Admin", "QWERTY");

// Implementation
Admin::Admin(const std::string adminName, const std::string password)
    : adminName(adminName), adminPassword(password) {}

bool Admin::authenticate(const std::string &name, const std::string &password) const
{
    if(name != adminName)   return false;
    return password == adminPassword;
}

#endif