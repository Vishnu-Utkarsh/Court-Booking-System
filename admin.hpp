#ifndef ADMIN
#define ADMIN

#include "Template.hpp"
#include "storage.hpp"

class Admin
{
private:
    std::string adminUsername;
    std::string adminPassword;

public:
    Admin(const std::string adminName, const std::string password);

    bool authenticate(const std::string &name, const std::string &password) const;
    void showAdminPanel(const std::string &password);

    // User Management
    void banUser(const std::string &adminName);
    void unbanUser(const std::string &adminName);
    void displayAllUsers();

    // Court Management
    void changeCourtStatus(int courtIndex, courtStatus newStatus);
    void displayAllCourts();

    // Booking Management
    void displayAdaptiveBookingFilter();

    // Helper
    bool isValidCourt(int courtIndex) const;
} obj("Admin", "QWERTY");

// Implementation
Admin::Admin(const std::string adminName, const std::string password)
    : adminUsername(adminName), adminPassword(password) {}

bool Admin::authenticate(const std::string &name, const std::string &password) const
{
    if(name != adminUsername)   return false;
    return password == adminPassword;
}

bool Admin::isValidCourt(int courtIndex) const
{
    return courtIndex >= 0 && courtIndex < (int)courts.size();
}

void Admin::banUser(const std::string &adminName)
{
    if (users.find(adminName) == users.end())
    {
        std::cout << "User not found!" << std::endl;
        return;
    }
    users[adminName].switchStatus(BANNED);
    std::cout << "User '" << adminName << "' has been BANNED." << std::endl;
}

void Admin::unbanUser(const std::string &adminName)
{
    if (users.find(adminName) == users.end())
    {
        std::cout << "User not found!" << std::endl;
        return;
    }
    users[adminName].switchStatus(AUTHORIZED);
    std::cout << "User '" << adminName << "' has been UNBANNED." << std::endl;
}

void Admin::displayAllUsers()
{
    std::cout << std::endl;
    std::cout << "====== ALL USERS ======" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    if (users.empty())
    {
        std::cout << "No users found." << std::endl;
        return;
    }

    int i = 1;
    for (auto &user : users)
        std::cout << std::setw(3) << i++ << ") " << user.second << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
}

void Admin::changeCourtStatus(int courtIndex, courtStatus newStatus)
{
    if (!isValidCourt(courtIndex))
    {
        std::cout << "Invalid court index!" << std::endl;
        return;
    }

    courts[courtIndex] -> switchStatus(newStatus);
    std::cout << "Court '" << courts[courtIndex] -> getCourtName() << "' status changed to " << newStatus << "." << std::endl;
}

void Admin::displayAllCourts()
{
    std::cout << std::endl;
    std::cout << "====== ALL COURTS ======" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    if (courts.empty())
    {
        std::cout << "No courts found." << std::endl;
        return;
    }

    for (int i = 0; i < (int)courts.size(); i++)
        std::cout << std::setw(3) << i << ") " << *courts[i] << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
}

