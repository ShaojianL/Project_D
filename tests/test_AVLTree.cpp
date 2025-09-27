#include <iostream>
#include "/Users/wilsonliang/Project_D/Core/Source/Core/AVLTree.h"

int main() {
    Core::AVLTree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");

    std::string value;
    if (tree.search(2, value)) {
        std::cout << "Found: " << value << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    tree.printInorder();
    return 0;
}