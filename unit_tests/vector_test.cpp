#include "../vector.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "utils.hpp"

template <class Cont>
void print_contnl(Cont & c)
{
	typename Cont::iterator itr = c.begin(), end = c.end();
	while (itr != end) { std::cout << *itr << ' '; ++itr; } std::cout << "\n";
//	std::cout << "size : " << c.size() << ", cap : " << c.capacity() << "\n";
}

int main(void)
{
	ft::vector<int> my_base;
	for (int i = 0; i < 10; ++i) { my_base.push_back(i); }
	std::vector<int> std_base;
	for (int i = 0; i < 10; ++i) { std_base.push_back(i); }

	{
		highlight("Constructor : empty");
		cyannl("ft::vector<int> my_empty");
		ft::vector<int> my_empty;
		print_contnl(my_empty);
	}

	{
		highlight("Constructor : insert val n times");
		cyannl("my(10, 42)");
		ft::vector<int> my(10, 421);
		print_contnl(my);
		purplenl("ori(10, 42)");
		std::vector<int> ori(10, 421);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Constructor : from a range of iterators");
		cyannl("ft::vector<int> my2(my.begin(), my.begin() + 6)");
		ft::vector<int> my2(my.begin(), my.begin() + 6);
		print_contnl(my2);

		purplenl("std::vector<int> ori2(ori.begin(), ori.begin() + 6)");
		std::vector<int> ori2(ori.begin(), ori.begin() + 6);
		print_contnl(ori2);
	}
	{
		highlight("Constructor : copy another container");
		cyannl("my_base");
		print_contnl(my_base);
		cyannl("ft::vector<int> my(my_base)");
		ft::vector<int> my(my_base);
		print_contnl(my);

		purplenl("ori_base");
		print_contnl(std_base);
		purplenl("std::vector<int> ori(std_base)");
		std::vector<int> ori(std_base);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Operator overload : assignement");
		cyannl("ft::vector<int> my_assigned = my_base");
		ft::vector<int> my_assigned = my_base;
		print_contnl(my_assigned);

		purplenl("std::vector<int> ori_assigned = std_base");
		std::vector<int> ori_assigned = std_base;
		print_contnl(ori_assigned);
		//--------------------------------------------------------------------
		highlight("Method : max_size");
		cyan("my.max_size() : "); std::cout << my.max_size() << "\n";
		purple("ori.max_size() : "); std::cout << ori.max_size() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : reserve memory");
		cyannl("my.reserve(100)");
		my.reserve(100);
		cyan("my.capacity() : "); std::cout << my.capacity() << "\n";
		purplenl("ori.reserve(100)");
		ori.reserve(100);
		purple("ori.capacity() : "); std::cout << ori.capacity() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : front, back");
		cyan("my.front() : "); std::cout << my.front() << "\n";
		cyan("my.back() : "); std::cout << my.back() << "\n";
		cyan("ori.front() : "); std::cout << ori.front() << "\n";
		cyan("ori.back() : "); std::cout << ori.back() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : at");
		cyannl("my.at(42)");
		try
			{ my.at(42); }
		catch (std::out_of_range & errmsg)
			{ std::cout << errmsg.what() << std::endl; }
		//--------------------------------------------------------------------
		highlight("Method : insert elem at position");
		cyan("my : "); print_contnl(my);
		cyannl("my.insert(my.begin() + 3, 9000)");
		my.insert(my.begin() + 3, 9000);
		print_contnl(my);

		purple("ori : "); print_contnl(ori);
		purplenl("ori.insert(ori.begin() + 3, 9000)");
		ori.insert(ori.begin() + 3, 9000);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : insert n times at position");
		cyannl("my.insert(my.begin() + 6, 3, 666)");
		my.insert(my.begin() + 6, 3, 666);
		print_contnl(my);

		purplenl("ori.insert(ori.begin() + 6, 3, 666)");
		ori.insert(ori.begin() + 6, 3, 666);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : insert a range of iterators at position");
		cyannl("my.insert(my.end(), my.begin() + 6, my.begin() + 9)");
		my.insert(my.end(), my.begin() + 6, my.begin() + 9);
		print_contnl(my);

		purplenl("ori.insert(ori.end(), ori.begin() + 6, ori.begin() + 9)");
		ori.insert(ori.end(), ori.begin() + 6, ori.begin() + 9);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : push_back");
		cyannl("my.push_back 90 to 99");
		for (int i = 90; i <= 99; i++)
			my.push_back(i);
		print_contnl(my);
		purplenl("ori.push_back 90 to 99");
		for (int i = 90; i <= 99; i++)
			ori.push_back(i);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : pop_back");
		cyannl("my.pop_back 10 times");
		for (int i = 0; i < 10; i++)
			my.pop_back();
		print_contnl(my);

		purplenl("ori.pop_back 10 times");
		for (int i = 0; i < 10; i++)
			ori.pop_back();
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : assign container to a range of iterators");
		ft::vector<int> my_assign;
		for (int i = 0; i < 10; i++) { my_assign.push_back(i); }
		cyannl("ft::vector<int> my_assign : "); print_contnl(my_assign);
		my_assign.assign(my.begin(), my.end());
		cyannl("my_assign.assign(my.begin(), my.end())");
		print_contnl(my_assign);

		std::vector<int> ori_assign;;
		for (int i = 0; i < 10; i++) { ori_assign.push_back(i); }
		purplenl("ft::vector<int> ori_assign : "); print_contnl(ori_assign);
		ori_assign.assign(ori.begin(), ori.end());
		purplenl("ori_assign.assign(ori.begin(), ori.end())");
		print_contnl(ori_assign);
		//--------------------------------------------------------------------
		highlight("Method : self assign");
		cyannl("my_assign.assign(my_assign.begin(), my_assign.end())");
		my_assign.assign(my_assign.begin(), my_assign.end());
		print_contnl(my_assign);

		purplenl("ori_assign.assign(ori_assign.begin(), ori_assign.end())");
		ori_assign.assign(ori_assign.begin(), ori_assign.end());
		print_contnl(ori_assign);
		//--------------------------------------------------------------------
		highlight("Method : fill assign test");
		ft::vector<int> my_fill;
		cyannl("my_fill");
		for (int i = 0; i < 10; i++) { my_fill.push_back(i); }
		print_contnl(my_fill);
		cyannl("my_fill.assign(3, 42)");
		my_fill.assign(3, 42);
		print_contnl(my_fill);

		std::vector<int> std_fill;
		purplenl("std_fill");
		for (int i = 0; i < 10; i++) { std_fill.push_back(i); }
		print_contnl(std_fill);
		purplenl("std_fill.assign(3, 42)");
		std_fill.assign(3, 42);
		print_contnl(std_fill);
		//--------------------------------------------------------------------
		highlight("Method : erase test");
		cyannl("before :"); print_contnl(my_assign);
		purplenl("before :"); print_contnl(ori_assign);

		cyannl("my_assign.erase(my_assign.begin(), my_assign.begin() + 3)");
		my_assign.erase(my_assign.begin(), my_assign.begin() + 3);
		print_contnl(my_assign);

		purplenl("ori_assign.erase(ori_assign.begin(), ori_assign.begin() + 3)");
		ori_assign.erase(ori_assign.begin(), ori_assign.begin() + 3);
		print_contnl(ori_assign);
		//--------------------------------------------------------------------
		highlight("Method : swap");
		ft::vector<int> v1, v2;
		for (int i = 0; i < 10; i++) { v1.push_back(i); v2.push_back(100 + 2 * i); }
		cyannl("v1");
		print_contnl(v1);
		cyannl("v2");
		print_contnl(v2);
		cyannl("v1.swap(v2)");
		v1.swap(v2);
		cyannl("v1");
		print_contnl(v1);
		cyannl("v2");
		print_contnl(v2);
		//--------------------------------------------------------------------
		highlight("Method : clear");
		cyannl("my.clear()");
		my.clear();
		print_contnl(my);

		purplenl("ori.clear()");
		ori.clear();
		print_contnl(ori);
	}
}
