#ifndef FREELANCER_H
#define FREELANCER_H

#include <string>
#include <vector>

using namespace std;

struct Freelancer {
    int id;
    string name;
    vector<string> skills;

    int experience;
    double rating;
    bool available;
    double hourlyRate;
};

#endif