void Admin::displayAdaptiveBookingFilter()
{
    std::string filterUser = "";
    int filterCourt = -1;
    std::string filterDate = "";

    while (true)
    {
        cout << std::endl;
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif

        std::cout << std::endl;
        std::cout << "====== ADAPTIVE BOOKING FILTER ======" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Active Filters:" << std::endl;
        if (!filterUser.empty())
            std::cout << "  ✓ User: " << filterUser << std::endl;
        if (filterCourt != -1)
            std::cout << "  ✓ Court: " << courts[filterCourt]->getCourtName() << std::endl;
        if (!filterDate.empty())
            std::cout << "  ✓ Date: " << filterDate << std::endl;
        if (filterUser.empty() && filterCourt == -1 && filterDate.empty())
            std::cout << "  (No filters applied - showing all bookings)" << std::endl;

        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Enter 1 to Add/Change User Filter" << std::endl;
        std::cout << "Enter 2 to Add/Change Court Filter" << std::endl;
        std::cout << "Enter 3 to Add/Change Date Filter" << std::endl;
        std::cout << "Enter 4 to View Filtered Bookings" << std::endl;
        std::cout << "Enter 5 to Clear All Filters" << std::endl;
        std::cout << "Enter 0 to Go Back" << std::endl;
        std::cout << std::endl;

        int choice;
        cin >> choice;

        if (! choice)
            break;

        switch (choice)
        {
        case 1:
        {
            std::cout << std::endl;
            displayAllUsers();
            std::string tempUser;
            std::cout << "Enter username (or 0 to disable filter): ";
            cin >> tempUser;

            if (tempUser == "0")
            {
                filterUser = "";
                std::cout << "User filter disabled." << std::endl;
            }
            else if (users.count(tempUser))
            {
                filterUser = tempUser;
                std::cout << "User filter set to: " << filterUser << std::endl;
            }
            else
            {
                std::cout << "User not found!" << std::endl;
            }
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 2:
        {
            std::cout << std::endl;
            displayAllCourts();
            int tempCourt;
            std::cout << "Enter court index (or -1 to disable filter): ";
            cin >> tempCourt;

            if (tempCourt == -1)
            {
                filterCourt = -1;
                std::cout << "Court filter disabled." << std::endl;
            }
            else if (isValidCourt(tempCourt))
            {
                filterCourt = tempCourt;
                std::cout << "Court filter set to: " << courts[filterCourt]->getCourtName() << std::endl;
            }
            else
            {
                std::cout << "Invalid court index!" << std::endl;
            }
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 3:
        {
            std::cout << std::endl;
            std::string tempDate;
            std::cout << "Enter booking date in YYYY-MM-DD format (or 0 to disable filter): ";
            cin >> tempDate;

            if (tempDate == "0")
            {
                filterDate = "";
                std::cout << "Date filter disabled." << std::endl;
            }
            else if(validateDate(tempDate))
            {
                filterDate = tempDate;
                std::cout << "Date filter set to: " << filterDate << std::endl;
            }
            else
            {
                std::cout << "Invalid date format!" << std::endl;
            }
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 4:
        {
            std::cout << std::endl;
            std::cout << "====== FILTERED BOOKINGS ======" << std::endl;
            std::cout << "----------------------------------------------------" << std::endl;

            int bookingCount = 0;
            for (int i = 0; i < (int)courts.size(); i++)
            {
                const auto &bookingsMap = courts[i]->getBookings();
                for (const auto &dateEntry : bookingsMap)
                {
                    for (const auto &hourEntry : dateEntry.second)
                    {
                        if (!hourEntry.second.isBooked())
                            continue;

                        bool matchesFilter = true;

                        if (! filterUser.empty() && hourEntry.second.bookedBy != filterUser)
                            matchesFilter = false;

                        if (filterCourt != -1 && i != filterCourt)
                            matchesFilter = false;

                        if (! filterDate.empty() && dateEntry.first != filterDate)
                            matchesFilter = false;

                        if (! matchesFilter)
                            continue;

                        bookingCount++;
                        std::cout << std::setw(3) << bookingCount << ") "
                                    << "Court: " << courts[i] -> getCourtName() << " | "
                                    << "Date & Time: " << hourEntry.second.toString() << " | "
                                    << "User: " << hourEntry.second.bookedBy << std::endl;
                    }
                }
            }

            if (! bookingCount)
                std::cout << "No bookings match the applied filters." << std::endl;

            std::cout << "----------------------------------------------------" << std::endl;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 5:
        {
            filterUser = "";
            filterCourt = -1;
            filterDate = "";
            std::cout << std::endl;
            std::cout << "All filters cleared." << std::endl;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            break;
        }

        default:
        {
            std::cout << "Invalid option!" << std::endl;
            break;
        }
        }
    }
}

void Admin::showAdminPanel(const std::string &password)
{
    if (adminPassword != password)
    {
        std::cout << "Authentication failed!" << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "Successfully Logged In as Admin!" << std::endl;
    std::cerr << std::endl << "----- Admin Logged In -----" << std::endl;
    int task = 0;

    while (true)
    {
        cout << std::endl;
        #ifdef _WIN32
            std::system("cls"); // For Windows
        #else
            // Assume POSIX (Linux, macOS, etc.)
            std::system("clear");
        #endif

        std::cout << std::endl;
        std::cout << "====== ADMIN PANEL ======" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Enter 1 to Manage Users (Ban/Unban):" << std::endl;
        std::cout << "Enter 2 to Manage Court Status:" << std::endl;
        std::cout << "Enter 3 to View & Filter Bookings:" << std::endl;
        std::cout << "Enter 0 to Logout:" << std::endl;
        std::cout << std::endl;

        cin >> task;
        if (!task)  break;

        switch (task)
        {
        case 1:
        {
            while (true)
            {
                std::cout << std::endl;
                displayAllUsers();
                std::cout << std::endl;
                std::cout << "Enter 1 to Ban User:" << std::endl;
                std::cout << "Enter 2 to Unban User:" << std::endl;
                std::cout << "Enter 0 to Go Back:" << std::endl;

                int userTask;
                cin >> userTask;

                if (! userTask)
                    break;

                if (userTask == 1 || userTask == 2)
                {
                    std::string adminName;
                    std::cout << "Enter adminName: ";
                    cin >> adminName;

                    if (userTask == 1)
                        banUser(adminName);
                    else
                        unbanUser(adminName);
                }
                else
                {
                    std::cout << "Invalid option!" << std::endl;
                }
            }
            break;
        }

        case 2:
        {
            while (true)
            {
                std::cout << std::endl;
                displayAllCourts();
                std::cout << std::endl;
                std::cout << "Enter court index to change status (or -1 to go back): ";

                int courtIdx;
                cin >> courtIdx;

                if (courtIdx == -1)
                    break;

                if (!isValidCourt(courtIdx))
                {
                    std::cout << "Invalid court index!" << std::endl;
                    continue;
                }

                std::cout << std::endl;
                std::cout << "Enter 1 to set AVAILABLE:" << std::endl;
                std::cout << "Enter 2 to set MAINTENANCE:" << std::endl;
                std::cout << "Enter choice: ";

                int statusChoice;
                cin >> statusChoice;

                if (statusChoice == 1)
                    changeCourtStatus(courtIdx, AVAILABLE);
                else if (statusChoice == 2)
                    changeCourtStatus(courtIdx, MAINTAINANCE);
                else
                    std::cout << "Invalid choice!" << std::endl;
            }
            break;
        }

        case 3:
        {
            displayAdaptiveBookingFilter();
            break;
        }

        default:
            std::cout << "Enter valid operation!" << std::endl;
            break;
        }
    }

    std::cout << "Successfully Logged Out from Admin Panel!" << std::endl;
    std::cerr << std::endl << "----- Admin Logged Out -----" << std::endl;
}

#endif