#ifndef COURT
#define COURT

#include "Template.hpp"
#include <ostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <map>

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
{   AVAILABLE, RESERVED, Maintainace };

std::ostream& operator<<(std::ostream& os, courtStatus currState)
{
    switch (currState)
    {
        case courtStatus::AVAILABLE:    os << "Available";          break;
        // case courtStatus::RESERVED:     os << "RESERVED";           break;
        case courtStatus::Maintainace:  os << "under Maintainace";  break;
        default:                        os << "UNKNOWN";            break;
    }
    return os;
}

const int maxDayLimit = 5; // hrs

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

    bool isBooked() const { return !bookedBy.empty(); }

    // Change Format
    std::string toString() const
    {
        std::stringstream ss;
        ss << date << " " << std::setfill('0') << std::setw(2) << hour << ":00";
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
    string courtName;
    type courtType;
    std::map<std::string, std::map<int, TimeSlot>> bookings; // date -> hour -> TimeSlot

protected:
    void switchStatus(courtStatus newState);
    bool checkAvailibility() const;

public:
    // constructor
    Court();
    Court(type courtType, string courtName);
    Court(type courtType, string courtName, int courtNumber);

    // getters
    std::string getBookedBy() const;
    const std::map<std::string, std::map<int, TimeSlot>> &getBookings() const;

    // booking methods
    bool bookSlot(const std::string &date, int hour, const std::string &username);
    bool isSlotAvailable(const std::string &date, int hour) const;
    std::vector<TimeSlot> getAvailableSlots(const std::string &date) const;

    // save file
    string saveFile();

    // output operator (<<)
    friend std::ostream &operator<<(std::ostream &os, const Court &court)
    {
        os << court.courtName;
        if(court.courtNumber)   os << ' ' << court.courtNumber;
        os << "\t\t";
        os << "type: " << court.courtType << "\t\t";
        os << "status: " << (court.checkAvailibility() ? "Available" : "Not Available") << "\t\t";
        return os;
    }
};

// forward declaration
Court::Court() : currState(AVAILABLE) {}
Court::Court(type courtType, string courtName) : currState(AVAILABLE), courtName(courtName), courtType(courtType) {}
Court::Court(type courtType, string courtName, int courtNumber) : currState(AVAILABLE), courtName(courtName), courtType(courtType), courtNumber(courtNumber) {}

void Court::switchStatus(courtStatus newState) { currState = newState; }
bool Court::checkAvailibility() const { return currState == AVAILABLE; }
const std::map<std::string, std::map<int, TimeSlot>> &Court::getBookings() const { return bookings; }

bool Court::isSlotAvailable(const std::string &date, int hour) const
{
    auto dateIt = bookings.find(date);
    if (dateIt == bookings.end())
        return true;

    auto hourIt = dateIt->second.find(hour);
    return hourIt == dateIt->second.end() || !hourIt->second.isBooked();
}

bool Court::bookSlot(const std::string &date, int hour, const std::string &username)
{
    if (!isSlotAvailable(date, hour))
        return false;

    bookings[date][hour] = TimeSlot(date, hour, username);
    return true;
}

std::vector<TimeSlot> Court::getAvailableSlots(const std::string &date) const
{
    std::vector<TimeSlot> available;
    for (int hour = 6; hour < 22; hour++) // Operating hours: 6 AM to 11 PM
    {
        if (isSlotAvailable(date, hour))
            available.push_back(TimeSlot(date, hour));
    }
    return available;
}

// Derived Class Badminton
class Badminton : public Court
{
public:
    // constructor
    Badminton();
    Badminton(const int number);
};

// forward declaration
Badminton::Badminton() : Court(INDOOR, "Badminton Court") {}
Badminton::Badminton(const int number) : Court(INDOOR, "Badminton Court", number) {}

// Derived Class Basketball
class Basketball : public Court
{
public:
    // constructor
    Basketball();
    Basketball(const int number);
};

// forward declaration
Basketball::Basketball() : Court(OUTDOOR, "Basketball Court") {}
Basketball::Basketball(const int number) : Court(OUTDOOR, "Basketball Court", number) {}

// Derived Class Volleyball
class Volleyball : public Court
{
public:
    // constructor
    Volleyball();
    Volleyball(const int number);
};

// forward declaration
Volleyball::Volleyball() : Court(INDOOR, "Volleyball Court") {}
Volleyball::Volleyball(const int number) : Court(INDOOR, "Volleyball Court", number) {}

// Derived Class Football
class Football : public Court
{
public:
    // constructor
    Football();
    Football(const int number);
};

// forward declaration
Football::Football() : Court(GROUND, "Football Ground") {}
Football::Football(const int number) : Court(GROUND, "Football Ground", number) {}

// Derived Class Cricket
class Cricket : public Court
{
public:
    // constructor
    Cricket();
    Cricket(const int number);
};

// forward declaration
Cricket::Cricket() : Court(GROUND, "Cricket Ground") {}
Cricket::Cricket(const int number) : Court(GROUND, "Cricket Ground", number) {}


void _print(type courtType)
    {   cerr << courtType; }
void print(type courtType)
    {   cout << courtType; }

void _print(Court court)
    {   cerr << endl << court; }
void print(Court &court)
    {   cout << court << endl; }


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
    // dates.push_back(getTodayDate());
    
    for (int i = 1; i <= maxDayLimit; i++)
        dates.push_back(getDateOffset(i));

    return dates;
}

#endif