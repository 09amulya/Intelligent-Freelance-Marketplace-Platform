#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "../models/Freelancer.h"

#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;


// ==========================================================
// FREELANCER MATCH
// ==========================================================

struct FreelancerMatch {

    Freelancer freelancer;
    double score;
};


// ==========================================================
// MAX HEAP
// ==========================================================

class MaxHeap {

private:

    vector<FreelancerMatch> heap;


    // ------------------------------------------------------
    // HEAPIFY UP
    // ------------------------------------------------------

    void heapifyUp(int index) {

        while (index > 0) {

            int parent =
                (index - 1) / 2;


            if (heap[parent].score >=
                heap[index].score) {

                break;
            }


            swap(
                heap[parent],
                heap[index]
            );


            index = parent;
        }
    }


    // ------------------------------------------------------
    // HEAPIFY DOWN
    // ------------------------------------------------------

    void heapifyDown(int index) {

        int n = heap.size();


        while (true) {

            int left =
                2 * index + 1;

            int right =
                2 * index + 2;

            int largest =
                index;


            if (
                left < n &&
                heap[left].score >
                heap[largest].score
            ) {

                largest = left;
            }


            if (
                right < n &&
                heap[right].score >
                heap[largest].score
            ) {

                largest = right;
            }


            if (largest == index) {

                break;
            }


            swap(
                heap[index],
                heap[largest]
            );


            index = largest;
        }
    }


public:


    // ======================================================
    // INSERT
    // ======================================================

    void insert(
        const Freelancer& freelancer,
        double score
    ) {

        FreelancerMatch match{
            freelancer,
            score
        };


        heap.push_back(match);


        heapifyUp(
            heap.size() - 1
        );
    }


    // ======================================================
    // EMPTY
    // ======================================================

    bool empty() const {

        return heap.empty();
    }


    // ======================================================
    // SIZE
    // ======================================================

    int size() const {

        return static_cast<int>(
            heap.size()
        );
    }


    // ======================================================
    // TOP
    // ======================================================

    FreelancerMatch top() const {

        if (heap.empty()) {

            throw runtime_error(
                "Heap is empty."
            );
        }


        return heap[0];
    }


    // ======================================================
    // EXTRACT MAX
    // ======================================================

    FreelancerMatch extractMax() {

        if (heap.empty()) {

            throw runtime_error(
                "Heap is empty."
            );
        }


        FreelancerMatch result =
            heap[0];


        heap[0] =
            heap.back();


        heap.pop_back();


        if (!heap.empty()) {

            heapifyDown(0);
        }


        return result;
    }


    // ======================================================
    // GET TOP K
    //
    // IMPORTANT:
    // This method does NOT destroy the original heap.
    // ======================================================

    vector<FreelancerMatch> getTopK(
        int k
    ) const {

        vector<FreelancerMatch> result;


        if (k <= 0 ||
            heap.empty()) {

            return result;
        }


        // Make a copy of the heap.
        MaxHeap temporaryHeap;

        temporaryHeap.heap =
            heap;


        int count =
            min(
                k,
                static_cast<int>(
                    temporaryHeap.heap.size()
                )
            );


        for (int i = 0;
             i < count;
             i++) {

            result.push_back(
                temporaryHeap.extractMax()
            );
        }


        return result;
    }


    // ======================================================
    // DISPLAY TOP K
    // ======================================================

    void displayTopK(
        int k
    ) const {

        vector<FreelancerMatch> topMatches =
            getTopK(k);


        cout << "\n===== TOP "
             << topMatches.size()
             << " FREELANCER RECOMMENDATIONS =====\n";


        for (
            int i = 0;
            i < static_cast<int>(
                    topMatches.size()
                );
            i++
        ) {

            const FreelancerMatch& match =
                topMatches[i];


            cout << "\nRank: "
                 << i + 1
                 << endl;


            cout << "Freelancer ID: "
                 << match.freelancer.id
                 << endl;


            cout << "Name: "
                 << match.freelancer.name
                 << endl;


            cout << "Match Score: "
                 << match.score
                 << endl;


            cout << "Rating: "
                 << match.freelancer.rating
                 << endl;


            cout << "Experience: "
                 << match.freelancer.experience
                 << " years"
                 << endl;


            cout << "Hourly Rate: Rs. "
                 << match.freelancer.hourlyRate
                 << endl;
        }
    }
};

#endif