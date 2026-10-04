#include <iostream>

#include "models/Freelancer.h"
#include "trees/AVLTree.h"
#include "graph/Graph.h"
#include "algorithm/Matching.h"

using namespace std;

int main() {

    // =========================
    // AVL TREE
    // =========================

    AVLTree freelancerTree;

    Freelancer f1{
        105,
        "Arjun",
        {"C++", "Java", "DSA"},
        5,
        4.9,
        true,
        1000
    };

    Freelancer f2{
        102,
        "Priya",
        {"Python", "SQL", "ML"},
        2,
        4.8,
        true,
        700
    };

    Freelancer f3{
        108,
        "Rahul",
        {"React", "Node.js", "MongoDB"},
        4,
        4.6,
        true,
        900
    };

    Freelancer f4{
        101,
        "Aarav",
        {"C++", "SQL", "DSA"},
        3,
        4.7,
        true,
        800
    };

    Freelancer f5{
        110,
        "Meera",
        {"Python", "SQL", "Data Analysis"},
        5,
        4.9,
        true,
        900
    };

    freelancerTree.insert(f1);
    freelancerTree.insert(f2);
    freelancerTree.insert(f3);
    freelancerTree.insert(f4);
    freelancerTree.insert(f5);

    freelancerTree.displayInorder();


    // =========================
    // GRAPH
    // =========================

    Graph graph;

    /*
        Freelancer IDs:

        101 -> Aarav
        102 -> Priya
        105 -> Arjun
        108 -> Rahul
        110 -> Meera

        Connections represent shared
        skills / relationships.
    */

    graph.addEdge(101, 102);
    graph.addEdge(101, 105);
    graph.addEdge(102, 110);
    graph.addEdge(105, 108);
    graph.addEdge(108, 110);

    graph.displayGraph();

    cout << endl;

    graph.BFS(101);

    graph.DFS(101);



    // =========================
// MATCHING ENGINE
// =========================

MatchingEngine matcher;

vector<string> requiredSkills = {
    "C++",
    "SQL",
    "DSA"
};

double projectBudget = 900;

cout << "\n\n===== FREELANCER MATCHING =====\n";

matcher.displayMatchScore(
    f1,
    requiredSkills,
    projectBudget
);

matcher.displayMatchScore(
    f2,
    requiredSkills,
    projectBudget
);

matcher.displayMatchScore(
    f3,
    requiredSkills,
    projectBudget
);

matcher.displayMatchScore(
    f4,
    requiredSkills,
    projectBudget
);

matcher.displayMatchScore(
    f5,
    requiredSkills,
    projectBudget
);


    return 0;
}