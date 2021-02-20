#include "../queue.hpp"
#include <queue>
#include "utils.hpp"

int main()
{
	{
		//---------------------------------------------------------------------
		highlight("Constructor : default");
		cyannl("ft::queue<int> my;");
		ft::queue<int> my;
		purplenl("std::queue<int> ori;");
		std::queue<int> ori;
		//---------------------------------------------------------------------
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
		//---------------------------------------------------------------------
		highlight("Method : push");
		cyannl("for (int i = 1; i <= 42; i++) { my.push(i); }");
		for (int i = 1; i <= 42; i++) { my.push(i); }
		std::cout << "my.front() : " << my.front() << "\n";
		std::cout << "my.back() : " << my.back() << "\n";
		std::cout << "my.size() : " << my.size() << "\n";
		purplenl("for (int i = 1; i <= 42; i++) { ori.push(i); }");
		for (int i = 1; i <= 42; i++) { ori.push(i); }
		std::cout << "ori.front() : " << ori.front() << "\n";
		std::cout << "ori.back() : " << ori.back() << "\n";
		std::cout << "ori.size() : " << ori.size() << "\n";
		//---------------------------------------------------------------------
		highlight("Method : pop");
		cyannl("for (int i = 0; i < 21; i++) { my.pop(i); }");
		for (int i = 0; i < 21; i++) { my.pop(); }
		std::cout << "my.front() : " << my.front() << "\n";
		std::cout << "my.back() : " << my.back() << "\n";
		std::cout << "my.size() : " << my.size() << "\n";
		purplenl("for (int i = 0; i < 21; i++) { ori.pop(i); }");
		for (int i = 0; i < 21; i++) { ori.pop(); }
		std::cout << "ori.front() : " << ori.front() << "\n";
		std::cout << "ori.back() : " << ori.back() << "\n";
		std::cout << "ori.size() : " << ori.size() << "\n";
		//---------------------------------------------------------------------
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
