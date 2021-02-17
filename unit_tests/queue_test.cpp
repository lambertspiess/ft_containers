#include <string>
#include <iostream>
#include <random>
#include <queue>
#include "../queue.hpp"
#include "test.hpp"

int main()
{
	{
		title("Constructor test");
		blue("ft::queue<int> m;");
		ft::queue<int> m;
		yellow("std::queue<int> o;");
		std::queue<int> o;

		title("push and front back test");
		blue("ft stack");
		for (int i = 0; i < 10; i++)
		{
			m.push(i);
			std::cout << "m.front(): "<< m.front() << " " << "m.back(): " << m.back();
			std::cout << std::endl;
		}

		cyan("==================");
		yellow("std stack");
		for (int i = 0; i < 10; i++)
		{
			o.push(i);
			std::cout << "o.front(): "<< o.front() << " " << "o.back(): " << o.back();
			std::cout << std::endl;
		}
		title("size test");
		std::cout << "m.size(): " << m.size() << std::endl;
		std::cout << "o.size(): " << o.size() << std::endl;

		title("pop test");
		blue("ft stack");
		for(int i = 0;i < 5; i++)
		{
			m.pop();
			std::cout << "m.front(): "<< m.front() << " " << "m.back(): " << m.back();
			std::cout << std::endl;
		}
		cyan("==================");
		yellow("std stack");
		for (int i = 0; i < 5; i++)
		{
			o.pop();
			std::cout << "o.front(): "<< o.front() << " " << "o.back(): " << o.back();
			std::cout << std::endl;
		}

		title("empty test");
		blue("if m.empty()");
		if (m.empty())
			std::cout << "empty" << std::endl;
		else
			std::cout << "not empty" << std::endl;
		yellow("if o.empty()");
		if (o.empty())
			std::cout << "empty" << std::endl;
		else
			std::cout << "not empty" << std::endl;
	}
}
