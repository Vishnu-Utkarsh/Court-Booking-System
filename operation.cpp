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
    std::cout << "Successfully Logged Out !" << std::endl;
}

void User::Login(const std::string &password)
{
    if (password != this->password)
        return;
    std::cout << "Successfully Logged In !" << std::endl;

    switch(currState)
    {
        // case FREE:      output.push_back('0');  break;
        // case BOOKED:    output.push_back('1');  break;
        // case BANNED:    output.push_back('2');  break;
        default:    break;
    }

    std::cout << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Select Court :-" << std::endl;
    std::cout << "Enter 1 to Select Badminton:" << std::endl;
    std::cout << "Enter 2 to Select Volleyball:" << std::endl;
    std::cout << "Enter 3 to Select Basketball:" << std::endl;
    std::cout << "Enter 4 to Select Football:" << std::endl;
    std::cout << "Enter 5 to Select Cricket:" << std::endl;
    std::cout << "Enter 0 to Exit:" << std::endl;
    std::cout << std::endl;
}