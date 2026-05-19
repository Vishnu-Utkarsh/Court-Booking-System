#include "Template.hpp"
#include "storage.hpp"

// Create Account
void createAccount()
{
    string username, password;
    std::cout << "Enter 0 to Back";

    while (true)
    {
        std::cout << std::endl
                  << "Enter username: ";
        std::cin >> username;

        if (username == "0")
            return;
        if (!users.count(username))
            break;

        std::cout << std::endl
                  << "Username Already exist" << std::endl
                  << "Try Again !" << std::endl;
    }

    std::cout << std::endl
              << "Create password: ";
    std::cin >> password;

    if (password == "0")
        return;

    std::cout << std::endl;
    #ifdef _WIN32
        std::system("cls"); // For Windows
    #else
        // Assume POSIX (Linux, macOS, etc.)
        std::system("clear");
    #endif

    std::cout << std::endl
              << "Successfully Created Account !" << std::endl;
    User newUser(username, password);
    debug(newUser);
    users[username] = newUser;
}

// User Login
void userLogin()
{
    string username, password;
    std::cout << "Enter 0 to Back";

    while (true)
    {
        std::cout << std::endl
                  << "Enter username: ";
        std::cin >> username;

        if (username == "0")
            return;
        if (users.count(username))
            break;

        std::cout << std::endl
                  << "Username not found" << std::endl
                  << "Try Again !" << std::endl;
    }

    User loginUser = users[username];
    bool loggedIn = false;

    std::cout << std::endl
              << "Enter password: ";
    std::cin >> password;

    if (password == "0")
        return;

    loggedIn = loginUser.checkPassword(password);

    if (!loggedIn)
    {
        std::cout << std::endl
                  << "Wrong Password !" << std::endl;
        return;
    }

    cout << std::endl;
    #ifdef _WIN32
        std::system("cls"); // For Windows
    #else
        // Assume POSIX (Linux, macOS, etc.)
        std::system("clear");
    #endif

    std::cout << std::endl;
    debug(loginUser);
    loginUser.Login(password);
}

