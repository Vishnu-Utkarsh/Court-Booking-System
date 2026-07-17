#ifndef UTILITIES
#define UTILITIES

#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "../headers/storage.hpp"

inline void clear()
{
    #ifdef _WIN32   
        std::system("cls"); // For Windows
    #else
        std::system("clear"); // Assume POSIX (Linux, macOS, etc.)
    #endif
}

inline int takeInput()
{
    int ans;

    while (! (std::cin >> ans))
    {
        std::cout << "Invalid input !\nPlease enter a valid integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
    }
    return ans;
}

inline bool validateDate(const std::string &date)
{
    std::istringstream ss(date);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return !ss.fail();
}

inline std::string getTodayDate()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return ss.str();
}

inline std::string getTimeStamp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d-%H-%M-%S");
    return ss.str();
}

inline std::string getDateOffset(int days)
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto futureTime = time + (days * 86400); // 86400 seconds in a day
    std::stringstream ss;
    ss << std::put_time(std::localtime(&futureTime), "%Y-%m-%d");
    return ss.str();
}

inline std::vector<std::string> getNextDays()
{
    std::vector<std::string> dates;

    for (int i = 0; i < maxDayLimit; i++)
        dates.push_back(getDateOffset(i));

    return dates;
}

#endif