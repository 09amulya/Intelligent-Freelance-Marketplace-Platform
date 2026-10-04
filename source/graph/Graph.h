#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

class Graph {

private:

    // Adjacency List
    unordered_map<string, vector<string>> adjList;

public:

    // Add a vertex
    void addVertex(const string& vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = {};
        }
    }

    // Add an undirected relationship
    void addEdge(
        const string& u,
        const string& v
    ) {

        addVertex(u);
        addVertex(v);

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // BFS traversal
    void BFS(const string& start) {

        if (adjList.find(start) == adjList.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        unordered_set<string> visited;
        queue<string> q;

        visited.insert(start);
        q.push(start);

        cout << "\nBFS Traversal: ";

        while (!q.empty()) {

            string current = q.front();
            q.pop();

            cout << current << " ";

            for (const string& neighbour : adjList[current]) {

                if (visited.find(neighbour) == visited.end()) {

                    visited.insert(neighbour);
                    q.push(neighbour);
                }
            }
        }

        cout << endl;
    }

private:

    void DFSUtil(
        const string& vertex,
        unordered_set<string>& visited
    ) {

        visited.insert(vertex);

        cout << vertex << " ";

        for (const string& neighbour : adjList[vertex]) {

            if (visited.find(neighbour) == visited.end()) {

                DFSUtil(neighbour, visited);
            }
        }
    }

public:

    // DFS traversal
    void DFS(const string& start) {

        if (adjList.find(start) == adjList.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        unordered_set<string> visited;

        cout << "\nDFS Traversal: ";

        DFSUtil(start, visited);

        cout << endl;
    }

    // Display graph
    void displayGraph() {

        cout << "\n========== MARKETPLACE GRAPH ==========\n";

        for (const auto& pair : adjList) {

            cout << pair.first << " -> ";

            for (const string& neighbour : pair.second) {
                cout << neighbour << " ";
            }

            cout << endl;
        }
    }
};

#endif