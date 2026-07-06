#include "../headers/admin.hpp"
#include "utilities.cpp"

// -------------------- Authentication --------------------
Admin::Admin(const std::string adminName, const std::string password)
    : adminName(adminName), adminPassword(password) {}

bool Admin::authenticate(const std::string &name, const std::string &password) const
{
    if(name != adminName)   return false;
    return password == adminPassword;
}

// -------------------- Users --------------------
void Admin::banUser(const std::string &userName) const
{
    if (users.find(userName) == users.end())
    {
        std::cout << "User not found!" << std::endl;
        return;
    }
    users[userName].switchStatus(BANNED);
    std::cout << "User '" << userName << "' has been BANNED." << std::endl;
}

void Admin::unbanUser(const std::string &userName) const
{
    if (users.find(userName) == users.end())
    {
        std::cout << "User not found!" << std::endl;
        return;
    }
    users[userName].switchStatus(AUTHORIZED);
    std::cout << "User '" << userName << "' has been UNBANNED." << std::endl;
}

void Admin::displayAllUsers() const
{
    std::cout << "============================== ALL USERS ==============================" << std::endl;
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;

    if (users.empty())
    {
        std::cout << "No users found." << std::endl;
        return;
    }

    int i = 0;
    for (auto &user : users)
        std::cout << std::setw(3) << ++i << ") " << user.second << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;
    return;
}

// -------------------- Courts --------------------
bool Admin::isValidCourt(int courtIndex) const
{   return courtIndex >= 0 && courtIndex < (int)courts.size(); }

