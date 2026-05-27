#ifndef COURT
#define COURT

#include "storage.hpp"

#include <ostream>
#include <chrono>
#include <iomanip>
#include <sstream>

// -------------------- Structure Definition --------------------

// Court Type
enum type
{   INDOOR, OUTDOOR, GROUND };
std::ostream& operator<<(std::ostream& os, type courtType)
{
    switch (courtType)
    {
        case type::INDOOR:  os << "INDOOR";     break;
        case type::OUTDOOR: os << "OUTDOOR";    break;
        case type::GROUND:  os << "GROUND";     break;
        default:            os << "UNKNOWN";    break;
    }
    return os;
}

// Court Status
enum courtStatus
{   AVAILABLE, RESERVED, MAINTAINANCE };
std::ostream& operator<<(std::ostream& os, courtStatus currState)
{
    switch (currState)
    {
        case courtStatus::AVAILABLE:    os << "Available";      break;
        case courtStatus::RESERVED:     os << "Reserved";       break;
        case courtStatus::MAINTAINANCE: os << "Maintainance";   break;
        default:                        os << "UNKNOWN";        break;
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

    TimeSlot() : date(""), hour(-1), bookedBy("") {}
    TimeSlot(const std::string &d, int h) : date(d), hour(h), bookedBy("") {}
    TimeSlot(const std::string &d, int h, const std::string &user) : date(d), hour(h), bookedBy(user) {}

    bool isBooked() const { return ! bookedBy.empty(); }

    // Change Format
    std::string toString() const
    {
        std::stringstream ss;
        ss << date << " \t" << std::setw(2) << std::setfill('0') << hour << ":00 to " << std::setw(2) << std::setfill('0') << hour + durationLimit << ":00";
        return ss.str();
    }

    static TimeSlot fromString(const std::string &str)
    {
        std::string date, time, user;
        std::stringstream ss(str);
        int hour;

        ss >> date >> hour;

        TimeSlot slot(date, hour);
        if (ss >> user)
            slot.bookedBy = user;

        return slot;
    }
};

// Parent Class Court
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
    int getCourtNumber() const;

    // booking methods
    bool bookSlot(const std::string &date, int hour, const std::string &username);
    bool cancelSlot(const std::string &date, int hour);
    bool isSlotAvailable(const std::string &date, int hour) const;
    std::vector<TimeSlot> getAvailableSlots(const std::string &date) const;
    void switchStatus(courtStatus newState);

    // save file
    std::string saveFile();

    // delete expired bookings
    void deleteExpiredBookings();

    // output operator (<<)
    friend std::ostream &operator<<(std::ostream &os, const Court &court)
    {
        std::string suffix = " ";
        if(court.courtNumber)   suffix += '0' + court.courtNumber;
        os << std::setw(20) << std::setfill(' ') << court.courtName << suffix;
        os << "\t\t";
        os << "type: " << court.courtType << "\t\t";
        os << "status: " << court.currState << "\t\t";
        return os;
    }
};

// forward declaration
Court::Court() : currState(AVAILABLE) {}
Court::Court(type courtType, std::string courtName, courtStatus currState) : currState(currState), courtName(courtName), courtType(courtType) {}
Court::Court(type courtType, std::string courtName, int courtNumber, courtStatus currState) : currState(currState), courtName(courtName), courtType(courtType), courtNumber(courtNumber) {}

void Court::switchStatus(courtStatus newState) { currState = newState; }
courtStatus Court::getStatus() const { return currState; }
std::string Court::getCourtName() const { return courtName + ' ' + std::to_string(courtNumber); }
int Court::getCourtNumber() const { return courtNumber; }
const std::map<std::string, std::map<int, TimeSlot>> &Court::getBookings() const { return bookings; }

bool Court::isSlotAvailable(const std::string &date, int hour) const
{
    auto dateIt = bookings.find(date);
    if (dateIt == bookings.end())
        return true;

    auto hourIt = dateIt -> second.find(hour);
    return hourIt == dateIt->second.end() || ! hourIt -> second.isBooked();
}

