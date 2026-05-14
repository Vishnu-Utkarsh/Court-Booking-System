#ifndef COURT
#define COURT

#include "Template.hpp"
#include <ostream>

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
        case courtStatus::RESERVED:     os << "RESERVED";           break;
        case courtStatus::Maintainace:  os << "under Maintainace";  break;
        default:                        os << "UNKNOWN";            break;
    }
    return os;
}

const int durationLimit = 3;    // hrs

// Parent Class Court
class Court
{
private:
    courtStatus currState;
    int courtNumber = 0;
    string courtName, bookedBy;
    type courtType;

protected:
    void switchStatus(courtStatus newState);
    bool checkAvailibility() const;
    bool book(const string &name);

public:
    // constructor
    Court();
    Court(type courtType, string courtName);
    Court(type courtType, string courtName, int courtNumber);
    Court(type courtType, string courtName, string bookedBy, int courtNumber);

    // save file
    string saveFile();

    // output operator (<<)
    friend std::ostream &operator<<(std::ostream &os, const Court &court)
    {
        os << court.courtName;
        if(court.courtNumber)   os << ' ' << court.courtNumber;
        os << "\t\t";
        os << "type: " << court.courtType << "\t\t";
        os << "status: " << (court.checkAvailibility() ? "FREE" : "Not FREE") << "\t\t";
        return os;
    }
};

// forward declaration
Court::Court() : currState(AVAILABLE) {}
Court::Court(type courtType, string courtName) : currState(AVAILABLE), courtName(courtName), courtType(courtType) {}
Court::Court(type courtType, string courtName, int courtNumber) : currState(AVAILABLE), courtName(courtName), courtType(courtType), courtNumber(courtNumber) {}
Court::Court(type courtType, string courtName, string bookedBy, int courtNumber = 0) : currState(RESERVED), courtName(courtName), courtType(courtType), bookedBy(bookedBy), courtNumber(courtNumber) {}

void Court::switchStatus(courtStatus newState) { currState = newState; }
bool Court::checkAvailibility() const { return currState; }
bool Court::book(const string &name)
{
    if(currState)   return false;   // Booked or in Maintainance

    currState = RESERVED;
    bookedBy = name;
    return true;
}

// Derived Class Badminton
class Badminton : public Court
{
public:
    // constructor
    Badminton();
    Badminton(const int number);
    Badminton(const int number, string bookedBy);
};

// forward declaration
Badminton::Badminton() : Court(INDOOR, "Badminton Court") {}
Badminton::Badminton(const int number) : Court(INDOOR, "Badminton Court", number) {}
Badminton::Badminton(const int number, string bookedBy) : Court(INDOOR, "Badminton Court", bookedBy, number) {}

// Derived Class Basketball
class Basketball : public Court
{
public:
    // constructor
    Basketball();
    Basketball(const int number);
    Basketball(const int number, string bookedBy);
};

// forward declaration
Basketball::Basketball() : Court(OUTDOOR, "Basketball Court") {}
Basketball::Basketball(const int number) : Court(OUTDOOR, "Basketball Court", number) {}
Basketball::Basketball(const int number, string bookedBy) : Court(OUTDOOR, "Basketball Court", bookedBy, number) {}

// Derived Class Volleyball
class Volleyball : public Court
{
public:
    // constructor
    Volleyball();
    Volleyball(const int number);
    Volleyball(const int number, string bookedBy);
};

// forward declaration
Volleyball::Volleyball() : Court(INDOOR, "Volleyball Court") {}
Volleyball::Volleyball(const int number) : Court(INDOOR, "Volleyball Court", number) {}
Volleyball::Volleyball(const int number, string bookedBy) : Court(INDOOR, "Volleyball Court", bookedBy, number) {}

// Derived Class Football
class Football : public Court
{
public:
    // constructor
    Football();
    Football(const int number);
    Football(const int number, string bookedBy);
};

// forward declaration
Football::Football() : Court(GROUND, "Football Ground") {}
Football::Football(const int number) : Court(GROUND, "Football Ground", number) {}
Football::Football(const int number, string bookedBy) : Court(GROUND, "Football Ground", bookedBy, number) {}

// Derived Class Cricket
class Cricket : public Court
{
public:
    // constructor
    Cricket();
    Cricket(const int number);
    Cricket(const int number, string bookedBy);
};

// forward declaration
Cricket::Cricket() : Court(GROUND, "Cricket Ground") {}
Cricket::Cricket(const int number) : Court(GROUND, "Cricket Ground", number) {}
Cricket::Cricket(const int number, string bookedBy) : Court(GROUND, "Cricket Ground", bookedBy, number) {}


void _print(type courtType)
    {   cerr << courtType; }
void print(type courtType)
    {   cout << courtType; }

void _print(Court court)
    {   cerr << endl << court; }
void print(Court &court)
    {   cout << court << endl; }

#endif