void Admin::changeCourtStatus() const
{
    std::cout << std::endl;
    std::cout << "Select court index to change status (or 0 to go back): ";

    int courtIndex = takeInput();
    std::cout << std::endl;

    if (! courtIndex--)
        return;

    if (!isValidCourt(courtIndex))
    {
        std::cout << "Invalid court index!" << std::endl;
        return;
    }

    std::cout << "-------------------- Select an Option --------------------" <<std::endl;
    std::cout << std::endl;
    std::cout << "[1] Set AVAILABLE" << std::endl;
    std::cout << "[2] Set RESERVED" << std::endl;
    std::cout << "[3] Set MAINTAINANCE" << std::endl;
    std::cout << "[0] back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter choice: ";

    courtStatus newStatus;
    int statusChoice = takeInput();

    switch (statusChoice)
    {
    case 0:
        return;

    case 1:
        newStatus = AVAILABLE;
        break;

    case 2:
        newStatus = RESERVED;
        break;

    case 3:
        newStatus = MAINTAINANCE;
        break;

    default:
        std::cout << std::endl << "Invalid choice !";
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    courts[courtIndex] -> switchStatus(newStatus);
    std::cout << std::endl << "Court '" << courts[courtIndex] -> getCourtName() << "' status changed to " << newStatus << ".";
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
    return;
}

void Admin::displayAllCourts() const
{
    std::cout << "================================== ALL COURTS ==================================" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

    if (courts.empty())
    {
        std::cout << "No courts found !" << std::endl;
        return;
    }

    for (int i = 0; i < (int)courts.size(); i++)
        std::cout << std::setw(3) << i + 1 << ") " << *courts[i] << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    return;
}

void Admin::addCourt() const
{
    std::cout << std::endl;
    std::cout << "================= ADD NEW COURT =================" << std::endl;
    std::cout << "Court Types:" << std::endl;
    std::cout << "  [1] Badminton Court" << std::endl;
    std::cout << "  [2] Basketball Court" << std::endl;
    std::cout << "  [3] Volleyball Court" << std::endl;
    std::cout << "  [4] Football Ground" << std::endl;
    std::cout << "  [5] Cricket Ground" << std::endl;
    std::cout << "  [0] back" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::cout << "Select court type: ";
    int courtType = takeInput();

    if(! courtType)
        return;

    std::string courtTypeName;
    switch (courtType)
    {
    case 1:
        courtTypeName = "Badminton Court";
        break;
    case 2:
        courtTypeName = "Basketball Court";
        break;
    case 3:
        courtTypeName = "Volleyball Court";
        break;
    case 4:
        courtTypeName = "Football Ground";
        break;
    case 5:
        courtTypeName = "Cricket Ground";
        break;
    default:
        std::cout << "Invalid court type!" << std::endl;
        return;
    }

    std::cout << "Enter choice for new court number: ";
    int courtNumber = takeInput();

    if (courtNumber <= 0)
    {
        std::cout << "Court number must be positive!" << std::endl;
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    // Check for duplicate court
    for (const auto &court : courts)
    {
        if (court -> getCourtName() != courtTypeName + " " + std::to_string(courtNumber))
            continue;

        std::cout << std::endl;
        std::cout << "ERROR: Court with same type and number already exists!" << std::endl;
        std::cout << "Court: " << courtTypeName << " " << courtNumber << std::endl;
        return;
    }

    Court *newCourt = NULL;

    switch (courtType)
    {
    case 1:
        newCourt = new Badminton(courtNumber, AVAILABLE);
        break;
    case 2:
        newCourt = new Basketball(courtNumber, AVAILABLE);
        break;
    case 3:
        newCourt = new Volleyball(courtNumber, AVAILABLE);
        break;
    case 4:
        newCourt = new Football(courtNumber, AVAILABLE);
        break;
    case 5:
        newCourt = new Cricket(courtNumber, AVAILABLE);
        break;
    }

    if (! newCourt)
        return;

    courts.push_back(newCourt);
    std::sort(courts.begin(), courts.end(), [](Court *x, Court *y) { return x -> getCourtName() < y -> getCourtName(); });

    std::cout << std::endl << "New court added successfully !";
    std::cout << std::endl << "Court: " << *newCourt;
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void Admin::removeCourt() const
{
    if(! courts.size())
        return;

    std::cout << std::endl;
    std::cout << "Enter court index to remove (or 0 to go back): ";
    int removeIndex = takeInput();

    if (! removeIndex--)
        return;

    if (! isValidCourt(removeIndex))
    {
        std::cout << "Invalid court index!" << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "Court to be removed:" << std::endl;
    std::cout << std::setw(3) << removeIndex + 1 << ") " << *courts[removeIndex] << std::endl;
    std::cout << std::endl;

    const auto &bookingsMap = courts[removeIndex] -> getBookings();
    int bookingCount = 0;

    for (const auto &dateEntry : bookingsMap)
    {
        for (const auto &hourEntry : dateEntry.second)
        {
            if (hourEntry.second.isBooked())
                bookingCount++;
        }
    }

    if (bookingCount)
    {
        std::cout << "WARNING: This court has " << bookingCount << " active booking(s)!" << std::endl;
        std::cout << "Deleting this court will remove all associated bookings." << std::endl;
    }

    std::string confirm;
    std::cout << "Type 'yes' to confirm deletion: ";
    std::cin >> confirm;

    if (confirm != "yes")
    {
        std::cout << "Deletion Aborted." << std::endl;
        return;
    }

    delete courts[removeIndex];
    courts.erase(courts.begin() + removeIndex);
    std::cout << std::endl << "Court removed !";
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// -------------------- Booking Management --------------------
void Admin::displayAdaptiveBookingFilter() const
{
    std::string filterUser = "";
    int filterCourt = -1;
    std::string filterDate = "";

    while (true)
    {
        clear();

        std::cout << "=================================================== FILTERED BOOKINGS ===================================================" << std::endl;
        std::cout << std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;

        int bookingCount = 0;
        for (int i = 0; i < (int)courts.size(); i++)
        {
            const std::map<std::string, std::map<int, TimeSlot>> &bookingsMap = courts[i] -> getBookings();
            for (const std::pair<std::string, std::map<int, TimeSlot>> &dateEntry : bookingsMap)
            {
                for (const std::pair<int, TimeSlot> &hourEntry : dateEntry.second)
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
                                << "Court: " << std::setw(20) << courts[i] -> getCourtName() << "\t | "
                                << "Date & Time: " << hourEntry.second.toString() << "\t | "
                                << "Booked by: " << hourEntry.second.bookedBy << std::endl;
                }
            }
        }

        if (! bookingCount)
            std::cout << "No bookings matches applied filters." << std::endl;

        std::cout << "-------------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << "========== ADAPTIVE BOOKING DATA FILTER ==========" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Active Filters:" << std::endl;

        if (! filterUser.empty())
            std::cout << "  -> User: " << filterUser << std::endl;
        if (filterCourt != -1)
            std::cout << "  -> Court: " << courts[filterCourt]->getCourtName() << std::endl;
        if (! filterDate.empty())
            std::cout << "  -> Date: " << filterDate << std::endl;
        if (filterUser.empty() && filterCourt == -1 && filterDate.empty())
            std::cout << "  (No filters applied - showing all bookings)" << std::endl;

        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "  [1] Add/Change User Filter:" << std::endl;
        std::cout << "  [2] Add/Change Court Filter:" << std::endl;
        std::cout << "  [3] Add/Change Date Filter:" << std::endl;
        std::cout << "  [4] Clear All Filters:" << std::endl;
        std::cout << "  [0] Back:" << std::endl;
        std::cout << std::endl;

        std::cout << "Select Filter Option: ";
        int choice = takeInput();
        std::cout << std::endl;


        if (! choice)
            break;

        switch (choice)
        {
        case 1:
        {
            displayAllUsers();
            std::string tempUser;
            std::cout << "Enter username (or 0 to disable filter): ";
            std::cin >> tempUser;

            if (tempUser == "0")
            {
                filterUser = "";
                std::cout << std::endl << "User filter disabled.";
            }
            else if (users.count(tempUser))
            {
                filterUser = tempUser;
                std::cout << std::endl << "User filter set to: " << filterUser;
            }
            else
            {
                std::cout << std::endl << "User not found!";
            }
            break;
        }

        case 2:
        {
            displayAllCourts();
            std::cout << "Enter court index (or 0 to disable filter): ";
            int tempCourt = takeInput();

            if (! tempCourt--)
            {
                filterCourt = -1;
                std::cout << std::endl << "Court filter disabled.";
            }
            else if (isValidCourt(tempCourt))
            {
                filterCourt = tempCourt;
                std::cout << std::endl << "Court filter set to: " << courts[filterCourt] -> getCourtName();
            }
            else
            {
                std::cout << std::endl << "Invalid court index!";
            }
            break;
        }

        case 3:
        {
            std::string tempDate;
            std::cout << "Enter booking date in YYYY-MM-DD format (or 0 to disable filter): ";
            std::cin >> tempDate;

            if (tempDate == "0")
            {
                filterDate = "";
                std::cout << std::endl << "Date filter disabled.";
            }
            else if(validateDate(tempDate))
            {
                filterDate = tempDate;
                std::cout << std::endl << "Date filter set to: " << filterDate;
            }
            else
            {
                std::cout << std::endl << "Invalid date format!";
            }
            break;
        }

        case 4:
        {
            filterUser = "";
            filterCourt = -1;
            filterDate = "";
            std::cout << std::endl << "All filters cleared.";
            break;
        }

        default:
            std::cout << "Invalid option !" << std::endl;
            break;
        }

        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}

// -------------------- Admin Panel --------------------
void Admin::showAdminPanel(const std::string &name, const std::string &password) const
{
    if (adminName != name || adminPassword != password)
    {
        std::cout << std::endl << "Authentication failed!";
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    clear();
    std::cout << "Successfully Logged In as Admin!" << std::endl;

    while (true)
    {
        std::cout << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << "                    ADMIN PANEL                   " << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << std::endl;
        std::cout << "  [1] Manage Users:" << std::endl;
        std::cout << "  [2] Manage Courts:" << std::endl;
        std::cout << "  [3] View & Filter Bookings:" << std::endl;
        std::cout << "  [0] Logout:" << std::endl;
        std::cout << std::endl;

        std::cout << "Select an Option: ";
        int task = takeInput();
        if (! task)  break;

        switch (task)
        {
        case 1:
        {
            while (true)
            {
                clear();
                displayAllUsers();

                std::cout << std::endl;
                std::cout << "  [1] Ban User:" << std::endl;
                std::cout << "  [2] Unban User:" << std::endl;
                std::cout << "  [0] Go Back:" << std::endl;
                std::cout << std::endl;

                std::cout << "Select an option: ";
                int userTask = takeInput();
                std::cout << std::endl;

                if (! userTask)
                    break;

                if (userTask != 1 && userTask != 2)
                {
                    std::cout << "Invalid option!" << std::endl;
                    std::cout << std::endl << "Press Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    continue;
                }

                std::string userName;
                std::cout << "Enter userName: ";
                std::cin >> userName;
                std::cout << std::endl;

                if (userTask == 1)
                    banUser(userName);
                else
                    unbanUser(userName);
            }
            break;
        }

        case 2:
        {
            while (true)
            {
                clear();
                displayAllCourts();

                std::cout << std::endl;
                std::cout << "====== COURT MANAGEMENT ======" << std::endl;
                std::cout << "----------------------------------------------------" << std::endl;
                std::cout << "  [1] to Change Court Status:" << std::endl;
                std::cout << "  [2] to Add New Court:" << std::endl;
                std::cout << "  [3] to Remove Court:" << std::endl;
                std::cout << "  [0] to Go Back:" << std::endl;
                std::cout << std::endl;

                std::cout << "Select an Option: ";
                int choice = takeInput();

                if (! choice)
                    break;

                switch (choice)
                {
                case 1:
                    changeCourtStatus();
                    break;
                case 2:
                    addCourt();
                    break;
                case 3:
                    removeCourt();
                    break;
                default:
                    std::cout << "Invalid option !" << std::endl;
                    std::cout << std::endl << "Press Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }
            }
            break;
        }

        case 3:
        {
            displayAdaptiveBookingFilter();
            break;
        }

        default:
            std::cout << std::endl << "Enter valid option !";
            std::cout << std::endl << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        clear();
    }

    std::cout << std::endl << "Successfully Logged Out from Admin !";
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
    return;
}