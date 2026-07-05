#include "../headers/user.hpp"
#include "utilities.cpp"

User::User() {}
User::User(const std::string &name, const std::string &pass) : username(name), password(pass), currState(AUTHORIZED) {}
User::User(const std::string &name, const std::string &pass, const userStatus newState) : username(name), password(pass), currState(newState) {}

void User::switchStatus(const userStatus newStatus) { currState = newStatus; }

// -------------------- Account Settings --------------------
void User::changePassword()
{
    clear();
    std::cout << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "          CHANGE PASSWORD          " << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << std::endl;
    std::string oldPassword, newPassword, checkPassword;

    while(true)
    {
        std::cout << "Enter \"0\" to exit !" << std::endl;
        std::cout << "Enter old Password: ";
        std::cin >> oldPassword;

        if(oldPassword == "0")      break;
        if(oldPassword != password)
        {
            std::cout << std::endl << "Wrong Password !";
            break;
        }

        std::cout << "Enter new Password: ";
        std::cin >> newPassword;
        if(newPassword == "0")      break;

        std::cout << "Confirm new Password: ";
        std::cin >> checkPassword;
        if(checkPassword == "0") break;
    
        if(checkPassword != newPassword)
        {
            std::cout << std::endl << "Password didn't matched !";
            break;
        }

        password = newPassword;
        std::cout << std::endl << "Password changed Successfully !";
        break;
    }

    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
    return;
}

// -------------------- Booking --------------------

// Book court availability view
void User::book() const
{
    clear();
    std::cout << std::endl;
    std::cout << "====================================================================================================" << std::endl;
    std::cout << "                                            BOOKING COURT                                           " << std::endl;
    std::cout << "====================================================================================================" << std::endl;
    std::cout << std::endl;

    if(courts.empty())
    {
        std::cout << std::endl << "No courts available for booking.";
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::vector<std::string> nextDays = getNextDays();

    // Display available courts
    std::cout << "All Courts:" << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < (int)courts.size(); i++)
        std::cout << std::setw(3) << std::setfill(' ') << (i + 1) << ") " << *courts[i] << std::endl;

    std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << std::endl << "Select court number (or 0 to cancel): ";
    int courtChoice = takeInput();
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
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    if(selectedCourt -> getStatus() == MAINTAINANCE)
    {
        std::cout << "Court under maintainance. Try another court !" << std::endl;
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
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
        dayChoice = takeInput();

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
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    // Display available slots
    for (int i = 0; i < (int)availableSlots.size(); i++)
    {
        std::cout << std::setw(3) << std::setfill(' ') << i + 1 << ") "
                  << std::setw(2) << std::setfill('0') << availableSlots[i].hour << ":00 - "
                  << std::setw(2) << std::setfill('0') << availableSlots[i].hour + durationLimit << ":00" << std::endl;
    }

    std::cout << std::endl << "Select time slot (or 0 to cancel): ";
    int slotChoice = takeInput();

    if (! slotChoice--)
        return;

    if (slotChoice < 0 || slotChoice >= (int)availableSlots.size())
    {
        std::cout << "Invalid time slot selection!" << std::endl;
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
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
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// Cancel user bookings
void User::cancelBooking() const
{
    clear();
    std::cout << std::endl;
    std::cout << "==================================================================================================================================================" << std::endl;
    std::cout << "                                                                BOOKING CANCELLATION                                                              " << std::endl;
    std::cout << "==================================================================================================================================================" << std::endl;
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
        std::cout << std::endl << "No Bookings to Cancel";
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "Your Bookings:" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < (int)userBookings.size(); i++)
        std::cout << std::setw(3) << std::setfill(' ') << (i + 1) << ") " << *userBookings[i].first
                  << " : " << userBookings[i].second.toString() << std::endl;

    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl
              << "Select a booking to cancel (or 0 to cancel): ";

    int choice = takeInput();

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
    std::cout << "======================== CANCEL BOOKING ========================" << std::endl;
    std::cout << "Confirming cancellation of -" << std::endl;
    std::cout << "Court: " << *courtToCancel << std::endl;
    std::cout << "Date & Time: " << bookingToCancel.toString() << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << std::endl << "Enter 'yes' to confirm cancellation: ";

    std::string confirm;
    std::cin >> confirm;

    if (confirm == "yes")
    {
        courtToCancel -> cancelSlot(bookingToCancel.date, bookingToCancel.hour);
        std::cout << std::endl  << "Booking cancelled !";
    }
    else
        std::cout << std::endl << "Cancellation aborted.";

    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// Display user bookings
void User::showBookings() const
{
    clear();
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
        std::cout << std::endl << "No Bookings Yet" << std::endl;
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "============================================================== Your Bookings ==============================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < (int)userBookings.size(); i++)
    {
        std::cout << std::setw(3) << std::setfill(' ') << (i + 1) << ") " << *userBookings[i].first
                    << " : " << userBookings[i].second.toString() << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
    return;
}