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

    // Get height of a node
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        return node->height;
    }

    // Get maximum of two values
    int maxValue(int a, int b) {
        return (a > b) ? a : b;
    }

    // Calculate balance factor
    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        return height(node->left) - height(node->right);
    }

    // Right rotation - LL case
    Node* rightRotate(Node* y) {

        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height =
            1 + maxValue(height(y->left), height(y->right));

        x->height =
            1 + maxValue(height(x->left), height(x->right));

        return x;
    }

    // Left rotation - RR case
    Node* leftRotate(Node* x) {

        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height =
            1 + maxValue(height(x->left), height(x->right));

        y->height =
            1 + maxValue(height(y->left), height(y->right));

        return y;
    }

    // Insert freelancer into AVL tree
    Node* insert(Node* node, const Freelancer& freelancer) {

        // Normal BST insertion
        if (node == nullptr) {
            return new Node(freelancer);
        }

        if (freelancer.id < node->freelancer.id) {

            node->left =
                insert(node->left, freelancer);

        }
        else if (freelancer.id > node->freelancer.id) {

            node->right =
                insert(node->right, freelancer);

        }
        else {
            // Duplicate ID not allowed
            return node;
        }

        // Update height
        node->height =
            1 + maxValue(
                height(node->left),
                height(node->right)
            );

        // Check balance
        int balance = getBalance(node);

        // LL Case
        if (balance > 1 &&
            freelancer.id < node->left->freelancer.id) {

            return rightRotate(node);
        }

        // RR Case
        if (balance < -1 &&
            freelancer.id > node->right->freelancer.id) {

            return leftRotate(node);
        }

        // LR Case
        if (balance > 1 &&
            freelancer.id > node->left->freelancer.id) {

            node->left = leftRotate(node->left);

            return rightRotate(node);
        }

        // RL Case
        if (balance < -1 &&
            freelancer.id < node->right->freelancer.id) {

            node->right = rightRotate(node->right);

            return leftRotate(node);
        }

        return node;
    }

    // Search freelancer by ID
    Node* search(Node* node, int id) {

        if (node == nullptr ||
            node->freelancer.id == id) {

            return node;
        }

        if (id < node->freelancer.id) {
            return search(node->left, id);
        }

        return search(node->right, id);
    }

    // Inorder traversal
    void inorder(Node* node) {

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

public:

    // Insert a freelancer
    void insert(const Freelancer& freelancer) {
        root = insert(root, freelancer);
    }

    // Search freelancer
    Freelancer* search(int id) {

        Node* result = search(root, id);

        if (result == nullptr) {
            return nullptr;
        }

        return &result->freelancer;
    }

    // Display freelancers in sorted order
    void displayInorder() {
        cout << "\n--- AVL Tree Inorder Traversal ---\n";

        inorder(root);
    }

};

#endif