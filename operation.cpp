#include "Template.hpp"
#include "storage.hpp"

// Create Account
void createAccount()
{
    string username, password;

    while(true)
    {
        std::cout << std::endl
            << "Enter new username: ";
        std::cin >> username;

        if(! users.count(username))
            break;

        std::cout << std::endl
                  << "Username Already exist" << std::endl
                  << "Try Again !" << std::endl;
    }

    std::cout << std::endl
         << "Create password: ";
    std::cin >> password;

    User newUser(username, password);
    debug(newUser);
    users[username] = newUser;
}

// User Login
void userLogin()
{
    string username, password;

    while(true)
    {
        std::cout << std::endl
            << "Enter username: ";
        std::cin >> username;

        if(users.count(username))
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

    loggedIn = loginUser.checkPassword(password);

    if(! loggedIn)
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

    debug(loginUser);
    std::cout << "Successfully Logged In !" << std::endl;
    // Login(loginUser);
}