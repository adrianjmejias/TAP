#include <iostream>
#include "fibonacci_heap.hpp"

int main()
{
	{
		using namespace fibonacci;

		Heap<int> h([](int a, int b){return b - a;});

		if (h.root == nullptr)
		{
			std::cout << "h is null\n";
		}
	}
	std::cout << "Hello Easy C++ project!" << std::endl;
}