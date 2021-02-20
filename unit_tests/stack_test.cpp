#include "../stack.hpp"
#include <stack>
#include "utils.hpp"

int main()
{
	{
		//--------------------------------------------------------------------
		highlight("Constructor : default");
		cyannl("ft::stack<int> my");
		ft::stack<int> my;
		purplenl("std::stack<int> ori");
		std::stack<int> ori;
		//--------------------------------------------------------------------
		highlight("Method : size");
		cyannl("my.size()");
		std::cout  << my.size() << "\n";
		purplenl("ori.size()");
		std::cout  << ori.size() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : empty");
		cyannl("my.empty()");
		if (my.empty() == true)
			std::cout << "empty" << "\n";
		else
			std::cout << "not empty" << "\n";
		purplenl("ori.empty()");
		if (ori.empty() == true)
			std::cout << "empty" << "\n";
		else
			std::cout << "not empty" << "\n";
		//--------------------------------------------------------------------
		highlight("Method : push");
		cyannl("for (int i = 1; i <= 42; ++i) { my.push(i); }");
		for (int i = 1; i <= 42; ++i) { my.push(i); }
		cyannl("my.top()");
		std::cout << my.top() << "\n";
		cyannl("my.size()");
		std::cout  << my.size() << "\n";
		purplenl("for (int i = 1; i <= 42; ++i) { ori.push(i); }");
		for (int i = 1; i <= 42; ++i) { ori.push(i); }
		purplenl("ori.top()");
		std::cout << ori.top() << "\n";
		purplenl("ori.size()");
		std::cout  << ori.size() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : pop");
		cyannl("for (int i = 1; i <= 21; ++i) { my.pop(); }");
		for (int i = 1; i <= 21; ++i) { my.pop(); }
		cyannl("my.top()");
		std::cout << my.top() << "\n";
		cyannl("my.size()");
		std::cout  << my.size() << "\n";
		cyannl("for (int i = 1; i <= 21; ++i) { ori.pop(); }");
		for (int i = 1; i <= 21; ++i) { ori.pop(); }
		purplenl("ori.top()");
		std::cout << ori.top() << "\n";
		purplenl("ori.size()");
		std::cout  << ori.size() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : pop");
		cyannl("for (int i = 1; i <= 21; ++i) { my.pop(); }");
		for (int i = 1; i <= 21; ++i) { my.pop(); }
		cyannl("my.size()");
		std::cout  << my.size() << "\n";
		cyannl("for (int i = 1; i <= 21; ++i) { ori.pop(); }");
		for (int i = 1; i <= 21; ++i) { ori.pop(); }
		purplenl("ori.size()");
		std::cout  << ori.size() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : empty");
		cyannl("my.empty()");
		if (my.empty() == true)
			std::cout << "empty" << "\n";
		else
			std::cout << "not empty" << "\n";
		purplenl("ori.empty()");
		if (ori.empty() == true)
			std::cout << "empty" << "\n";
		else
			std::cout << "not empty" << "\n";
	}
}
