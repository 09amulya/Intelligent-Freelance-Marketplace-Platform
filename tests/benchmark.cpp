#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "../source/models/Freelancer.h"
#include "../source/algorithm/Matching.h"
#include "../source/heap/MaxHeap.h"

using namespace std;
using namespace chrono;


// ==========================================================
// GENERATE TEST FREELANCERS
// ==========================================================

vector<Freelancer> generateFreelancers(int count) {

    vector<Freelancer> freelancers;

    vector<string> skillPool = {
        "C++",
        "Python",
        "Java",
        "SQL",
        "React",
        "Node.js",
        "MongoDB",
        "DSA",
        "Machine Learning",
        "JavaScript"
    };

    freelancers.reserve(count);

    for (int i = 0; i < count; i++) {

        Freelancer freelancer;

        freelancer.id = 1000 + i;

        freelancer.name =
            "Freelancer_" + to_string(i);

        freelancer.skills.push_back(
            skillPool[i % skillPool.size()]
        );

        freelancer.skills.push_back(
            skillPool[(i + 3) % skillPool.size()]
        );

        freelancer.skills.push_back(
            skillPool[(i + 6) % skillPool.size()]
        );

        freelancer.experience =
            1 + (i % 10);

        freelancer.rating =
            4.0 + ((i % 10) * 0.1);

        freelancer.available =
            (i % 5 != 0);

        freelancer.hourlyRate =
            500 + (i % 10) * 100;

        freelancers.push_back(freelancer);
    }

    return freelancers;
}


// ==========================================================
// RUN ONE RECOMMENDATION PIPELINE
// ==========================================================

long long runPipeline(
    const vector<Freelancer>& freelancers
) {

    vector<string> requiredSkills = {
        "C++",
        "SQL",
        "DSA"
    };

    double maxHourlyRate = 900;

    MatchingEngine matcher;

    MaxHeap heap;


    auto start =
        high_resolution_clock::now();


    // ------------------------------------------------------
    // Match scoring + heap insertion
    // ------------------------------------------------------

    for (
        const Freelancer& freelancer :
        freelancers
    ) {

        double score =
            matcher.calculateMatchScore(
                freelancer,
                requiredSkills,
                maxHourlyRate
            );

        heap.insert(
            freelancer,
            score
        );
    }


    // ------------------------------------------------------
    // Top-K recommendation
    // ------------------------------------------------------

    vector<FreelancerMatch> recommendations =
        heap.getTopK(10);


    auto end =
        high_resolution_clock::now();


    return duration_cast<nanoseconds>(
        end - start
    ).count();
}


// ==========================================================
// BENCHMARK ONE DATASET SIZE
// ==========================================================

void benchmarkSize(
    int numberOfFreelancers,
    int repetitions
) {

    vector<Freelancer> freelancers =
        generateFreelancers(
            numberOfFreelancers
        );


    long long totalTime = 0;


    for (int i = 0;
         i < repetitions;
         i++) {

        totalTime +=
            runPipeline(freelancers);
    }


    double averageNanoseconds =
        static_cast<double>(
            totalTime
        ) / repetitions;


    double averageMicroseconds =
        averageNanoseconds / 1000.0;


    cout << numberOfFreelancers
         << "\t\t"
         << averageMicroseconds
         << " us"
         << endl;
}


// ==========================================================
// MAIN
// ==========================================================

int main() {

    cout << "\n";
    cout << "=============================================\n";
    cout << "       PERFORMANCE BENCHMARK\n";
    cout << "=============================================\n";


    cout << "\n";
    cout << "Freelancers\tAverage Execution Time\n";
    cout << "---------------------------------------------\n";


    vector<int> testSizes = {
        10,
        50,
        100,
        500,
        1000,
        5000
    };


    // Number of repetitions for each dataset.
    int repetitions = 1000;


    for (int size : testSizes) {

        benchmarkSize(
            size,
            repetitions
        );
    }


    cout << "\n";
    cout << "=============================================\n";
    cout << "Benchmark completed successfully.\n";
    cout << "Each dataset was tested "
         << repetitions
         << " times.\n";
    cout << "=============================================\n";


    return 0;
}