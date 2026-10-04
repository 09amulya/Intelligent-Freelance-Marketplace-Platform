#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "../models/Freelancer.h"
#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;

struct FreelancerMatch {
    Freelancer freelancer;
    double score;
};

class MaxHeap {

private:

    vector<FreelancerMatch> heap;

    // Move a node upward
    void heapifyUp(int index) {

        while (index > 0) {

            int parent = (index - 1) / 2;

            if (heap[parent].score >= heap[index].score) {
                break;
            }

            swap(heap[parent], heap[index]);

            index = parent;
        }
    }

    // Move a node downward
    void heapifyDown(int index) {

        int n = heap.size();

        while (true) {

            int left = 2 * index + 1;
            int right = 2 * index + 2;

            int largest = index;

            if (left < n &&
                heap[left].score > heap[largest].score) {

                largest = left;
            }

            if (right < n &&
                heap[right].score > heap[largest].score) {

                largest = right;
            }

            if (largest == index) {
                break;
            }

            swap(heap[index], heap[largest]);

            index = largest;
        }
    }

public:

    // Insert a freelancer with match score
    void insert(
        const Freelancer& freelancer,
        double score
    ) {

        FreelancerMatch match{
            freelancer,
            score
        };

        heap.push_back(match);

        heapifyUp(heap.size() - 1);
    }


    // Check whether heap is empty
    bool empty() const {
        return heap.empty();
    }


    // Get highest scoring freelancer
    FreelancerMatch top() const {

        if (heap.empty()) {
            throw runtime_error("Heap is empty.");
        }

        return heap[0];
    }


    // Remove and return highest scoring freelancer
    FreelancerMatch extractMax() {

        if (heap.empty()) {
            throw runtime_error("Heap is empty.");
        }

        FreelancerMatch result = heap[0];

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            heapifyDown(0);
        }

        return result;
    }


    // Display top K freelancers
    void displayTopK(int k) {

        cout << "\n===== TOP "
             << k
             << " FREELANCER RECOMMENDATIONS =====\n";

        int count = 0;

        while (!heap.empty() && count < k) {

            FreelancerMatch match = extractMax();

            cout << "\nRank: "
                 << count + 1 << endl;

            cout << "Freelancer ID: "
                 << match.freelancer.id << endl;

            cout << "Name: "
                 << match.freelancer.name << endl;

            cout << "Match Score: "
                 << match.score << endl;

            cout << "Rating: "
                 << match.freelancer.rating << endl;

            cout << "Experience: "
                 << match.freelancer.experience
                 << " years" << endl;

            cout << "Hourly Rate: Rs. "
                 << match.freelancer.hourlyRate
                 << endl;

            count++;
        }
    }
};

#endif