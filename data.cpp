#include "Template.hpp"
#include "storage.hpp"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

// show data
void displayUserData()
{
    cout << "Username Status" << endl;
    for(auto &data : users)
        print(data.second);
}

void displayCourtData()
{
    cout << "Court Status" << endl;
    for(auto &data : courts)
        print(data);
}

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

        int state = stoi(row_fields[2]);
        string username = row_fields[0], password = row_fields[1];

        users[username] = User(username, password, (userStatus) state);
    }

    file.close();
    std::cerr << "CSV file imported and user data readed successfully." << std::endl;
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
                int courtNumber = stoi(row_fields[1]);

                if(row_fields.size() == 2)
                    court = new Badminton(courtNumber);
                else
                    court = new Badminton(courtNumber, row_fields[2]);
                break;
            }

            case 2:
            {
                int courtNumber = stoi(row_fields[1]);

                if(row_fields.size() == 2)
                    court = new Basketball(courtNumber);
                else
                    court = new Basketball(courtNumber, row_fields[2]);
                break;
            }
        
            case 3:
            {
                int courtNumber = stoi(row_fields[1]);

                if(row_fields.size() == 2)
                    court = new Volleyball(courtNumber);
                else
                    court = new Volleyball(courtNumber, row_fields[2]);
                break;
            }
        
            case 4:
            {
                int courtNumber = stoi(row_fields[1]);

                if(row_fields.size() == 2)
                    court = new Football(courtNumber);
                else
                    court = new Football(courtNumber, row_fields[2]);
                break;
            }
        
            case 5:
            {
                int courtNumber = stoi(row_fields[1]);

                if(row_fields.size() == 2)
                    court = new Cricket(courtNumber);
                else
                    court = new Cricket(courtNumber, row_fields[2]);
                break;
            }

            default:    std::cerr << "Currupted File !" << std::endl;   return;
        }
        courts.push_back(*court);
    }

    file.close();
    std::cerr << "CSV file imported and court data readed successfully." << std::endl;
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
        case FREE:      output.push_back('0');  break;
        case BOOKED:    output.push_back('1');  break;
        case BANNED:    output.push_back('2');  break;
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
    std::cerr << "CSV file created and user data written successfully." << std::endl;

    debug(users);
    cerr << endl;
    return;
}

string Court::saveFile()
{
    string output = courtName;
    output.push_back(',');
    output += to_string(courtNumber);

    if(available)   return output;

    output.push_back(',');
    output += bookedBy;
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
        file << court.saveFile() << std::endl;

    file.close();
    std::cerr << "CSV file created and court data written successfully." << std::endl;

    debug(courts);
    cerr << endl;
    return;
}