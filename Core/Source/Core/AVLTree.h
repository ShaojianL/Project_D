#pragma once

#include <iostream>
#include <algorithm>

namespace Core {

    template<typename Key, typename Value>
    class AVLTree {
    private:
        struct Node {
            Key key;
            Value value;
            Node* left;
            Node* right;
            int height;

            Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
        };

        Node* root;

        // Helper functions - declarations only
        int getHeight(Node* node);
        int getBalance(Node* node);
        void updateHeight(Node* node);

        // Rotation functions - declarations only
        Node* rotateRight(Node* y);
        Node* rotateLeft(Node* x);

        // Recursive helper functions - declarations only
        Node* insertHelper(Node* node, Key key, Value value);
        Node* searchHelper(Node* node, Key key);
        void inorderHelper(Node* node);
        void clearHelper(Node* node);

    public:
        // Constructor and Destructor
        AVLTree();
        ~AVLTree();

        // Copy constructor and assignment operator
        AVLTree(const AVLTree& other);
        AVLTree& operator=(const AVLTree& other);

        // Public interface
        void insert(Key key, Value value);
        bool search(Key key, Value& value);
        bool contains(Key key);
        void printInorder();
        int getHeight();
        void clear();
        bool empty() const;
    };

} // namespace Core

// Include the implementation
#include "AVLTree.cpp"