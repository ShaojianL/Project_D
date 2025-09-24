#include "Core.h"

#include <iostream>

namespace Core {

	void PrintHelloWorld()
	{
		std::cout << "Hello World!\n";
	}

	void DemonstrateAVLTree()
	{
		std::cout << "\n=== AVL Tree Demonstration ===\n";
		
		// Create an AVL tree with int keys and int values
		AVLTree<int, int> tree;
		
		std::cout << "Inserting elements: 5, 10, 3, 8, 2, 1\n";
		
		// Insert elements as requested
		tree.insert(5, 0);
		tree.insert(10, 1);
		tree.insert(3, 2);
		tree.insert(8, 3);
		tree.insert(2, 4);
		tree.insert(1, 5);
		
		// Print the tree
		tree.printInorder();
		std::cout << "Tree height: " << tree.getHeight() << std::endl;
		
		// Demonstrate search functionality
		std::cout << "\nSearching for key 5: ";
		int value;
		if (tree.search(5, value)) {
			std::cout << "Found! Value: " << value << std::endl;
		} else {
			std::cout << "Not found!" << std::endl;
		}
		
		std::cout << "Searching for key 7: ";
		if (tree.search(7, value)) {
			std::cout << "Found! Value: " << value << std::endl;
		} else {
			std::cout << "Not found!" << std::endl;
		}
		
		// Demonstrate contains function
		std::cout << "Does tree contain key 3? " << (tree.contains(3) ? "Yes" : "No") << std::endl;
		std::cout << "Does tree contain key 99? " << (tree.contains(99) ? "Yes" : "No") << std::endl;
		
		std::cout << "=== End AVL Tree Demonstration ===\n";
	}

}