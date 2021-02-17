#include <string>
#include <iostream>
#include <random>
#include <stack>
#include "test.hpp"
#include "../stack.hpp"

int main()
{
	{
		title("Constructor test");
		blue("ft::stack<int> m;");
		ft::stack<int> m;
		yellow("std::stack<int> o;");
		std::stack<int> o;

		title("push and top test");
		for (int i = 0; i < 10; i++)
		{
			m.push(i);
			std::cout << "m.top(): "<< m.top();
			std::cout << std::endl;
		}
		std::cout << std::endl;

		for (int i = 0; i < 10; i++)
		{
			o.push(i);
			std::cout << o.top() << " ";
		}
		std::cout << std::endl;

		title("size test");
		std::cout << "m.size(): " << m.size() << std::endl;
		std::cout << "o.size(): " << o.size() << std::endl;

		title("pop test");
		blue("m.top() after pop");
		m.pop();
		std::cout << "m.top(): " << m.top() << std::endl;

		yellow("o.top() after pop");
		o.pop();
		std::cout << "o.top(): " << o.top() << std::endl;

	}
}
