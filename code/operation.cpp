#include "storage.hpp"
#include "utilities.cpp"

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

    obj.showAdminPanel(adminName, adminPassword);
}

// -------------------- User --------------------
// Create new user account
void createAccount()
{
    std::string username, password;
    std::cout << "Enter 0 to Back";

    while (true)
    {
        std::cout << std::endl << "Enter username: ";
        std::cin >> username;

        if (username == "0")
            return;
        if (! users.count(username))
            break;

        std::cout << std::endl << "Username Already exist"
                  << std::endl << "Try using different username !";
    }

    std::cout << "Create password: ";
    std::cin >> password;

    if (password == "0")
        return;

    clear();
    std::cout << "Successfully Created New Account !" << std::endl;

    User newUser(username, password);
    users[username] = newUser;
    newUser.Login(password);
}

// User Login
void userLogin()
{
    std::string username, password;
    std::cout << std:: endl << "Enter 0 to Back";

    while (true)
    {
        std::cout << std:: endl << "Enter username: ";
        std::cin >> username;

        if (username == "0")
            return;
        if (users.count(username))
            break;

        std::cout << std::endl << "Username not found"
                  << std::endl << "Try Again !";
    }

    User loginUser = users[username];
    bool loggedIn = false;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (password == "0")
        return;

    clear();
    loginUser.Login(password);
}

// Operate while LoggedIn
void User::Login(const std::string &password)
{
    if (password != this -> password)
    {
        std::cout << std::endl << "Wrong Password !";
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "Successfully Logged In !" << std::endl;

    while (true)
    {
        if (currState == BANNED)
        {
            std::cout << std::endl << "ID Banned !";
            std::cout << std::endl << "Press Enter to LogOut...";
            std::cout << std::endl;
            std::cin.ignore();
            std::cin.get();
            return;
        }

        std::cout << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Choose tab :-" << std::endl;
        std::cout << "Enter 1 to Check Bookings:" << std::endl;
        std::cout << "Enter 2 to Book Court:" << std::endl;
        std::cout << "Enter 3 to Cancel Booking:" << std::endl;
        std::cout << "Enter 0 to Logout:" << std::endl;
        std::cout << std::endl;

        int task = takeInput();
        if (! task)
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

        clear();
    }

    std::cout << std::endl << "Successfully Logged Out !";
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
    return;
}