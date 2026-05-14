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

    std::cout << std::endl << "Successfully Created Account !" << std::endl;
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

    std::cout << std::endl;
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

// incomplete
void User::bookings()
{
    if(booked.empty())
    {
        std::cout << std::endl;
        std::cout << "No Previous Bookings" << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Bookings-" << std::endl;

        for (int index = 0; index < (int)booked.size(); index++)
        {
            std::cout << booked[index] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "Enter 0 for back:" << std::endl;
    return;
}

// incomplete
void User::book()
{
    std::cout << "Select Court :-" << std::endl;
    return;
}

void User::Login(const std::string &password)
{
    if (password != this -> password)
        return;
    std::cout << "Successfully Logged In !" << std::endl;
    int task = 0;

    while(true)
    {
        cout << std::endl;
        #ifdef _WIN32
            std::system("cls"); // For Windows
        #else
            // Assume POSIX (Linux, macOS, etc.)
            std::system("clear");
        #endif

        if(currState == BANNED)
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
        if(! task)  break;

        switch(task)
        {
            case 1: bookings(); break;
            case 2: book();     break;
            default:    std::cout << "Enter valid operation !" << std::endl;    break;
        }
    }

    std::cout << "Successfully Logged Out !" << std::endl;
}