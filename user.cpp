#ifndef USER_CPP
#define USER_CPP

#include "user.hpp"

User::User() {}
User::User(const std::string &name, const std::string &pass) : username(name), password(pass), currState(AUTHORIZED) {}
User::User(const std::string &name, const std::string &pass, const userStatus newState) : username(name), password(pass), currState(newState) {}

std::string User::getUsername() { return username; }
std::string User::getPassword() { return password; } // remove
userStatus User::getStatus() { return currState; }

bool User::checkPassword(const std::string &password) { return password == this->password; }

void User::switchStatus(const userStatus newStatus) { currState = newStatus; }

// -------------------- Utilities --------------------

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

// -------------------- Booking --------------------

// Book court availability view
void User::book()
{
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif

    std::cout << std::endl;
    std::cout << "====== BOOKING COURT ======" << std::endl;
    std::cout << std::endl;

    if(courts.empty())
    {
        std::cout << "No courts available for booking." << std::endl;
        std::cout << std::endl
                  << "Press Enter to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::vector<std::string> nextDays = getNextDays();

    // Display available courts
    std::cout << "All Courts:" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (int i = 0; i < (int)courts.size(); i++)
        std::cout << std::setw(3) << std::setfill(' ') << (i + 1) << ") " << *courts[i] << std::endl;

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << std::endl
              << "Select court number (or 0 to cancel): ";

    int courtChoice;
    std::cin >> courtChoice;
    std::cout << std::endl;

    if (! courtChoice)
        return;

    if (courtChoice < 1 || courtChoice > (int)courts.size())
    {
        std::cout << "Invalid court selection!" << std::endl;
        return;
    }

    Court *selectedCourt = courts[courtChoice - 1];
    if(selectedCourt -> getStatus() == RESERVED)
    {
        std::cout << "Court already reserved. Try another court !" << std::endl;
        return;
    }
    if(selectedCourt -> getStatus() == MAINTAINANCE)
    {
        std::cout << "Court under maintainance. Try another court !" << std::endl;
        return;
    }

    // Display day availability
    std::cout << std::endl;
    std::cout << "====== BOOKING DATE ======" << std::endl;

    int dayChoice = -1;
    while (dayChoice < 0 || dayChoice >= (int)nextDays.size())
    {
        std::cout << std::endl
                  << "Select Date (YYYY-MM-DD format):" << std::endl;

        for (int i = 0; i < (int)nextDays.size(); i++)
            std::cout << std::setw(3) << (i + 1) << ") " << nextDays[i] << std::endl;

        std::cout << std::endl
                  << "Enter choice (or 0 to cancel): ";
        std::cin >> dayChoice;

        if (! dayChoice--)
            return;

        if (dayChoice < 0 || dayChoice >= (int)nextDays.size())
        {
            std::cout << "Invalid date selection!" << std::endl;
            dayChoice = -1;
        }
    }

    std::string selectedDate = nextDays[dayChoice];
    auto availableSlots = selectedCourt -> getAvailableSlots(selectedDate);


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
        std::cout << std::setw(3) << std::setfill(' ') << i + 1 << ") "
                  << std::setw(2) << std::setfill('0') << availableSlots[i].hour << ":00 - "
                  << std::setw(2) << std::setfill('0') << availableSlots[i].hour + durationLimit << ":00" << std::endl;
    }

    std::cout << std::endl
              << "Select time slot (or 0 to cancel): ";
    int slotChoice;
    std::cin >> slotChoice;

    if (! slotChoice--)
        return;

    if (slotChoice < 0 || slotChoice >= (int)availableSlots.size())
    {
        std::cout << "Invalid time slot selection!" << std::endl;
        return;
    }
    if (! selectedCourt -> bookSlot(selectedDate, availableSlots[slotChoice].hour, username))
    {
        std::cout << "Failed to book slot. Please try again." << std::endl;
        return;
    }

    // Book slot
    std::cout << std::endl;
    std::cout << "======= BOOKING CONFIRMED =======" << std::endl;
    std::cout << "User: " << username << std::endl;
    std::cout << "Court: " << *selectedCourt << std::endl;
    std::cout << "Date: " << selectedDate << std::endl;
    std::cout << "Time: " << availableSlots[slotChoice].hour << ":00 - "
                << (availableSlots[slotChoice].hour + durationLimit) << ":00" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << std::endl
                << "Press Enter to continue..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

// Cancel user bookings
void User::cancelBooking()
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
                    userBookings.emplace_back(court, hourEntry.second);
            }
        }
    }

    if (userBookings.empty())
    {
        std::cout << "No Bookings to Cancel" << std::endl;
        std::cout << std::endl;
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "Your Bookings:" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (int i = 0; i < (int)userBookings.size(); i++)
        std::cout << std::setw(3) << std::setfill(' ') << (i + 1) << ") " << *userBookings[i].first
                  << " : " << userBookings[i].second.toString() << std::endl;

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << std::endl
              << "Select booking to cancel (or 0 to cancel): ";

    int choice;
    std::cin >> choice;

    if (! choice)
        return;

    if (choice < 0 || choice > (int)userBookings.size())
    {
        std::cout << "Invalid selection!" << std::endl;
        return;
    }

    TimeSlot bookingToCancel = userBookings[choice - 1].second;
    Court *courtToCancel = userBookings[choice - 1].first;

    std::cout << std::endl;
    std::cout << "====== CANCEL BOOKING ======" << std::endl;
    std::cout << "Confirming cancellation of:" << std::endl;
    std::cout << "Court: " << *courtToCancel << std::endl;
    std::cout << "Date & Time: " << bookingToCancel.toString() << std::endl;
    std::cout << "Enter 'yes' to confirm cancellation: ";

    std::string confirm;
    std::cin >> confirm;

    if (confirm == "yes")
    {
        courtToCancel -> cancelSlot(bookingToCancel.date, bookingToCancel.hour);
        std::cout << std::endl;
        std::cout << "Booking cancelled!" << std::endl;
    }
    else
        std::cout << "Cancellation aborted." << std::endl;

    std::cout << std::endl
              << "Press Enter to continue..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

// Display user bookings
void User::showBookings()
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
                    userBookings.emplace_back(court, hourEntry.second);
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
            std::cout << std::setw(3) << std::setfill(' ') << (i + 1) << ") " << *userBookings[i].first
                      << " : " << userBookings[i].second.toString() << std::endl;
        }
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    return;
}

#endif