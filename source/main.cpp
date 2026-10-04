#include <iostream>
#include <vector>
#include <string>

#include "models/Freelancer.h"
#include "models/FreelancerLoader.h"

#include "trees/AVLTree.h"
#include "graph/Graph.h"

#include "algorithm/Matching.h"
#include "algorithm/Knapsack.h"

#include "heap/MaxHeap.h"

using namespace std;


// ==========================================================
// RUN ONE PROJECT
// ==========================================================

void runProject(
    const string& projectName,
    const vector<string>& requiredSkills,
    double maxHourlyRate,
    double totalProjectBudget,
    const vector<Freelancer>& freelancers
) {

    cout << "\n\n";
    cout << "==================================================\n";
    cout << "           INTELLIGENT FREELANCE MARKETPLACE\n";
    cout << "==================================================\n";

    cout << "\nProject: "
         << projectName
         << endl;

    cout << "Required Skills: ";

    for (const string& skill : requiredSkills) {
        cout << skill << " ";
    }

    cout << "\nMaximum Hourly Rate: Rs. "
         << maxHourlyRate
         << endl;

    cout << "Total Project Budget: Rs. "
         << totalProjectBudget
         << endl;


    // ------------------------------------------------------
    // MATCHING + MAX HEAP
    // ------------------------------------------------------

    MatchingEngine matcher;

    MaxHeap recommendationHeap;

    vector<SelectedFreelancer> candidates;


    cout << "\n\n========== MATCHING ANALYSIS ==========\n";


    for (const Freelancer& freelancer : freelancers) {

        double score =
            matcher.calculateMatchScore(
                freelancer,
                requiredSkills,
                maxHourlyRate
            );


        cout << "\n"
             << freelancer.name
             << " -> Match Score: "
             << score
             << endl;


        // Add freelancer to Max Heap
        recommendationHeap.insert(
            freelancer,
            score
        );


        // Only consider reasonably suitable candidates
        if (score >= 50.0) {

            candidates.push_back({
                freelancer,
                score
            });
        }
    }


    // ------------------------------------------------------
    // TOP-K RECOMMENDATIONS
    // ------------------------------------------------------

    recommendationHeap.displayTopK(3);


    // ------------------------------------------------------
    // 0/1 KNAPSACK
    // ------------------------------------------------------

    Knapsack knapsack;


    vector<SelectedFreelancer> selected =
        knapsack.selectFreelancers(
            candidates,
            static_cast<int>(totalProjectBudget)
        );


    knapsack.displaySelection(
        selected,
        static_cast<int>(totalProjectBudget)
    );
}


// ==========================================================
// MAIN
// ==========================================================

