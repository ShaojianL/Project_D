// AVLTree.cpp - Template implementation file
// This file contains the implementation of AVLTree template methods

#include "AVLTree.h"

namespace Core {

    // Helper functions implementation
    template<typename Key, typename Value>
    int AVLTree<Key, Value>::getHeight(Node* node) {
        return node ? node->height : 0;
    }

    template<typename Key, typename Value>
    int AVLTree<Key, Value>::getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    template<typename Key, typename Value>
    void AVLTree<Key, Value>::updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    // Rotation functions implementation
    template<typename Key, typename Value>
    typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    template<typename Key, typename Value>
    typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Constructor and Destructor implementation
    template<typename Key, typename Value>
    AVLTree<Key, Value>::AVLTree() : root(nullptr) {}

    template<typename Key, typename Value>
    AVLTree<Key, Value>::~AVLTree() {
        clear();
    }

    // Copy constructor and assignment operator implementation
    template<typename Key, typename Value>
    AVLTree<Key, Value>::AVLTree(const AVLTree& other) : root(nullptr) {
        // TODO: Implement deep copy if needed
    }

    template<typename Key, typename Value>
    AVLTree<Key, Value>& AVLTree<Key, Value>::operator=(const AVLTree& other) {
        if (this != &other) {
            clear();
            // TODO: Implement deep copy if needed
        }
        return *this;
    }

    // Recursive insert function implementation
    template<typename Key, typename Value>
    typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::insertHelper(Node* node, Key key, Value value) {
        // 1. Perform normal BST insertion
        if (!node) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insertHelper(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key, value);
        } else {
            // Key already exists, update value
            node->value = value;
            return node;
        }

        // 2. Update height of this ancestor node
        updateHeight(node);

        // 3. Get the balance factor
        int balance = getBalance(node);

        // 4. If unbalanced, perform rotations

        // Left Left Case
        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Recursive search function implementation
    template<typename Key, typename Value>
    typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::searchHelper(Node* node, Key key) {
        if (!node || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return searchHelper(node->left, key);
        } else {
            return searchHelper(node->right, key);
        }
    }

    // Recursive inorder traversal for printing implementation
    template<typename Key, typename Value>
    void AVLTree<Key, Value>::inorderHelper(Node* node) {
        if (node) {
            inorderHelper(node->left);
            std::cout << "(" << node->key << ", " << node->value << ") ";
            inorderHelper(node->right);
        }
    }

    // Helper function to delete all nodes implementation
    template<typename Key, typename Value>
    void AVLTree<Key, Value>::clearHelper(Node* node) {
        if (node) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

    // Public interface implementation
    template<typename Key, typename Value>
    void AVLTree<Key, Value>::insert(Key key, Value value) {
        root = insertHelper(root, key, value);
    }

    template<typename Key, typename Value>
    bool AVLTree<Key, Value>::search(Key key, Value& value) {
        Node* node = searchHelper(root, key);
        if (node) {
            value = node->value;
            return true;
        }
        return false;
    }

    template<typename Key, typename Value>
    bool AVLTree<Key, Value>::contains(Key key) {
        return searchHelper(root, key) != nullptr;
    }

    template<typename Key, typename Value>
    void AVLTree<Key, Value>::printInorder() {
        std::cout << "AVL Tree (inorder): ";
        inorderHelper(root);
        std::cout << std::endl;
    }

    template<typename Key, typename Value>
    int AVLTree<Key, Value>::getHeight() {
        return getHeight(root);
    }

    template<typename Key, typename Value>
    void AVLTree<Key, Value>::clear() {
        clearHelper(root);
        root = nullptr;
    }

    template<typename Key, typename Value>
    bool AVLTree<Key, Value>::empty() const {
        return root == nullptr;
    }

} // namespace Core