bool Court::bookSlot(const std::string &date, int hour, const std::string &username)
{
    if (!isSlotAvailable(date, hour))
        return false;

    bookings[date][hour] = TimeSlot(date, hour, username);
    return true;
}

bool Court::cancelSlot(const std::string &date, int hour)
{
    auto dateIt = bookings.find(date);
    if (dateIt == bookings.end())
        return false;

    auto hourIt = dateIt->second.find(hour);
    if (hourIt == dateIt->second.end() || !hourIt->second.isBooked())
        return false;

    dateIt->second.erase(hourIt);
    return true;
}

std::vector<TimeSlot> Court::getAvailableSlots(const std::string &date) const
{
    std::vector<TimeSlot> available;
    for (int hour = 6; hour < 22; hour++) // Operating hours: 6 AM to 10 PM
    {
        if (isSlotAvailable(date, hour))
            available.push_back(TimeSlot(date, hour));
    }
    return available;
}


// -------------------- Derived Classes --------------------

// Derived Class Badminton
class Badminton : public Court
{
public:
    // constructor
    Badminton(courtStatus currState);
    Badminton(const int number, courtStatus currState);
};

// forward declaration
Badminton::Badminton(courtStatus currState) : Court(INDOOR, "Badminton Court", currState) {}
Badminton::Badminton(const int number, courtStatus currState) : Court(INDOOR, "Badminton Court", number, currState) {}

// Derived Class Basketball
class Basketball : public Court
{
public:
    // constructor
    Basketball(courtStatus currState);
    Basketball(const int number, courtStatus currState);
};

// forward declaration
Basketball::Basketball(courtStatus currState) : Court(OUTDOOR, "Basketball Court", currState) {}
Basketball::Basketball(const int number, courtStatus currState) : Court(OUTDOOR, "Basketball Court", number, currState) {}

// Derived Class Volleyball
class Volleyball : public Court
{
public:
    // constructor
    Volleyball(courtStatus currState);
    Volleyball(const int number, courtStatus currState);
};

// forward declaration
Volleyball::Volleyball(courtStatus currState) : Court(INDOOR, "Volleyball Court", currState) {}
Volleyball::Volleyball(const int number, courtStatus currState) : Court(INDOOR, "Volleyball Court", number, currState) {}

// Derived Class Football
class Football : public Court
{
public:
    // constructor
    Football(courtStatus currState);
    Football(const int number, courtStatus currState);
};

// forward declaration
Football::Football(courtStatus currState) : Court(GROUND, "Football Ground", currState) {}
Football::Football(const int number, courtStatus currState) : Court(GROUND, "Football Ground", number, currState) {}

// Derived Class Cricket
class Cricket : public Court
{
public:
    // constructor
    Cricket(courtStatus currState);
    Cricket(const int number, courtStatus currState);
};

// forward declaration
Cricket::Cricket(courtStatus currState) : Court(GROUND, "Cricket Ground", currState) {}
Cricket::Cricket(const int number, courtStatus currState) : Court(GROUND, "Cricket Ground", number, currState) {}


// -------------------- Utilities --------------------

void print(type courtType)
    {   std::cout << std::setw(15) << courtType; }
void print(Court &court)
    {   std::cout << std::setw(16) << court << std::endl; }


// Utility Functions for date/time operations
inline std::string getTodayDate()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
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

void Court::deleteExpiredBookings()
{
    std::string today = getTodayDate();
    std::vector<std::string> datesToRemove;

    for (auto &dateEntry : bookings)
    {
        if (dateEntry.first < today)
            datesToRemove.push_back(dateEntry.first);
    }

    for (const auto &date : datesToRemove)
        bookings.erase(date);
}

inline bool validateDate(const std::string &date)
{
    std::istringstream ss(date);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return !ss.fail();
}

#endif