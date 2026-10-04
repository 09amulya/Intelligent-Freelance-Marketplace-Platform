#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "../models/Freelancer.h"
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

struct SelectedFreelancer {
    Freelancer freelancer;
    double score;
};

class Knapsack {

public:

    /*
        Select freelancers under a fixed budget.

        Each freelancer can either be:
        - selected (1)
        - not selected (0)

        The value of a freelancer is represented
        by their Match Score.
    */

    vector<SelectedFreelancer> selectFreelancers(
        const vector<SelectedFreelancer>& candidates,
        int budget
    ) {

        int n = candidates.size();

        // Convert budget to integer for DP.
        // Freelancer rates are rounded to integer values.
        vector<vector<double>> dp(
            n + 1,
            vector<double>(budget + 1, 0.0)
        );

        // Build DP table
        for (int i = 1; i <= n; i++) {

            int cost =
                static_cast<int>(
                    candidates[i - 1].freelancer.hourlyRate
                );

            double value =
                candidates[i - 1].score;

            for (int b = 0; b <= budget; b++) {

                // Don't select freelancer
                dp[i][b] = dp[i - 1][b];

                // Select freelancer if affordable
                if (cost <= b) {

                    dp[i][b] = max(
                        dp[i][b],
                        value + dp[i - 1][b - cost]
                    );
                }
            }
        }

        // Recover selected freelancers
        vector<SelectedFreelancer> selected;

        int remainingBudget = budget;

        for (int i = n; i > 0; i--) {

            if (dp[i][remainingBudget] !=
                dp[i - 1][remainingBudget]) {

                selected.push_back(
                    candidates[i - 1]
                );

                int cost =
                    static_cast<int>(
                        candidates[i - 1]
                            .freelancer
                            .hourlyRate
                    );

                remainingBudget -= cost;
            }
        }

        reverse(
            selected.begin(),
            selected.end()
        );

        return selected;
    }


    void displaySelection(
        const vector<SelectedFreelancer>& selected,
        int budget
    ) {

        cout << "\n===== BUDGET-CONSTRAINED SELECTION =====\n";

        double totalCost = 0;
        double totalScore = 0;

        for (const auto& candidate : selected) {

            cout << "\nFreelancer: "
                 << candidate.freelancer.name
                 << endl;

            cout << "Match Score: "
                 << candidate.score
                 << endl;

            cout << "Hourly Rate: Rs. "
                 << candidate.freelancer.hourlyRate
                 << endl;

            totalCost +=
                candidate.freelancer.hourlyRate;

            totalScore +=
                candidate.score;
        }

        cout << "\n-----------------------------\n";

        cout << "Total Cost: Rs. "
             << totalCost
             << endl;

        cout << "Total Match Value: "
             << totalScore
             << endl;

        cout << "Available Budget: Rs. "
             << budget
             << endl;

        cout << "Remaining Budget: Rs. "
             << budget - totalCost
             << endl;
    }
};

#endif