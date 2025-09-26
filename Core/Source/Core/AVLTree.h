#pragma once
#include<iostream>
#include<algorithm>

namespace Core {

    template<typename Key, typename Value> class AVLTree {
    private:
        struct Node
        {
            /* data */
            Key key;
            Value value;
            Node* left;
            Node* right;
            int height;
            // Initialization list
            Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}

        };

        Node* root;
        
        
        int getHeight(Node* node);
        int getBalance(Node* node);
        void updateHeight(Node* node);
        
        // Recursive helper
        Node* insertHelper(Node* node, Key key, Value value);
        Node* searchHelper(Node* node, Key key);
        void inorderHelper(Node* node);
        void clearHelper(Node* node);

        // Rotation
        Node* rotateRight(Node* node);
        Node* rotateLeft(Node* node);

        public:
        // constructor and destructor
        AVLTree();
        ~AVLTree();

        // Copy constructor and assignment operator
        AVLTree(const AVLTree& other);
        AVLTree& operator=(const AVLTree& other);

        // API
        void insert(Key key, Value value);
        bool search(Key key, Value& value);
        bool contains(Key key);
        void printInorder();
        int getHeight();
        void clear();
        bool empty() const;
        
    };
} // namespace Core

// Include the implementation cpp
#include"AVLTree.cpp"