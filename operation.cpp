#include "storage.hpp"

// -------------------- Admin --------------------
// Login
void adminLogin()
{
    std::string adminName, adminPassword;
    std::cout << std::endl;
    std::cout << "====== ADMIN LOGIN ======" << std::endl;
    std::cout << "Enter 0 to Back" << std::endl;

    std::cout << "Enter admin username: ";
    std::cin >> adminName;

    if (adminName == "0")
        return;

    std::cout << "Enter admin password: ";
    std::cin >> adminPassword;

    if (adminPassword == "0")
        return;

    obj.showAdminPanel(adminPassword);
}

// -------------------- Operations --------------------
// Create new user account
void createAccount()
{
    std::string username, password;
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

    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif

    std::cout << std::endl
              << "Successfully Created Account !" << std::endl;
    User newUser(username, password);
    users[username] = newUser;
    newUser.Login(password);
}

// User Login
void userLogin()
{
    std::string username, password;
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

    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif

    std::cout << std::endl;
    loginUser.Login(password);
}

// Operate while LoggedIn
void User::Login(const std::string &password)
{
    if (password != this->password)
        return;
    std::cout << "Successfully Logged In !" << std::endl;
    int task = 0;

    while (true)
    {
        std::cout << std::endl;

        if (currState == BANNED)
        {
            std::cout << std::endl;
            std::cout << "ID Banned !" << std::endl;
            std::cout << "Press Enter to logOut..." << std::endl;
            std::cout << std::endl;
            std::cin.ignore();
            std::cin.get();
            break;
        }

        std::cout << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Choose tab :-" << std::endl;
        std::cout << "Enter 1 to Check Bookings:" << std::endl;
        std::cout << "Enter 2 to Book Court:" << std::endl;
        std::cout << "Enter 3 to Cancel Booking:" << std::endl;
        std::cout << "Enter 0 to Logout:" << std::endl;
        std::cout << std::endl;

        std::cin >> task;
        if (!task)
            break;

        switch (task)
        {
        case 1:
            showBookings();
            break;
        case 2:
            book();
            break;
        case 3:
            cancelBooking();
            break;
        default:
            std::cout << "Enter valid operation !" << std::endl;
            break;
        }
    }

    std::cout << "Successfully Logged Out !" << std::endl;
}