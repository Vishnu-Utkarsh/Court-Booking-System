#ifndef COURT_HPP
#define COURT_HPP

#include "storage.hpp"

#include <ostream>
#include <chrono>
#include <iomanip>
#include <sstream>

// Court Type
enum type
{
    INDOOR,
    OUTDOOR,
    GROUND
};
std::ostream &operator<<(std::ostream &os, type courtType)
{
    switch (courtType)
    {
    case type::INDOOR:
        os << "INDOOR";
        break;
    case type::OUTDOOR:
        os << "OUTDOOR";
        break;
    case type::GROUND:
        os << "GROUND";
        break;
    default:
        os << "UNKNOWN";
        break;
    }
    return os;
}

// Court Status
enum courtStatus
{
    AVAILABLE,
    RESERVED,
    MAINTAINANCE
};
std::ostream &operator<<(std::ostream &os, courtStatus currState)
{
    switch (currState)
    {
    case courtStatus::AVAILABLE:
        os << "Available";
        break;
    case courtStatus::RESERVED:
        os << "Reserved";
        break;
    case courtStatus::MAINTAINANCE:
        os << "Maintainance";
        break;
    default:
        os << "UNKNOWN";
        break;
    }
    return os;
}

// Time Slot Booking Structure
class TimeSlot
{
public:
    std::string date; // YYYY-MM-DD format
    int hour;         // 6-22
    std::string bookedBy;
    std::vector<std::string> issuedItems;

    TimeSlot();
    TimeSlot(const std::string &d, int h);
    TimeSlot(const std::string &d, int h, const std::string &user);

    bool isBooked() const;
    std::string toString() const;
    std::string issuedItemsToString() const;
};

// -------------------- Abstract Classes --------------------
class Court
{
private:
    courtStatus currState;
    int courtNumber = 0;
    std::string courtName;
    type courtType;
    std::map<std::string, std::map<int, TimeSlot>> bookings; // date -> hour -> TimeSlot

public:
    // constructor
    Court();
    Court(type courtType, std::string courtName, courtStatus currState);
    Court(type courtType, std::string courtName, int courtNumber, courtStatus currState);

    // getters
    const std::map<std::string, std::map<int, TimeSlot>> &getBookings() const;
    courtStatus getStatus() const;
    std::string getCourtName() const;

    // booking methods
    bool bookSlot(const std::string &date, int hour, const std::string &username);
    bool cancelSlot(const std::string &date, int hour);
    bool isSlotAvailable(const std::string &date, int hour) const;
    std::vector<TimeSlot> getAvailableSlots(const std::string &date) const;
    void switchStatus(courtStatus newState);

    // save file
    std::string saveFile();

    // attach issued item to a booked slot
    bool addIssuedItem(const std::string &date, int hour, const std::string &item);

    // issue items provided by the court (abstract)
    virtual std::vector<std::string> issueItems() const = 0;

    // delete expired bookings
    void deleteExpiredBookings();

    // output operator (<<)
    friend std::ostream &operator<<(std::ostream &os, const Court &court)
    {
        os << std::setw(20) << std::setfill(' ') << court.getCourtName();
        os << "\t\t";
        os << "type: " << court.courtType << "\t\t";
        os << "status: " << court.currState << "\t\t";
        return os;
    }
};

// -------------------- Derived Classes --------------------

// Badminton
class Badminton : public Court
{
public:
    // constructor
    Badminton(courtStatus currState);
    Badminton(const int number, courtStatus currState);
    std::vector<std::string> issueItems() const override;
};

// Basketball
class Basketball : public Court
{
public:
    // constructor
    Basketball(courtStatus currState);
    Basketball(const int number, courtStatus currState);
    std::vector<std::string> issueItems() const override;
};

// Volleyball
class Volleyball : public Court
{
public:
    // constructor
    Volleyball(courtStatus currState);
    Volleyball(const int number, courtStatus currState);
    std::vector<std::string> issueItems() const override;
};

// Football
class Football : public Court
{
public:
    // constructor
    Football(courtStatus currState);
    Football(const int number, courtStatus currState);
    std::vector<std::string> issueItems() const override;
};

// Cricket
class Cricket : public Court
{
public:
    // constructor
    Cricket(courtStatus currState);
    Cricket(const int number, courtStatus currState);
    std::vector<std::string> issueItems() const override;
};

// Lawn Tennis
class LawnTennis : public Court
{
public:
    // constructor
    LawnTennis(courtStatus currState);
    LawnTennis(const int number, courtStatus currState);
    std::vector<std::string> issueItems() const override;
};

#endif