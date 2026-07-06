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
    void showAdminPanel(const std::string &name, const std::string &password) const;

    // User Management
    void banUser(const std::string &adminName) const;
    void unbanUser(const std::string &adminName) const;
    void displayAllUsers() const;

    // Court Management
    void changeCourtStatus() const;
    void displayAllCourts() const;
    void addCourt() const;
    void removeCourt() const;

    // Booking Management
    void displayAdaptiveBookingFilter() const;

    // Helper
    bool isValidCourt(int courtIndex) const;
} obj("Admin", "QWERTY");

#endif