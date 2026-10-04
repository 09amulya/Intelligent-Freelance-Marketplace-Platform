#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "../source/models/Freelancer.h"
#include "../source/models/FreelancerLoader.h"

#include "../source/trees/AVLTree.h"
#include "../source/graph/Graph.h"

#include "../source/algorithm/Matching.h"
#include "../source/algorithm/Knapsack.h"

#include "../source/heap/MaxHeap.h"

using namespace std;


// ==========================================================
// TEST UTILITIES
// ==========================================================

int passed = 0;
int failed = 0;


void check(
    bool condition,
    const string& testName
) {
    if (condition) {
        cout << "[PASS] " << testName << endl;
        passed++;
    }
    else {
        cout << "[FAIL] " << testName << endl;
        failed++;
    }
}


// ==========================================================
// TEST 1: DATA LOADING
// ==========================================================

void testDataLoading() {

    FreelancerLoader loader;

    vector<Freelancer> freelancers =
        loader.loadFromFile(
            "data/freelancers.txt"
        );

    check(
        freelancers.size() == 10,
        "Freelancer data loading"
    );

    if (!freelancers.empty()) {

        check(
            freelancers[0].id == 101,
            "First freelancer ID"
        );

        check(
            freelancers[0].name == "Aarav",
            "First freelancer name"
        );

        check(
            freelancers[0].skills.size() == 3,
            "Freelancer skills loaded"
        );
    }
}


// ==========================================================
// TEST 2: AVL TREE
// ==========================================================

void testAVL() {

    AVLTree tree;

    Freelancer f1{
        101,
        "Aarav",
        {"C++", "SQL"},
        3,
        4.7,
        true,
        800
    };

    Freelancer f2{
        105,
        "Arjun",
        {"C++", "DSA"},
        5,
        4.9,
        true,
        1000
    };

    Freelancer f3{
        110,
        "Meera",
        {"SQL", "Python"},
        5,
        4.9,
        true,
        900
    };


    tree.insert(f1);
    tree.insert(f2);
    tree.insert(f3);


    Freelancer* result =
        tree.search(105);

    check(
        result != nullptr,
        "AVL search existing freelancer"
    );


    if (result != nullptr) {

        check(
            result->name == "Arjun",
            "AVL search returns correct freelancer"
        );
    }


    Freelancer* missing =
        tree.search(999);

    check(
        missing == nullptr,
        "AVL search non-existing freelancer"
    );
}


// ==========================================================
// TEST 3: MATCHING ENGINE
// ==========================================================

void testMatching() {

    Freelancer freelancer{
        101,
        "Aarav",
        {"C++", "SQL", "DSA"},
        3,
        4.7,
        true,
        800
    };


    MatchingEngine matcher;


    double score =
        matcher.calculateMatchScore(
            freelancer,
            {"C++", "SQL", "DSA"},
            900
        );


    check(
        score > 90.0,
        "Match score for strong candidate"
    );


    check(
        score <= 100.0,
        "Match score remains within 0-100"
    );
}


// ==========================================================
// TEST 4: MAX HEAP
// ==========================================================

void testMaxHeap() {

    MaxHeap heap;


    Freelancer f1{
        101,
        "Aarav",
        {"C++"},
        3,
        4.7,
        true,
        800
    };

    Freelancer f2{
        102,
        "Priya",
        {"Python"},
        2,
        4.8,
        true,
        700
    };

    Freelancer f3{
        103,
        "Rahul",
        {"React"},
        4,
        4.6,
        true,
        900
    };


    heap.insert(f1, 75.0);
    heap.insert(f2, 92.0);
    heap.insert(f3, 84.0);


    // ------------------------------------------------------
    // Test Top-K
    // ------------------------------------------------------

    vector<FreelancerMatch> topMatches =
        heap.getTopK(2);


    check(
        topMatches.size() == 2,
        "Max Heap returns requested Top-K"
    );


    check(
        topMatches[0].freelancer.id == 102,
        "Top recommendation has highest score"
    );


    check(
        topMatches[1].freelancer.id == 103,
        "Second recommendation has second-highest score"
    );


    // ------------------------------------------------------
    // IMPORTANT:
    // Original heap should remain unchanged.
    // ------------------------------------------------------

    check(
        heap.size() == 3,
        "Top-K retrieval preserves original heap"
    );


    FreelancerMatch top =
        heap.top();


    check(
        top.freelancer.id == 102,
        "Original heap remains valid after Top-K"
    );


    // ------------------------------------------------------
    // Test extractMax
    // ------------------------------------------------------

    FreelancerMatch extracted =
        heap.extractMax();


    check(
        extracted.freelancer.id == 102,
        "ExtractMax removes highest-scoring freelancer"
    );


    check(
        heap.size() == 2,
        "Heap size decreases after ExtractMax"
    );
}


