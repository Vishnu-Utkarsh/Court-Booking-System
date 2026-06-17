#include "court.hpp"

// -------------------- TimeSlot --------------------
TimeSlot::TimeSlot() : date(""), hour(-1), bookedBy("") {}
TimeSlot::TimeSlot(const std::string &d, int h) : date(d), hour(h), bookedBy("") {}
TimeSlot::TimeSlot(const std::string &d, int h, const std::string &user) : date(d), hour(h), bookedBy(user) {}

bool TimeSlot::isBooked() const { return ! bookedBy.empty(); }

std::string TimeSlot::toString() const
{
    std::stringstream ss;
    ss << date << " \t" << std::setw(2) << std::setfill('0') << hour << ":00 to " << std::setw(2) << std::setfill('0') << hour + durationLimit << ":00";
    return ss.str();
}

TimeSlot TimeSlot::fromString(const std::string &str) const
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

// -------------------- Court --------------------

Court::Court() : currState(AVAILABLE) {}
Court::Court(type courtType, std::string courtName, courtStatus currState) : currState(currState), courtName(courtName), courtType(courtType) {}
Court::Court(type courtType, std::string courtName, int courtNumber, courtStatus currState) : currState(currState), courtName(courtName), courtType(courtType), courtNumber(courtNumber) {}

void Court::switchStatus(courtStatus newState) { currState = newState; }
courtStatus Court::getStatus() const { return currState; }
std::string Court::getCourtName() const { return courtName + " " + std::to_string(courtNumber); }
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

// Badminton
Badminton::Badminton(courtStatus currState) : Court(INDOOR, "Badminton Court", currState) {}
Badminton::Badminton(const int number, courtStatus currState) : Court(INDOOR, "Badminton Court", number, currState) {}

// Basketball
Basketball::Basketball(courtStatus currState) : Court(OUTDOOR, "Basketball Court", currState) {}
Basketball::Basketball(const int number, courtStatus currState) : Court(OUTDOOR, "Basketball Court", number, currState) {}

// Volleyball
Volleyball::Volleyball(courtStatus currState) : Court(INDOOR, "Volleyball Court", currState) {}
Volleyball::Volleyball(const int number, courtStatus currState) : Court(INDOOR, "Volleyball Court", number, currState) {}

// Football
Football::Football(courtStatus currState) : Court(GROUND, "Football Ground", currState) {}
Football::Football(const int number, courtStatus currState) : Court(GROUND, "Football Ground", number, currState) {}

// Cricket
Cricket::Cricket(courtStatus currState) : Court(GROUND, "Cricket Ground", currState) {}
Cricket::Cricket(const int number, courtStatus currState) : Court(GROUND, "Cricket Ground", number, currState) {}


// -------------------- Utilities --------------------

inline std::string getTodayDate()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return ss.str();
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

void print(type courtType)
    {   std::cout << std::setw(15) << courtType; }
void print(Court &court)
    {   std::cout << std::setw(16) << court << std::endl; }