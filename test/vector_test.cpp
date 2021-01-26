#include "../vector.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "test.hpp"

template <typename V>
void print(V& v)
{
	std::cout << "\033[1;33;40m==================================\033[0m\n"
		<< "\033[1;31;40msize: \033[0m" << "\033[1;34;40m" << v.size()
		<<"\033[0m" << "\033[1;31;40m capacity: \033[0m" << "\033[1;34;40m"
		<< v.capacity() << std::endl;
	std::cout << "\033[1;32;40m";
	typename V::iterator it = v.begin();
	for (; it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n\033[1;33;40m==================================\033[0m" << std::endl;
}

int main(void)
{
	ft::vector<int> ftBase;
	std::vector<int> stdBase;
	for (int i = 0; i < 10; ++i) {
		ftBase.push_back(i);
	}
	for (int i = 0; i < 10; ++i) {
		stdBase.push_back(i);
	}
	{
		title("default constructor test");
		red("myvector");
		ft::vector<int> test;
		print(test);
	}
	{
		title("fill constructor test");
		blue("my(10, 123)");
		ft::vector<int> my(10, 123);
		print(my);
		yellow("ori(10, 123)");
		std::vector<int> ori(10, 123);
		print(ori);

		title("range constructor test");
		blue("my2(my.begin(), my.begin() + 5)");
		ft::vector<int> my2(my.begin(), my.begin() + 5);
		print(my2);

		yellow("ori2(ori.begin(), ori.begin() + 5;)");
		std::vector<int> ori2(ori.begin(), ori.begin() + 5);
		print(ori2);

	}
	{
		title("copy constructor test");
		blue("ftBase");
		print(ftBase);
		blue("ft::vector<int< my(ftBase)");
		ft::vector<int> my(ftBase);
		print(my);

		yellow("std::vector<int> ori(stdBase)");
		std::vector<int> ori(stdBase);
		print(ori);


		title("assign test");
		blue("ft::vector<int> a; a = ftBase");
		ft::vector<int> a; a = ftBase;
		print(a);

		yellow("std::vector<int> o;o = ftBase");
		std::vector<int> o; o = stdBase;
		print(o);

		title("max size");
		std::cout << "ft::vector : " << my.max_size() << std::endl;
		std::cout << "std::vector : " << ori.max_size() << std::endl;

		title("reserve test");
		blue("my.reserve(100)");
		my.reserve(100);
		print(my);

		yellow("ori.reserve(100)");
		ori.reserve(100);
		print(ori);

		title("element access test");
		std::cout << "my.front(): " << my.front() << std::endl;
		std::cout << "my.back(): " << my.back() << std::endl;
		std::cout << "ori.front(): " << ori.front() << std::endl;
		std::cout << "ori.back(): " << ori.back() << std::endl;

		title("at test");
		blue("my.at(11)");
		try
		{
			my.at(11);
		}
		catch (std::out_of_range& e)
		{
			std::cout <<e.what() << std::endl;
		}

		title("single element insert(position, val)");
		print(my);
		blue("my.insert(my.begin() + 5, 1000)");
		my.insert(my.begin() + 5, 1000);
		print(my);

		yellow("ori.insert(ori.begin() + 5, 1000)");
		ori.insert(ori.begin() + 5, 1000);
		print(ori);

		title("fill insert(position, n, val)");
		blue("my.insert(my.begin(), 3, 100)");
		my.insert(my.begin(), 3, 100);
		print(my);

		yellow("ori.insert(ori.begin(), 3, 100)");
		ori.insert(ori.begin(), 3, 100);
		print(ori);

		title("range insert(position, first, last)");
		blue("my.insert(my.end(), my.begin(), my.begin() + 3)");
		my.insert(my.end(), my.begin(), my.begin() + 3);
		print(my);

		yellow("ori.insert(ori.end(), ori.begin(), ori.begin() + 3)");
		ori.insert(ori.end(), ori.begin(), ori.begin() + 3);
		print(ori);

		title("push_back test");
		blue("my.push_back 0 to 9");
		for (int i = 0; i < 10; i++)
			my.push_back(i);
		print(my);
		yellow("ori.push_back 0 to 9");
		for (int i = 0; i < 10; i++)
			ori.push_back(i);
		print(ori);
		
		title("pop_back test");
		blue("my.pop_back 10 times");
		for (int i = 0; i < 10; i++)
			my.pop_back();
		print(my);

		yellow("ori.pop_back 10 times");
		for (int i = 0; i < 10; i++)
			ori.pop_back();
		print(ori);


		title("range assign test");
		ft::vector<int> my2;
		blue("my2");
		for (int i = 0; i < 10; i++)
			my2.push_back(i);
		print(my2);
		blue("my2.assign(my.begin(), my.end())");
		my2.assign(my.begin(), my.end());
		print(my2);

		std::vector<int> ori2;
		blue("ori2");
		for (int i = 0; i < 10; i++)
			ori2.push_back(i);
		ori2.assign(ori.begin(), ori.end());
		print(ori2);

		title("fill assign test");
		ft::vector<int> my3;
		blue("my3");
		for (int i = 0; i < 10; i++)
			my3.push_back(i);
		print(my3);
		blue("my3.assign(10, 0)");
		my3.assign(10, 0);
		print(my3);

		std::vector<int> ori3;
		blue("ori3");
		for (int i = 0; i < 10; i++)
			ori3.push_back(i);
		ori3.assign(10, 0);
		print(ori3);

		title("erase test");
		blue("my2.erase(my2.begin(), my2.begin() + 3)");
		print(my2);
		my2.erase(my2.begin(), my2.begin() + 3);
		print(my2);

		yellow("ori2.erase(ori2.begin(), ori2.begin() + 3)");
		print(ori2);
		ori2.erase(ori2.begin(), ori2.begin() + 3);
		print(ori2);


		title("swap test");
		blue("my2");
		print(my2);
		blue("my3");
		print(my3);
		swap(my2, my3);
		blue("my2");
		print(my2);
		blue("my3");
		print(my3);

		yellow("ori2");
		print(ori2);
		yellow("ori3");
		print(ori3);
		swap(ori2, ori3);
		yellow("ori2");
		print(ori2);
		yellow("ori3");
		print(ori3);

		title("clear test");
		blue("my.clear()");
		my.clear();
		print(my);
		
		yellow("ori.clear()");
		ori.clear();
		print(ori);
	}
}
