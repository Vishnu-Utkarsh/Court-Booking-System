#ifndef STORAGE
#define STORAGE

#include "user.hpp"
#include "court.hpp"

unordered_map<string, User> users;
vector<Court> courts;

static unordered_map<string, int> index = {{"Badminton Court", 1}, {"Basketball Court", 2}, {"Volleyball Court", 3}, {"Football Ground", 4}, {"Cricket Ground", 5}};

#endif