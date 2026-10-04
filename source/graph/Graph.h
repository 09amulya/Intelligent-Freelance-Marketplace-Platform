#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Graph {

private:

    // Adjacency List
    unordered_map<int, vector<int>> adjList;

public:

    // Add a vertex
    void addVertex(int vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = {};
        }
    }

    // Add an undirected edge
    void addEdge(int u, int v) {

        addVertex(u);
        addVertex(v);

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // BFS traversal
    void BFS(int start) {

        if (adjList.find(start) == adjList.end()) {
            cout << "Starting vertex not found.\n";
            return;
        }

        unordered_set<int> visited;
        queue<int> q;

        visited.insert(start);
        q.push(start);

        cout << "BFS: ";

        while (!q.empty()) {

            int current = q.front();
            q.pop();

            cout << current << " ";

            for (int neighbour : adjList[current]) {

                if (visited.find(neighbour) == visited.end()) {

                    visited.insert(neighbour);
                    q.push(neighbour);
                }
            }
        }

        cout << endl;
    }

private:

    // DFS helper
    void DFSUtil(
        int vertex,
        unordered_set<int>& visited
    ) {

        visited.insert(vertex);

        cout << vertex << " ";

        for (int neighbour : adjList[vertex]) {

            if (visited.find(neighbour) == visited.end()) {

                DFSUtil(neighbour, visited);
            }
        }
    }

public:

    // DFS traversal
    void DFS(int start) {

        if (adjList.find(start) == adjList.end()) {
            cout << "Starting vertex not found.\n";
            return;
        }

        unordered_set<int> visited;

        cout << "DFS: ";

        DFSUtil(start, visited);

        cout << endl;
    }

    // Display adjacency list
    void displayGraph() {

        cout << "\n--- Adjacency List ---\n";

        for (const auto& pair : adjList) {

            cout << pair.first << " -> ";

            for (int neighbour : pair.second) {
                cout << neighbour << " ";
            }

            cout << endl;
        }
    }
};

#endif