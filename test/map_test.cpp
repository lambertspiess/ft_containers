#include "../Map.hpp"
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include "test.hpp"

// print begin to end
template <typename M>
void print(M& a);
// print forwardly it to last
template <class Iter>
void iterPrint(Iter it, Iter last);
// print backwardly it to last
template <class Iter>
void iterBack(Iter it, Iter last);
// print key, value
template <class Iter>
void key_value(Iter it);
// print size

template <class M>
void printSize(M& a);

int main()
{
	std::pair<int, char> std_pair[] = {
		std::make_pair(1, 'a'),
		std::make_pair(2, 'b'),
		std::make_pair(3, 'c'),
		std::make_pair(4, 'd'),
		std::make_pair(5, 'e')};
	ft::pair<int, char> ft_pair[] = {
		ft::make_pair(1, 'a'),
		ft::make_pair(2, 'b'),
		ft::make_pair(3, 'c'),
		ft::make_pair(4, 'd'),
		ft::make_pair(5, 'e')};
	std::pair<int, char> std2_pair[] = {
		std::make_pair(3, 'a'),
		std::make_pair(5, 'b'),
		std::make_pair(7, 'c'),
		std::make_pair(9, 'd'),
		std::make_pair(11, 'e')};
	ft::pair<int, char> ft2_pair[] = {
		ft::make_pair(3, 'a'),
		ft::make_pair(5, 'b'),
		ft::make_pair(7, 'c'),
		ft::make_pair(9, 'd'),
		ft::make_pair(11, 'e')};
	{
		title("empty construct test");
		red("ft::map<int, char> my;");
		ft::map<int, char> my;
		std::map<int, char> ori;
		std::cout  << std::endl;
	}

//	{
//		title("range construct test");
//		red("make_pair(1, a) ... make_pair(5, e)");
//		blue("ft::map<int, char> my(ft_pair, ft_pair + 5)");
//		ft::map<int, char> my(ft_pair, ft_pair + 5);
//		print(my);
//		std::map<int, char> ori(std_pair, std_pair + 5);
//		yellow("std::map<int, char> ori(std_pair, std_pair + 5)");
//		print(ori);
//		
//		std::cout << std::endl;
//		title("copy construct test(check deep copy)");
//		red("ft::map<int, char> c(my)");
//		ft::map<int, char> c(my);
//		print(c);
//		red("check deep copy.");
//		red("c.clear() and print(c)");
//		c.clear();
//		print(c);
//		red("after c.clear and print(my)");
//		print(my);
//
//		std::cout << std::endl;
//		title("assignment operator test");
//		red("ft::map<int, char> a; a = my");
//		ft::map<int, char> a;
//		a = my;
//		print(a);
//
//		red("check deep copy.");
//		red("a.clear() and print(a)");
//		a.clear();
//		print(a);
//		red("after a.clear and print(my)");
//		print(my);
//
//		std::cout << std::endl;
//		title("empty size test");
//		blue("cout a.size");
//		printSize(a);
//		if (a.empty())
//			std::cout << "I'm Empty" << std::endl;
//		else
//			std::cout << "I'm not Empty" << std::endl;
//		yellow("cout my.size");
//		printSize(my);
//		if (my.empty())
//			std::cout << "I'm Empty" << std::endl;
//		else
//			std::cout << "I'm not Empty\n" << std::endl;
//
//		title("max size test");
//		std::cout << "ft's max size:  " << my.max_size() << std::endl;
//		std::cout << "std's max size: " << ori.max_size() << std::endl;
//		std::cout << std::endl;
//
//		title("operator[] test");
//		red("ft");
//		print(my);
//		blue("char op = my[7]\nif input key doesnt exist, insert key");
//		char op = my[7];
//		print(my);
//
//		red("std");
//		print(ori);
//		op = ori[7];
//		yellow("char op = ori[7]\nif input key doesnt exist, insert key");
//		print(ori);
//		std::cout << std::endl;
//
//		title("insert(val)");
//		blue("my.insert(ft::make_pair(10, h))");
//		my.insert(ft::make_pair(10, 'h'));
//		print(my);
//		yellow("ori.insert(std::make_pair(10, h))");
//		ori.insert(std::make_pair(10, 'h'));
//		print(ori);
//
//		red("insert already exist key\n");
//		blue("my.insert(ft::make_pair(3, h))");
//		my.insert(ft::make_pair(3, 'h'));
//		print(my);
//		
//		yellow("ori.insert(std::make_pair(3, h))");
//		ori.insert(std::make_pair(3, 'h'));
//		print(ori);
//
//		title("insert(position, val)");
//		red("ft::map<int, char>::iterator myIter = my.begin();\nit++;it++it++");
//		ft::map<int, char>::iterator ftIter = my.begin();
//		ftIter++; ftIter++; ftIter++;
//		blue("my.insert(myIter, ft::make_pair(15, 'z'));");
//		my.insert(ftIter, ft::make_pair(15, 'z'));
//		print(my);
//
//		std::map<int, char>::iterator stdIter = ori.begin();
//		stdIter++; stdIter++; stdIter++;
//		ori.insert(stdIter, std::make_pair(15, 'z'));
//		print(ori);
//
//		title("insert(first, last)");
//		ft::map<int, char> my2(ft2_pair, ft2_pair + 5);
//		std::map<int, char> ori2(std2_pair, std2_pair + 5);
//		red("my2");
//		print(my2);
//		red("ori2");
//		print(ori2);
//		blue("my.insert(my2.begin(), my2.end())");
//		my.insert(my2.begin(), my2.end());
//		print(my);
//		yellow("ori.insert(ori2.begin(), ori2.end())");
//		ori.insert(ori2.begin(), ori2.end());
//		print(ori);
//
//		title("erase(position)");
//		blue("my.erase(my.begin())");
//		my.erase(my.begin());
//		print(my);
//		yellow("ori.erase(ori.begin())");
//		ori.erase(ori.begin());
//		print(ori);
//
//		title("erase(key)");
//		blue("my.erase(2)");
//		my.erase(2);
//		print(my);
//	
//		yellow("ori.erase(2)");
//		ori.erase(2);
//		print(ori);
//
//		title("erase(first, last) -> [first, last)");
//		blue("my.erase(my.begin(), ++my.begin()");
//		my.erase(my.begin(), ++my.begin());
//		print(my);
//		yellow("ori.erase(ori.begin(), ++ori.begin())");
//		ori.erase(ori.begin(), ++ori.begin());
//		print(ori);
//
//		title("swap test");
//		red("my");
//		print(my);
//		blue("my2");
//		print(my2);
//		cyan("my.swap(my2)");
//		my.swap(my2);
//		red("my");
//		print(my);
//		blue("my2");
//		print(my2);
//		
//		ori.swap(ori2);
//		yellow("ori.swap(ori2)");
//		print(ori);
//
//		title("clear test");
//		blue("my2.clear()");
//		my2.clear();
//		print(my2);
//		printSize(my2);
//		yellow("----------\nori2.clear()");
//		ori2.clear();
//		print(ori2);
//		printSize(ori2);
//
//		title("find test");
//		blue("ftIter = my.find(3)");
//		ftIter = my.find(3);
//		key_value(ftIter);
//
//		yellow("stdIter = ori.find(3)");
//		stdIter = ori.find(3);
//		key_value(stdIter);
//		stdIter = ori.find(2);
//
//
//		title("count test (1 or 0)");
//		std::cout << "my.count(3): " << my.count(3) << std::endl;
//		std::cout << "my.count(2): " << my.count(2) << std::endl;
//		std::cout << "ori.count(3): " << ori.count(3) << std::endl;
//		std::cout << "ori.count(2): " << ori.count(2) << std::endl;
//
//		title("lower bound test (greater or equal to key)");
//		blue("ftIter = my.lower_bound(5);");
//		ftIter = my.lower_bound(5);
//		key_value(ftIter);
//		yellow("stdIter = ori.lower_bound(5)");
//		stdIter = ori.lower_bound(5);
//		key_value(stdIter);
//
//		title("upper bound");
//		blue("ftIter = my.upper_bound(5);");
//		ftIter = my.upper_bound(5);
//		key_value(ftIter);
//		yellow("stdIter = ori.upper_bound(5)");
//		stdIter = ori.upper_bound(5);
//		key_value(stdIter);
//
//		title("equal range test -> lower + upper");
//		blue("myPair = my.equal_range(5)");
//		ft::pair<ft::map<int, char>::iterator,ft::map<int, char>::iterator> myPair = my.equal_range(5);
//		blue("first: ");
//		key_value(myPair.first);
//		blue("second: ");
//		key_value(myPair.second);
//		std::pair<std::map<int, char>::iterator,std::map<int, char>::iterator> stdPair = ori.equal_range(5);
//		yellow("stdPair = ori.equal_range(5)");
//		yellow("first: ");
//		key_value(stdPair.first);
//		yellow("second: ");
//		key_value(stdPair.second);
//
//		title("finish");
//		print(my);
//		blue("my size");
//		printSize(my);
//		print(ori);
//		yellow("ori size");
//		printSize(ori);
//	}
}

