#include "Template.hpp"
#include "storage.hpp"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

// read from CSV file
void readUserData(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open user data." << std::endl;
        return;
    }

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> row_fields;

        // Split the line into fields using comma as delimiter
        while (std::getline(ss, field, ','))
            row_fields.push_back(field);

        // Process the data
        if (row_fields.empty())
            continue;

        int state = std::stoi(row_fields[2]);
        string username = row_fields[0], password = row_fields[1];

        users[username] = User(username, password, (userStatus) state);
    }

    file.close();
    std::cerr << "CSV file imported and user data readed." << std::endl;
    return;
}

void readCourtData(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open court data." << std::endl;
        return;
    }

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> row_fields;

        // Split the line into fields using comma as delimiter
        while (std::getline(ss, field, ','))
            row_fields.push_back(field);

        // Process the data
        if (row_fields.empty())
            continue;

        int courtType = index[row_fields[0]];
        Court *court;

        switch (courtType)
        {
            case 1:
            {
                int courtNumber = std::stoi(row_fields[1]), currState = stoi(row_fields[2]);
                court = new Badminton(courtNumber, (courtStatus) currState);
                break;
            }

            case 2:
            {
                int courtNumber = std::stoi(row_fields[1]), currState = stoi(row_fields[2]);
                court = new Basketball(courtNumber, (courtStatus) currState);
                break;
            }
        
            case 3:
            {
                int courtNumber = std::stoi(row_fields[1]), currState = stoi(row_fields[2]);
                court = new Volleyball(courtNumber, (courtStatus) currState);
                break;
            }
        
            case 4:
            {
                int courtNumber = std::stoi(row_fields[1]), currState = stoi(row_fields[2]);
                court = new Football(courtNumber, (courtStatus) currState);
                break;
            }
        
            case 5:
            {
                int courtNumber = std::stoi(row_fields[1]), currState = stoi(row_fields[2]);
                court = new Cricket(courtNumber, (courtStatus) currState);
                break;
            }

            default:    std::cerr << "Currupted File !" << std::endl;   return;
        }
        courts.push_back(court);
    }

    file.close();
    std::cerr << "CSV file imported and court data readed." << std::endl;
    return;
}

// save to CSV file
string User::saveFile()
{
    string output = username;
    output.push_back(',');
    output += password;
    output.push_back(',');

    switch(currState)
    {
        case AUTHORIZED:    output.push_back('0');  break;
        case BANNED:        output.push_back('1');  break;
    }
    return output;
}
void saveUserData(const std::string &filename)
{
    std::ofstream file;
    file.open(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    for (auto &user : users)
        file << user.second.saveFile() << std::endl;

    file.close();
    std::cerr << "CSV file created and user data written." << std::endl;

    debug(users);
    std::cerr << std::endl;
    return;
}

string Court::saveFile()
{
    string output = courtName;
    output.push_back(',');
    output += to_string(courtNumber);
    output.push_back(',');

    switch(currState)
    {
        case AVAILABLE:     output.push_back('0');  break;
        case MAINTAINANCE:  output.push_back('1');  break;
    }
    return output;
}
void saveCourtData(const std::string &filename)
{
    std::ofstream file;
    file.open(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    for (auto &court : courts)
        file << court -> saveFile() << std::endl;

    file.close();
    std::cerr << "CSV file created and court data written." << std::endl;

    for (auto &court : courts)
        _print(*court);
    return;
}

// Load bookings from file
void readBookings(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "No existing bookings file found. Starting fresh." << std::endl;
        return;
    }

    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string courtName, courtNumStr, date, hourStr, username;
        
        if (!std::getline(ss, courtName, ','))      continue;
        if (!std::getline(ss, courtNumStr, ','))    continue;
        if (!std::getline(ss, date, ','))           continue;
        if (!std::getline(ss, hourStr, ','))        continue;
        if (!std::getline(ss, username, ','))       continue;
        
        int hour = std::stoi(hourStr);
        
        // Find matching court
        for (auto &court : courts)
        {
            string courtId = court -> saveFile();
            while(courtId.back() != ',')    courtId.pop_back();
            courtId.pop_back();

            if (courtId != courtName + "," + courtNumStr)
                continue;

            court->bookSlot(date, hour, username);
            break;
        }
    }

    file.close();
    std::cerr << "Bookings loaded." << std::endl;
    return;
}

// Expired bookings
void deleteExpiredBookings()
{
    for (auto &court : courts)
        court -> deleteExpiredBookings();
    std::cerr << "Expired bookings deleted." << std::endl;
}

// Save bookings
void saveBookings(const std::string &filename)
{
    std::ofstream file;
    file.open(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open bookings file for writing." << std::endl;
        return;
    }

    // Format: CourtName,CourtNumber,Date,Hour,Username
    for (int i = 0; i < (int)courts.size(); i++)
    {
        const auto &bookingsMap = courts[i]->getBookings();
        for (const auto &dateEntry : bookingsMap)
        {
            for (const auto &hourEntry : dateEntry.second)
            {
                if (! hourEntry.second.isBooked())
                    continue;

                string courtId = courts[i] -> saveFile();
                while(courtId.back() != ',')    courtId.pop_back();
                courtId.pop_back();

                file << courtId << "," 
                     << dateEntry.first << ","
                     << hourEntry.first << ","
                     << hourEntry.second.bookedBy << std::endl;
            }
        }
    }

    file.close();
    std::cerr << "Bookings file saved." << std::endl;
    return;
}