int main() {

    cout << "\n";
    cout << "==================================================\n";
    cout << "     INTELLIGENT FREELANCE MARKETPLACE PLATFORM\n";
    cout << "==================================================\n";


    // ======================================================
    // LOAD FREELANCERS FROM DATA FILE
    // ======================================================

    FreelancerLoader loader;

    vector<Freelancer> freelancers =
        loader.loadFromFile(
            "data/freelancers.txt"
        );


    if (freelancers.empty()) {

        cout << "\nNo freelancer data found.\n";

        return 1;
    }


    cout << "\nLoaded "
         << freelancers.size()
         << " freelancers successfully.\n";


    // ======================================================
    // AVL TREE
    // ======================================================

    AVLTree freelancerTree;


    for (const Freelancer& freelancer : freelancers) {

        freelancerTree.insert(
            freelancer
        );
    }


    freelancerTree.displayInorder();


    // ======================================================
    // AVL SEARCH
    // ======================================================

    cout << "\n========== AVL SEARCH ==========\n";


    int searchId = 108;


    Freelancer* result =
        freelancerTree.search(
            searchId
        );


    if (result != nullptr) {

        cout << "Freelancer Found:\n";

        cout << "ID: "
             << result->id
             << endl;

        cout << "Name: "
             << result->name
             << endl;

        cout << "Experience: "
             << result->experience
             << " years"
             << endl;
    }

    else {

        cout << "Freelancer not found.\n";
    }


    // ======================================================
    // GRAPH
    // ======================================================

    Graph graph;


    // ------------------------------------------------------
    // BACKEND PROJECT
    // ------------------------------------------------------

    graph.addEdge(
        "Project:Backend",
        "Skill:C++"
    );

    graph.addEdge(
        "Project:Backend",
        "Skill:SQL"
    );

    graph.addEdge(
        "Project:Backend",
        "Skill:DSA"
    );


    graph.addEdge(
        "Skill:C++",
        "Freelancer:101"
    );

    graph.addEdge(
        "Skill:C++",
        "Freelancer:105"
    );

    graph.addEdge(
        "Skill:SQL",
        "Freelancer:101"
    );

    graph.addEdge(
        "Skill:SQL",
        "Freelancer:110"
    );

    graph.addEdge(
        "Skill:DSA",
        "Freelancer:101"
    );

    graph.addEdge(
        "Skill:DSA",
        "Freelancer:105"
    );


    // ------------------------------------------------------
    // WEB PROJECT
    // ------------------------------------------------------

    graph.addEdge(
        "Project:Web",
        "Skill:React"
    );

    graph.addEdge(
        "Project:Web",
        "Skill:Node.js"
    );

    graph.addEdge(
        "Project:Web",
        "Skill:MongoDB"
    );


    graph.addEdge(
        "Skill:React",
        "Freelancer:103"
    );

    graph.addEdge(
        "Skill:React",
        "Freelancer:106"
    );

    graph.addEdge(
        "Skill:React",
        "Freelancer:109"
    );


    graph.addEdge(
        "Skill:Node.js",
        "Freelancer:103"
    );

    graph.addEdge(
        "Skill:Node.js",
        "Freelancer:107"
    );

    graph.addEdge(
        "Skill:Node.js",
        "Freelancer:109"
    );


    graph.addEdge(
        "Skill:MongoDB",
        "Freelancer:103"
    );

    graph.addEdge(
        "Skill:MongoDB",
        "Freelancer:107"
    );


    // ------------------------------------------------------
    // ML PROJECT
    // ------------------------------------------------------

    graph.addEdge(
        "Project:ML",
        "Skill:Python"
    );

    graph.addEdge(
        "Project:ML",
        "Skill:SQL"
    );

    graph.addEdge(
        "Project:ML",
        "Skill:Machine Learning"
    );


    graph.addEdge(
        "Skill:Python",
        "Freelancer:102"
    );

    graph.addEdge(
        "Skill:Python",
        "Freelancer:106"
    );

    graph.addEdge(
        "Skill:Python",
        "Freelancer:108"
    );

    graph.addEdge(
        "Skill:Python",
        "Freelancer:110"
    );


    graph.addEdge(
        "Skill:Machine Learning",
        "Freelancer:102"
    );

    graph.addEdge(
        "Skill:Machine Learning",
        "Freelancer:108"
    );


    // ======================================================
    // DISPLAY GRAPH
    // ======================================================

    graph.displayGraph();


    // ======================================================
    // BFS + DFS
    // ======================================================

    cout << "\n========== GRAPH TRAVERSAL ==========\n";


    cout << "\nStarting from Backend Project:";

    graph.BFS(
        "Project:Backend"
    );

    graph.DFS(
        "Project:Backend"
    );


    // ======================================================
    // PROJECT 1
    // ======================================================

    runProject(
        "Backend Development",

        {"C++", "SQL", "DSA"},

        900,       // maximum hourly rate

        1800,      // total project budget

        freelancers
    );


    // ======================================================
    // PROJECT 2
    // ======================================================

    runProject(
        "Full Stack Web Application",

        {"React", "Node.js", "MongoDB"},

        900,

        1800,

        freelancers
    );


    // ======================================================
    // PROJECT 3
    // ======================================================

    runProject(
        "Data and Machine Learning",

        {"Python", "SQL", "Machine Learning"},

        850,

        1700,

        freelancers
    );


    // ======================================================
    // PROGRAM COMPLETED
    // ======================================================

    cout << "\n\n";
    cout << "==================================================\n";
    cout << "             PROGRAM COMPLETED\n";
    cout << "==================================================\n";


    return 0;
}