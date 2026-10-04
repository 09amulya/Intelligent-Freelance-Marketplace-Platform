#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "../models/Freelancer.h"

#include <iostream>

using namespace std;

class AVLTree {

private:

    struct Node {

        Freelancer freelancer;

        Node* left;
        Node* right;

        int height;


        Node(const Freelancer& freelancer)
            : freelancer(freelancer),
              left(nullptr),
              right(nullptr),
              height(1) {}
    };


    Node* root = nullptr;


    // ======================================================
    // HEIGHT
    // ======================================================

    int height(Node* node) const {

        if (node == nullptr) {
            return 0;
        }

        return node->height;
    }


    // ======================================================
    // MAX VALUE
    // ======================================================

    int maxValue(
        int a,
        int b
    ) const {

        return (a > b)
            ? a
            : b;
    }


    // ======================================================
    // BALANCE FACTOR
    // ======================================================

    int getBalance(Node* node) const {

        if (node == nullptr) {
            return 0;
        }

        return height(node->left)
             - height(node->right);
    }


    // ======================================================
    // RIGHT ROTATION
    // ======================================================

    Node* rightRotate(Node* y) {

        Node* x =
            y->left;

        Node* T2 =
            x->right;


        x->right = y;

        y->left = T2;


        y->height =
            1 +
            maxValue(
                height(y->left),
                height(y->right)
            );


        x->height =
            1 +
            maxValue(
                height(x->left),
                height(x->right)
            );


        return x;
    }


    // ======================================================
    // LEFT ROTATION
    // ======================================================

    Node* leftRotate(Node* x) {

        Node* y =
            x->right;

        Node* T2 =
            y->left;


        y->left = x;

        x->right = T2;


        x->height =
            1 +
            maxValue(
                height(x->left),
                height(x->right)
            );


        y->height =
            1 +
            maxValue(
                height(y->left),
                height(y->right)
            );


        return y;
    }


    // ======================================================
    // INSERT
    // ======================================================

    Node* insert(
        Node* node,
        const Freelancer& freelancer
    ) {

        // Empty position
        if (node == nullptr) {

            return new Node(
                freelancer
            );
        }


        // Go left
        if (
            freelancer.id <
            node->freelancer.id
        ) {

            node->left =
                insert(
                    node->left,
                    freelancer
                );
        }


        // Go right
        else if (
            freelancer.id >
            node->freelancer.id
        ) {

            node->right =
                insert(
                    node->right,
                    freelancer
                );
        }


        // Duplicate ID
        else {

            return node;
        }


        // Update height
        node->height =
            1 +
            maxValue(
                height(node->left),
                height(node->right)
            );


        // Calculate balance
        int balance =
            getBalance(node);


        // ==================================================
        // LL CASE
        // ==================================================

        if (
            balance > 1 &&
            freelancer.id <
            node->left->freelancer.id
        ) {

            return rightRotate(node);
        }


        // ==================================================
        // RR CASE
        // ==================================================

        if (
            balance < -1 &&
            freelancer.id >
            node->right->freelancer.id
        ) {

            return leftRotate(node);
        }


        // ==================================================
        // LR CASE
        // ==================================================

        if (
            balance > 1 &&
            freelancer.id >
            node->left->freelancer.id
        ) {

            node->left =
                leftRotate(
                    node->left
                );

            return rightRotate(node);
        }


        // ==================================================
        // RL CASE
        // ==================================================

        if (
            balance < -1 &&
            freelancer.id <
            node->right->freelancer.id
        ) {

            node->right =
                rightRotate(
                    node->right
                );

            return leftRotate(node);
        }


        return node;
    }


    // ======================================================
    // SEARCH
    // ======================================================

    Node* search(
        Node* node,
        int id
    ) const {

        if (
            node == nullptr ||
            node->freelancer.id == id
        ) {

            return node;
        }


        if (
            id <
            node->freelancer.id
        ) {

            return search(
                node->left,
                id
            );
        }


        return search(
            node->right,
            id
        );
    }


    // ======================================================
    // INORDER TRAVERSAL
    // ======================================================

    void inorder(Node* node) const {

        if (node == nullptr) {
            return;
        }


        inorder(node->left);


        cout << "ID: "
             << node->freelancer.id

             << " | Name: "
             << node->freelancer.name

             << " | Experience: "
             << node->freelancer.experience
             << " years"

             << endl;


        inorder(node->right);
    }


    // ======================================================
    // DELETE ALL NODES
    // ======================================================

    void clear(Node* node) {

        if (node == nullptr) {
            return;
        }


        clear(node->left);

        clear(node->right);


        delete node;
    }


public:


    // ======================================================
    // DESTRUCTOR
    // ======================================================

    ~AVLTree() {

        clear(root);

        root = nullptr;
    }


    // ======================================================
    // PUBLIC INSERT
    // ======================================================

    void insert(
        const Freelancer& freelancer
    ) {

        root =
            insert(
                root,
                freelancer
            );
    }


    // ======================================================
    // PUBLIC SEARCH
    // ======================================================

    Freelancer* search(
        int id
    ) {

        Node* result =
            search(
                root,
                id
            );


        if (result == nullptr) {

            return nullptr;
        }


        return &result->freelancer;
    }


    // ======================================================
    // DISPLAY INORDER
    // ======================================================

    void displayInorder() const {

        cout << "\n--- AVL Tree Inorder Traversal ---\n";

        inorder(root);
    }
};

#endif