template <typename M>
void print(M& a)
{
	typename M::iterator it = a.begin();
	std::cout << "\033[1;36;40m============================\033[0m" << std::endl;
	for (size_t i = 0; i < a.size(); i++, it++)
	{
		std::cout << "\033[1;31;40mkey: \033[0m" << it->first << 
				"\033[1;31;40m value: \033[0m" << it->second << std::endl;
	}
	std::cout << "\033[1;36;40m============================\033[0m" << std::endl;
}

template <class Iter>
void iterPrint(Iter it, Iter last)
{
	std::cout << "\033[1;36;40m============================\033[0m" << std::endl;
	for (; it != last; ++it)
	{
		std::cout << "\033[1;31;40mkey: \033[0m" << it->first << 
				"\033[1;31;40m value: \033[0m" << it->second << std::endl;
	}
	std::cout << "\033[1;36;40m============================\033[0m" << std::endl;
}

template <class Iter>
void iterBack(Iter it, Iter last)
{
	std::cout << "\033[1;36;40m============================\033[0m" << std::endl;
	for (; it != last; --it)
	{
		std::cout << "\033[1;31;40mkey: \033[0m" << it->first << 
				"\033[1;31;40m value: \033[0m" << it->second << std::endl;
	}
	std::cout << "\033[1;36;40m============================\033[0m" << std::endl;
}

template <class Iter>
void key_value(Iter it)
{
	std::cout << "\033[1;31;40mkey: \033[0m" << it->first << "\033[1;31;40m value: \033[0m" << it->second << std::endl;
}

template <class M>
void printSize(M& a)
{
	std::cout << "\033[1;31;40msize: \033[0m" << a.size() << std::endl;
}
