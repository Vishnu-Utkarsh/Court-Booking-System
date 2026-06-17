#include "admin.hpp"

// -------------------- Utilities --------------------
inline bool validateDate(const std::string &date)
{
    std::istringstream ss(date);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return !ss.fail();
}

// -------------------- Users --------------------
void Admin::banUser(const std::string &userName)
{
    if (users.find(userName) == users.end())
    {
        std::cout << "User not found!" << std::endl;
        return;
    }
    users[userName].switchStatus(BANNED);
    std::cout << "User '" << userName << "' has been BANNED." << std::endl;
}

void Admin::unbanUser(const std::string &userName)
{
    if (users.find(userName) == users.end())
    {
        std::cout << "User not found!" << std::endl;
        return;
    }
    users[userName].switchStatus(AUTHORIZED);
    std::cout << "User '" << userName << "' has been UNBANNED." << std::endl;
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
    return;
}

// -------------------- Courts --------------------

bool Admin::isValidCourt(int courtIndex) const
{   return courtIndex >= 0 && courtIndex < (int)courts.size(); }

void Admin::changeCourtStatus()
{
    std::cout << std::endl;
    std::cout << "Enter court index to change status (or 0 to go back): ";

    int courtIndex;
    std::cin >> courtIndex;
    std::cout << std::endl;

    if (! courtIndex--)
        return;

    if (!isValidCourt(courtIndex))
    {
        std::cout << "Invalid court index!" << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "Enter 0 to go back" << std::endl;
    std::cout << "Enter 1 to set AVAILABLE" << std::endl;
    std::cout << "Enter 2 to set RESERVED" << std::endl;
    std::cout << "Enter 3 to set MAINTAINANCE" << std::endl;
    std::cout << "Enter choice: ";

    int statusChoice;
    courtStatus newStatus;
    std::cin >> statusChoice;
    std::cout << std::endl;

    switch (statusChoice)
    {
    case 0:
        break;

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
        std::cout << "Invalid choice!" << std::endl;
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
        std::cout << std::setw(3) << i + 1 << ") " << *courts[i] << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    return;
}

void Admin::addCourt()
{
    std::cout << std::endl;
    std::cout << "====== ADD NEW COURT ======" << std::endl;
    std::cout << "Court Types:" << std::endl;
    std::cout << "  1) Badminton Court" << std::endl;
    std::cout << "  2) Basketball Court" << std::endl;
    std::cout << "  3) Volleyball Court" << std::endl;
    std::cout << "  4) Football Ground" << std::endl;
    std::cout << "  5) Cricket Ground" << std::endl;
    std::cout << "  Enter 0 to go back" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    int courtType;
    std::cout << "Select court type (1-5): ";
    std::cin >> courtType;

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

    int courtNumber;
    std::cout << "Enter court number: ";
    std::cin >> courtNumber;

    if (courtNumber <= 0)
    {
        std::cout << "Court number must be positive!" << std::endl;
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
    std::cout << std::endl;
    std::cout << "New court added successfully!" << std::endl;
    std::cout << "Court: " << *newCourt << std::endl;
    std::sort(courts.begin(), courts.end(), [](Court *x, Court *y) { return x -> getCourtName() < y -> getCourtName(); });
}

void Admin::removeCourt()
{
    if(! courts.size())
        return;

    std::cout << std::endl;
    int removeIndex;
    std::cout << "Enter court index to remove (or 0 to go back): ";
    std::cin >> removeIndex;

    if (! removeIndex--)
        return;

    if (!isValidCourt(removeIndex))
    {
        std::cout << "Invalid court index!" << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "Court to be removed:" << std::endl;
    std::cout << std::setw(3) << removeIndex + 1 << ") " << *courts[removeIndex] << std::endl;
    std::cout << std::endl;

    const auto &bookingsMap = courts[removeIndex]->getBookings();
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
    std::cout << std::endl;
    std::cout << "Court removed !" << std::endl;
}

// -------------------- Booking Management --------------------
void Admin::displayAdaptiveBookingFilter()
{
    std::string filterUser = "";
    int filterCourt = -1;
    std::string filterDate = "";

    while (true)
    {
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif

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

        std::cout << std::endl;
        std::cout << "====== ADAPTIVE BOOKING INFORMATION FILTER ======" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Active Filters:" << std::endl;
        if (!filterUser.empty())
            std::cout << "  -> User: " << filterUser << std::endl;
        if (filterCourt != -1)
            std::cout << "  -> Court: " << courts[filterCourt]->getCourtName() << std::endl;
        if (!filterDate.empty())
            std::cout << "  -> Date: " << filterDate << std::endl;
        if (filterUser.empty() && filterCourt == -1 && filterDate.empty())
            std::cout << "  (No filters applied - showing all bookings)" << std::endl;

        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Enter 1 to Add/Change User Filter:" << std::endl;
        std::cout << "Enter 2 to Add/Change Court Filter:" << std::endl;
        std::cout << "Enter 3 to Add/Change Date Filter:" << std::endl;
        std::cout << "Enter 4 to Clear All Filters:" << std::endl;
        std::cout << "Enter 0 to Go Back:" << std::endl;
        std::cout << std::endl;

        int choice;
        std::cin >> choice;
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
            std::cout << std::endl;

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
            displayAllCourts();
            int tempCourt;
            std::cout << "Enter court index (or 0 to disable filter): ";
            std::cin >> tempCourt;
            std::cout << std::endl;

            if (! tempCourt--)
            {
                filterCourt = -1;
                std::cout << "Court filter disabled." << std::endl;
            }
            else if (isValidCourt(tempCourt))
            {
                filterCourt = tempCourt;
                std::cout << "Court filter set to: " << courts[filterCourt] -> getCourtName() << std::endl;
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
            std::string tempDate;
            std::cout << "Enter booking date in YYYY-MM-DD format (or 0 to disable filter): ";
            std::cin >> tempDate;
            std::cout << std::endl;

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
            std::cout << "Invalid option!" << std::endl;
            break;
        }
    }
}

// -------------------- Admin Panel --------------------
void Admin::showAdminPanel(const std::string &password)
{
    if (adminPassword != password)
    {
        std::cout << std::endl << "Authentication failed!";
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << std::endl;
    std::cout << "Successfully Logged In as Admin!" << std::endl;
    int task = 0;

    while (true)
    {
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif

        std::cout << std::endl;
        std::cout << "====== ADMIN PANEL ======" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Enter 1 to Manage Users:" << std::endl;
        std::cout << "Enter 2 to Manage Courts:" << std::endl;
        std::cout << "Enter 3 to View & Filter Bookings:" << std::endl;
        std::cout << "Enter 0 to Logout:" << std::endl;
        std::cout << std::endl;

        std::cin >> task;
        if (! task)  break;

        switch (task)
        {
        case 1:
        {
            while (true)
            {
                #ifdef _WIN32
                    std::system("cls");
                #else
                    std::system("clear");
                #endif

                displayAllUsers();
                std::cout << std::endl;
                std::cout << "Enter 1 to Ban User:" << std::endl;
                std::cout << "Enter 2 to Unban User:" << std::endl;
                std::cout << "Enter 0 to Go Back:" << std::endl;

                int userTask;
                std::cin >> userTask;
                std::cout << std::endl;

                if (! userTask)
                    break;

                if (userTask != 1 && userTask != 2)
                    std::cout << "Invalid option!" << std::endl;
                else
                {
                    std::string userName;
                    std::cout << "Enter userName: ";
                    std::cin >> userName;
                    std::cout << std::endl;

                    if (userTask == 1)
                        banUser(userName);
                    else
                        unbanUser(userName);
                }
            }
            break;
        }

        case 2:
        {
            while (true)
            {
                #ifdef _WIN32
                    std::system("cls");
                #else
                    std::system("clear");
                #endif

                displayAllCourts();

                std::cout << std::endl;
                std::cout << "====== COURT MANAGEMENT ======" << std::endl;
                std::cout << "----------------------------------------------------" << std::endl;
                std::cout << "Enter 1 to Change Court Status:" << std::endl;
                std::cout << "Enter 2 to Add New Court:" << std::endl;
                std::cout << "Enter 3 to Remove Court:" << std::endl;
                std::cout << "Enter 0 to Go Back:" << std::endl;
                std::cout << std::endl;

                int choice;
                std::cin >> choice;

                if (! choice)
                    break;

                switch (choice)
                {
                case 1:
                {
                    changeCourtStatus();
                    std::cout << "Press Enter to continue..." << std::endl;
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }

                case 2:
                {
                    addCourt();
                    std::cout << "Press Enter to continue..." << std::endl;
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }

                case 3:
                {
                    removeCourt();
                    std::cout << "Press Enter to continue..." << std::endl;
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }

                default:
                    std::cout << "Invalid option!" << std::endl;
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
            std::cout << "Enter valid operation!" << std::endl;
            break;
        }
    }

    std::cout << "Successfully Logged Out from Admin Panel!" << std::endl;
}