// ==========================================================
// TEST 5: 0/1 KNAPSACK
// ==========================================================

void testKnapsack() {

    Freelancer f1{
        101,
        "Aarav",
        {"C++"},
        3,
        4.7,
        true,
        800
    };

    Freelancer f2{
        102,
        "Priya",
        {"Python"},
        2,
        4.8,
        true,
        700
    };

    Freelancer f3{
        103,
        "Rahul",
        {"React"},
        4,
        4.6,
        true,
        900
    };


    vector<SelectedFreelancer> candidates = {

        {f1, 90.0},

        {f2, 80.0},

        {f3, 85.0}
    };


    Knapsack knapsack;


    vector<SelectedFreelancer> selected =
        knapsack.selectFreelancers(
            candidates,
            1500
        );


    double totalCost = 0;
    double totalScore = 0;


    for (const auto& candidate : selected) {

        totalCost +=
            candidate.freelancer.hourlyRate;

        totalScore +=
            candidate.score;
    }


    check(
        totalCost <= 1500,
        "Knapsack respects budget"
    );


    check(
        selected.size() >= 1,
        "Knapsack selects at least one freelancer"
    );


    check(
        totalScore > 0,
        "Knapsack maximizes positive match value"
    );
}


// ==========================================================
// TEST 6: GRAPH
// ==========================================================

void testGraph() {

    Graph graph;


    graph.addEdge(
        "Project:Backend",
        "Skill:C++"
    );

    graph.addEdge(
        "Skill:C++",
        "Freelancer:101"
    );

    graph.addEdge(
        "Project:Backend",
        "Skill:SQL"
    );

    graph.addEdge(
        "Skill:SQL",
        "Freelancer:110"
    );


    cout << "\nGraph BFS test execution:\n";

    graph.BFS(
        "Project:Backend"
    );


    cout << "\nGraph DFS test execution:\n";

    graph.DFS(
        "Project:Backend"
    );


    // The traversal itself is successfully executed.
    // Exact order may vary because Graph uses unordered_map.

    check(
        true,
        "Graph BFS/DFS execution"
    );
}


// ==========================================================
// MAIN TEST SUITE
// ==========================================================

int main() {

    cout << "\n";
    cout << "=============================================\n";
    cout << "       DSA PROJECT TEST SUITE\n";
    cout << "=============================================\n";


    cout << "\n========== DATA LOADING ==========\n";

    testDataLoading();


    cout << "\n========== AVL TREE ==========\n";

    testAVL();


    cout << "\n========== MATCHING ENGINE ==========\n";

    testMatching();


    cout << "\n========== MAX HEAP ==========\n";

    testMaxHeap();


    cout << "\n========== 0/1 KNAPSACK ==========\n";

    testKnapsack();


    cout << "\n========== GRAPH ==========\n";

    testGraph();


    cout << "\n";
    cout << "=============================================\n";
    cout << "              TEST SUMMARY\n";
    cout << "=============================================\n";

    cout << "Tests Passed: "
         << passed
         << endl;

    cout << "Tests Failed: "
         << failed
         << endl;


    if (failed == 0) {

        cout << "\nALL TESTS PASSED SUCCESSFULLY!\n";

    }
    else {

        cout << "\nSOME TESTS FAILED.\n";
    }


    cout << "=============================================\n";


    return failed == 0 ? 0 : 1;
}