// Display user bookings
void User::bookings()
{
    std::cout << std::endl;
    std::vector<std::pair<Court *, TimeSlot>> userBookings;

    // Find all slots booked by this user across all courts
    for (auto &court : courts)
    {
        const auto &bookingsMap = court->getBookings();
        for (const auto &dateEntry : bookingsMap)
        {
            for (const auto &hourEntry : dateEntry.second)
            {
                if (hourEntry.second.isBooked() && hourEntry.second.bookedBy == username)
                    userBookings.push_back({court, hourEntry.second});
            }
        }
    }

    if (userBookings.empty())
    {
        std::cout << "No Bookings Yet" << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Your Bookings:" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;

        for (int i = 0; i < (int)userBookings.size(); i++)
        {
            std::cout << (i + 1) << ") " << *userBookings[i].first
                      << " - " << userBookings[i].second.toString() << std::endl;
        }
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    return;
}

// Book court with 2-day availability view
void User::book()
{
    std::cout << std::endl;
    std::cout << "====== BOOKING COURT ======" << std::endl;
    std::cout << std::endl;

    // Get next 2 days
    std::vector<std::string> nextDays = getNextDays();

    // Display available courts
    std::cout << "Available Courts:" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (int i = 0; i < (int)courts.size(); i++)
        std::cout << i << ") " << *courts[i] << std::endl;

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << std::endl
              << "Select court number (or -1 to cancel): ";

    int courtChoice;
    std::cin >> courtChoice;

    if (courtChoice == -1)
        return;

    if (courtChoice < 0 || courtChoice >= (int)courts.size())
    {
        std::cout << "Invalid court selection!" << std::endl;
        return;
    }

    Court *selectedCourt = courts[courtChoice];

    // Display day availability
    std::cout << std::endl;
    std::cout << "====== AVAILABILITY FOR NEXT FEW DAYS ======" << std::endl;

    int dayChoice = -1;
    while (dayChoice < 0 || dayChoice >= (int)nextDays.size())
    {
        std::cout << std::endl
                  << "Select Date:" << std::endl;

        for (int i = 0; i < (int)nextDays.size(); i++)
            std::cout << i << ") " << nextDays[i] << std::endl;

        std::cout << std::endl
                  << "Enter choice (or -1 to cancel): ";
        std::cin >> dayChoice;

        if (dayChoice == -1)
            return;

        if (dayChoice < 0 || dayChoice >= (int)nextDays.size())
        {
            std::cout << "Invalid date selection!" << std::endl;
            dayChoice = -1;
        }
    }

    std::string selectedDate = nextDays[dayChoice];
    auto availableSlots = selectedCourt->getAvailableSlots(selectedDate);

    std::cout << std::endl;
    std::cout << "====== AVAILABLE TIME SLOTS FOR " << selectedDate << " ======" << std::endl;
    std::cout << std::endl;

    if (availableSlots.empty())
    {
        std::cout << "No available slots for this date." << std::endl;
        return;
    }

    // Display available slots
    for (int i = 0; i < (int)availableSlots.size(); i++)
    {
        std::cout << i << ") " << std::setfill('0') << std::setw(2)
                  << availableSlots[i].hour << ":00 - "
                  << std::setfill('0') << std::setw(2)
                  << (availableSlots[i].hour + durationLimit) << ":00" << std::endl;
    }

    std::cout << std::endl
              << "Select time slot (or -1 to cancel): ";
    int slotChoice;
    std::cin >> slotChoice;

    if (slotChoice == -1)
        return;

    if (slotChoice < 0 || slotChoice >= (int)availableSlots.size())
    {
        std::cout << "Invalid time slot selection!" << std::endl;
        return;
    }

    // Book the slot
    if (selectedCourt->bookSlot(selectedDate, availableSlots[slotChoice].hour, username))
    {
        std::cerr << std::endl << " Booked -> " << username << ' ';
        debug(*selectedCourt);
        debug(selectedDate);
        debug(availableSlots[slotChoice].hour);

        std::cout << std::endl;
        std::cout << "======= BOOKING CONFIRMED =======" << std::endl;
        std::cout << "User: " << username << std::endl;
        std::cout << "Court: " << *selectedCourt << std::endl;
        std::cout << "Date: " << selectedDate << std::endl;
        std::cout << "Time: " << std::setfill('0') << std::setw(2)
                  << availableSlots[slotChoice].hour << ":00 - "
                  << std::setfill('0') << std::setw(2)
                  << (availableSlots[slotChoice].hour + durationLimit) << ":00" << std::endl;
        std::cout << "================================" << std::endl;
        std::cout << std::endl
                  << "Press Enter to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
    }
    else
    {
        std::cout << "Failed to book slot. Please try again." << std::endl;
    }
}

void User::Login(const std::string &password)
{
    if (password != this->password)
        return;
    std::cout << "Successfully Logged In !" << std::endl;
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

        if (currState == BANNED)
        {
            std::cout << std::endl;
            std::cout << "ID Banned !" << std::endl;
            std::cout << "Press any key to logOut" << std::endl;
            std::cout << std::endl;
            std::cin >> task;
            break;
        }

        std::cout << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Choose tab :-" << std::endl;
        std::cout << "Enter 1 for Bookings Tab:" << std::endl;
        std::cout << "Enter 2 to Book Court:" << std::endl;
        std::cout << "Enter 0 to Logout:" << std::endl;
        std::cout << std::endl;

        cin >> task;
        if (!task)
            break;

        switch (task)
        {
        case 1:
            bookings();
            break;
        case 2:
            book();
            break;
        default:
            std::cout << "Enter valid operation !" << std::endl;
            break;
        }
    }

    std::cout << "Successfully Logged Out !" << std::endl;
}