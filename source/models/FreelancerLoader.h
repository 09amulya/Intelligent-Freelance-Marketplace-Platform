#ifndef FREELANCER_LOADER_H
#define FREELANCER_LOADER_H

#include "Freelancer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class FreelancerLoader {

public:

    vector<Freelancer> loadFromFile(
        const string& filename
    ) {
        vector<Freelancer> freelancers;

        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Could not open file: "
                 << filename << endl;

            return freelancers;
        }

        string line;

        while (getline(file, line)) {

            if (line.empty()) {
                continue;
            }

            stringstream ss(line);

            string idStr;
            string name;
            string skillsStr;
            string experienceStr;
            string ratingStr;
            string availableStr;
            string hourlyRateStr;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, skillsStr, '|');
            getline(ss, experienceStr, '|');
            getline(ss, ratingStr, '|');
            getline(ss, availableStr, '|');
            getline(ss, hourlyRateStr, '|');

            Freelancer freelancer;

            freelancer.id = stoi(idStr);
            freelancer.name = name;

            stringstream skillStream(skillsStr);
            string skill;

            while (getline(skillStream, skill, ',')) {
                freelancer.skills.push_back(skill);
            }

            freelancer.experience = stoi(experienceStr);
            freelancer.rating = stod(ratingStr);
            freelancer.available = (availableStr == "1");
            freelancer.hourlyRate = stod(hourlyRateStr);

            freelancers.push_back(freelancer);
        }

        file.close();

        return freelancers;
    }
};

#endif