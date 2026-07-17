#ifndef STORAGE
#define STORAGE

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>

#include "user.hpp"
#include "court.hpp"
#include "admin.hpp"

const int durationLimit = 1;    // Hours per booking
const int maxDayLimit = 5;      // Number of days in advance for booking

std::map<std::string, User> users;
std::vector<Court *> courts;

std::unordered_map<std::string, int> index = {{"Badminton Court", 1}, {"Basketball Court", 2}, {"Volleyball Court", 3}, {"Football Ground", 4}, {"Cricket Ground", 5}};

#endif