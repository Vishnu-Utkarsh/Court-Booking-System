#include <ctime>
#include <iomanip>
#include <string>

#include "utilities.cpp"
#include "data.cpp"
#include "operation.cpp"
#include "court.cpp"
#include "user.cpp"
#include "admin.cpp"

void operate()
{
    while(true)
    {
        clear();
        std::cout << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << "                    Select Task                   " << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << std::endl;
        std::cout << "  [1] Create new user account:" << std::endl;
        std::cout << "  [2] Login to your account:" << std::endl;
        std::cout << "  [3] Login as Admin:" << std::endl;
        std::cout << "  [0] Exit:" << std::endl;
        std::cout << std::endl;

        std::cout << "Select an Option: ";
        int task = takeInput();

        switch(task)
        {
            case 1: createAccount();    break;
            case 2: userLogin();        break;
            case 3: adminLogin();       break;

            case 0:
            {
                std::time_t now = std::time(0);
                std::tm *local_time_struct = std::localtime(&now);

                std::cerr << "\n Data Updated by: " << std::put_time(local_time_struct, "%Y-%m-%d %H:%M:%S");
                std::cout << "\n~~Exit~~";

                return;
                break;
            }
            default:
            {
                std::cout << std::endl << "Enter valid option !";
                std::cout << std::endl << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            }
        }
    }
}

int main()
{
    readUserData("data/userData.csv");
    readCourtData("data/courtData.csv");
    readBookings("data/bookings.csv");

    deleteExpiredBookings();
    operate();

    saveUserData("data/userData.csv");
    saveCourtData("data/courtData.csv");
    saveBookings("data/bookings.csv");

    freeMemory();
}