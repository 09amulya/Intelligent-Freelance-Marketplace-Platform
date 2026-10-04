#ifndef MATCHING_H
#define MATCHING_H

#include "../models/Freelancer.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MatchingEngine {

private:

    // Calculate how well freelancer skills match
    // the project's required skills.
    double calculateSkillScore(
        const Freelancer& freelancer,
        const vector<string>& requiredSkills
    ) {

        if (requiredSkills.empty()) {
            return 0.0;
        }

        int matchedSkills = 0;

        for (const string& requiredSkill : requiredSkills) {

            for (const string& freelancerSkill : freelancer.skills) {

                if (requiredSkill == freelancerSkill) {
                    matchedSkills++;
                    break;
                }
            }
        }

        return (static_cast<double>(matchedSkills)
                / requiredSkills.size()) * 100.0;
    }


    // Experience score.
    // 5 years or more gets maximum score.
    double calculateExperienceScore(
        const Freelancer& freelancer
    ) {

        double score =
            (static_cast<double>(freelancer.experience) / 5.0) * 100.0;

        return min(score, 100.0);
    }


    // Rating is out of 5.
    double calculateRatingScore(
        const Freelancer& freelancer
    ) {

        return (freelancer.rating / 5.0) * 100.0;
    }


    // Available = 100, unavailable = 0.
    double calculateAvailabilityScore(
        const Freelancer& freelancer
    ) {

        return freelancer.available ? 100.0 : 0.0;
    }


    // Lower hourly rate gets a better budget score.
    double calculateBudgetScore(
        const Freelancer& freelancer,
        double maxBudget
    ) {

        if (freelancer.hourlyRate <= maxBudget) {
            return 100.0;
        }

        // Penalize freelancers above the budget.
        double excess =
            freelancer.hourlyRate - maxBudget;

        double score =
            100.0 - ((excess / maxBudget) * 100.0);

        return max(score, 0.0);
    }


public:

    /*
        Proposed project-specific weights:

        Skill Match       = 40%
        Experience        = 20%
        Rating            = 15%
        Availability      = 10%
        Budget            = 15%

        Total             = 100%
    */

    double calculateMatchScore(
        const Freelancer& freelancer,
        const vector<string>& requiredSkills,
        double maxBudget
    ) {

        double skillScore =
            calculateSkillScore(
                freelancer,
                requiredSkills
            );

        double experienceScore =
            calculateExperienceScore(
                freelancer
            );

        double ratingScore =
            calculateRatingScore(
                freelancer
            );

        double availabilityScore =
            calculateAvailabilityScore(
                freelancer
            );

        double budgetScore =
            calculateBudgetScore(
                freelancer,
                maxBudget
            );


        double finalScore =
            (0.40 * skillScore) +
            (0.20 * experienceScore) +
            (0.15 * ratingScore) +
            (0.10 * availabilityScore) +
            (0.15 * budgetScore);


        return finalScore;
    }


    // Display detailed matching information
    void displayMatchScore(
        const Freelancer& freelancer,
        const vector<string>& requiredSkills,
        double maxBudget
    ) {

        double skillScore =
            calculateSkillScore(
                freelancer,
                requiredSkills
            );

        double experienceScore =
            calculateExperienceScore(
                freelancer
            );

        double ratingScore =
            calculateRatingScore(
                freelancer
            );

        double availabilityScore =
            calculateAvailabilityScore(
                freelancer
            );

        double budgetScore =
            calculateBudgetScore(
                freelancer,
                maxBudget
            );

        double finalScore =
            (0.40 * skillScore) +
            (0.20 * experienceScore) +
            (0.15 * ratingScore) +
            (0.10 * availabilityScore) +
            (0.15 * budgetScore);


        cout << "\n----------------------------------\n";

        cout << "Freelancer: "
             << freelancer.name << endl;

        cout << "Skill Score: "
             << skillScore << endl;

        cout << "Experience Score: "
             << experienceScore << endl;

        cout << "Rating Score: "
             << ratingScore << endl;

        cout << "Availability Score: "
             << availabilityScore << endl;

        cout << "Budget Score: "
             << budgetScore << endl;

        cout << "Final Match Score: "
             << finalScore << endl;

        cout << "----------------------------------\n";
    }
};

#endif