#include <iostream>
#include "Core/Core.h"

int main()
{
	Core::PrintHelloWorld();
	
	std::cout << "\nPress Enter to exit...";
	std::cin.get();
}