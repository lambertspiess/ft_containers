#include "../map.hpp"
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include "utils.hpp"

template <class Iter>
void printMapRange(Iter begin, Iter end) {
	while (begin != end)
		{ std::cout << begin->first << ":" << begin->second << ", "; ++begin; }
}

template <class Iter>
void printMapRangeRev(Iter begin, Iter end) {
	while (begin != end)
		{ std::cout << begin->first << ":" << begin->second << ", "; --begin; }
}

template <class Iter>
void printPair(Iter itr)
{ std::cout << itr->first << ":" << itr->second; }

template <class Iter>
void printPairnl(Iter itr)
{ std::cout << itr->first << ":" << itr->second << "\n"; }

template <class Cont>
void printMap(Cont & c) {
	typename Cont::iterator begin = c.begin(), end = c.end();
	printMapRange(begin, end); std::cout << "\n"; }

template <class Cont>
void printMapSize(Cont & c)
	{ std::cout << "size : " << c.size(); }

template <class Cont>
void printMapSizenl(Cont & c)
	{ std::cout << "size : " << c.size() << "\n"; }


//-----------------------------------------------------------------------------
int main()
{
	ft::pair<int, char> ft_pairs[] = {
		ft::make_pair(1, 'a'),
		ft::make_pair(2, 'b'),
		ft::make_pair(3, 'c'),
		ft::make_pair(4, 'd'),
		ft::make_pair(5, 'e')};

	ft::pair<int, char> ft2_pairs[] = {
		ft::make_pair(3, 'a'),
		ft::make_pair(5, 'b'),
		ft::make_pair(7, 'c'),
		ft::make_pair(9, 'd'),
		ft::make_pair(11, 'e')};

	std::pair<int, char> std_pairs[] = {
		std::make_pair(1, 'a'),
		std::make_pair(2, 'b'),
		std::make_pair(3, 'c'),
		std::make_pair(4, 'd'),
		std::make_pair(5, 'e')};

	std::pair<int, char> std2_pairs[] = {
		std::make_pair(3, 'a'),
		std::make_pair(5, 'b'),
		std::make_pair(7, 'c'),
		std::make_pair(9, 'd'),
		std::make_pair(11, 'e')};


	{
		highlight("Constructor : empty map");
		cyannl("ft::map<int, char> my");
		ft::map<int, char> my;
		printMap(my);
		purplenl("std::map<int, char> ori");
		std::map<int, char> ori;
		printMap(ori);
	}

	{
		highlight("Constructor : from a range of elements (pairs)");
		cyannl("my");
		ft::map<int, char> my(ft_pairs, ft_pairs + 5);
		printMap(my);
		std::map<int, char> ori(std_pairs, std_pairs + 5);
		purplenl("std");
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Constructor : create copy from other container");
		cyannl("ft::map<int, char> mycopy(my)");
		ft::map<int, char> mycopy(my);
		printMap(mycopy);
		cyannl("mycopy.clear().");
		mycopy.clear();
		printMap(mycopy);
		cyannl("my");
		printMap(my); std::cout << "\n";

		purplenl("ft::map<int, char> stdcopy(ori)");
		std::map<int, char> stdcopy(ori);
		printMap(stdcopy);
		purplenl("stdcopy.clear().");
		stdcopy.clear();
		printMap(stdcopy);
		purplenl("std");
		printMap(ori);

		//---------------------------------------------------------------------
		highlight("Operator : assignement");
		cyannl("ft::map<int, char> my_assign = my");
		ft::map<int, char> my_assign = my;
		printMap(my_assign);
		cyannl("my_assign.clear()");
		my_assign.clear();
		cyannl("my");
		printMap(my);

		purplenl("std::map<int, char> std_assign = ori");
		std::map<int, char> std_assign = ori;
		printMap(std_assign);
		purplenl("std_assign.clear()");
		std_assign.clear();
		purplenl("ori");
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Method : empty");
		cyannl("my_assign.empty()");
		if (my_assign.empty() == true) { std::cout << "empty\n"; }
		else { std::cout << "not empty\n"; }
		purplenl("std_assign.empty()");
		if (std_assign.empty() == true) { std::cout << "empty\n"; }
		else { std::cout << "not empty\n"; }
		//---------------------------------------------------------------------
		highlight("Method : max_size");
		cyannl("my.max_size()");
		std::cout << my.max_size() << "\n";
		purplenl("ori.max_size()");
		std::cout << ori.max_size() << "\n";
		//---------------------------------------------------------------------
		highlight("Operator : access on existing key");
		cyannl("char my_access = my[3]");
		char my_access = my[3]; std::cout << my_access << "\n";
		cyannl("char std_access = ori[3]");
		char std_access = my[3]; std::cout << std_access << "\n";
		//---------------------------------------------------------------------
		highlight("Operator : access on non-existing key (insert)");
		cyannl("char my_access2 = my[42]");
		char my_access2 = my[42]; std::cout << my_access2 << "\n";
		printMap(my);
		cyannl("char std_access2 = std[42]");
		char std_access2 = ori[42]; std::cout << std_access2 << "\n";
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Method : insert value at non-existing key");
		cyannl("my.insert(ft::make_pair(10, h))");
		my.insert(ft::make_pair(10, 'h'));
		cyannl("after access, my");
		printMap(my);
		purplenl("ori.insert(std::make_pair(10, h))");
		ori.insert(std::make_pair(10, 'h'));
		purplenl("after access, ori");
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Method : insert value at already existing key");
		cyannl("my.insert(ft::make_pair(42, z))");
		my.insert(ft::make_pair(42, 'z'));
		printMap(my);
		purplenl("ori.insert(std::make_pair(42, z))");
		ori.insert(std::make_pair(42, 'z'));
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Method : insert val at iterator position");
		cyannl("for (int i = 0; i < 3; ++i) { ++my_itr; }");
		cyannl("my.insert(my_itr, ft::make_pair(21, 'y')");
		ft::map<int, char>::iterator my_itr = my.begin();
		for (int i = 0; i < 3; ++i) { ++my_itr; }
		my.insert(my_itr, ft::make_pair(21, 'y'));
		cyannl("my");
		printMap(my);

		purplenl("for (int i = 0; i < 3; ++i) { ++ori_itr; }");
		purplenl("ori.insert(ori_itr, std::make_pair(21, 'y')");
		std::map<int, char>::iterator ori_itr = ori.begin();
		for (int i = 0; i < 3; ++i) { ++ori_itr; }
		ori.insert(ori_itr, std::make_pair(21, 'y'));
		purplenl("ori");
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Constructor : from a range of iterators");
		cyannl("ft::map<int, char> my2(ft2_pairs, ft2_pairs + 5)");
		ft::map<int, char> my2(ft2_pairs, ft2_pairs + 5);
		cyannl("my2");
		printMap(my2);

		purplenl("std::map<int, char> my2(std2_pairs, std2_pairs + 5)");
		std::map<int, char> ori2(std2_pairs, std2_pairs + 5);
		purplenl("ori2");
		printMap(ori2);
		//---------------------------------------------------------------------
		highlight("Method : erase at iterator position");
		my_itr = my.begin(); for (int i = 0; i < 6; ++i) { ++my_itr; }
		cyannl("my_itr = my.begin(); for (int i = 0; i < 6; ++i) { ++my_itr; }");
		cyannl("my.erase(my_itr)");
		my.erase(my_itr);
		printMap(my);

		ori_itr = ori.begin(); for (int i = 0; i < 6; ++i) { ++ori_itr; }
		cyannl("ori_itr = ori.begin(); for (int i = 0; i < 6; ++i) { ++ori_itr; }");
		cyannl("ori.erase(ori_itr)");
		ori.erase(ori_itr);
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Method : erase existing key");
		cyannl("my.erase(42)");
		my.erase(42);
		printMap(my);

		purplenl("ori.erase(42)");
		ori.erase(42);
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Method : erase a range of iterators [first, last)");
		my_itr = my.begin(); for (int i = 0; i < 2; ++i) { ++my_itr; }
		ft::map<int, char>::iterator my_itr2 = my.begin();
		my_itr2 = my.begin(); for (int i = 0; i < 4; ++i) { ++my_itr2; }
		cyannl("for (int i = 0; i < 2; ++i) { ++my_itr; }");
		cyannl("my.erase(my_itr, my_itr + 2)");
		my.erase(my_itr, my_itr2);
		printMap(my);

		ori_itr = ori.begin(); for (int i = 0; i < 2; ++i) { ++ori_itr; }
		std::map<int, char>::iterator ori_itr2 = ori.begin();
		ori_itr2 = ori.begin(); for (int i = 0; i < 4; ++i) { ++ori_itr2; }
		purplenl("for (int i = 0; i < 2; ++i) { ++ori_itr; }");
		purplenl("ori.erase(ori_itr, ori_itr + 2)");
		ori.erase(ori_itr, ori_itr2);
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Method : swap");
		cyannl("my");
		printMap(my);
		cyannl("my2");
		printMap(my2);
		cyannl("my.swap(my2)");
		cyannl("my");
		printMap(my);

		purplenl("ori");
		printMap(ori);
		purplenl("ori2");
		printMap(ori2);
		purplenl("ori.swap(ori2)");
		purplenl("ori");
		printMap(ori);
		//---------------------------------------------------------------------
		highlight("Method : clear test");
		cyannl("my2.clear()");
		my2.clear();
		printMap(my2);
		std::cout << "my2.size() = " << my2.size() << "\n";
		purplenl("----------\nori2.clear()");
		ori2.clear();
		printMap(ori2);
		std::cout << "ori2.size() = " << ori2.size() << "\n";
		//---------------------------------------------------------------------
		highlight("Method : find key by value");
		cyannl("my_itr = my.find(2)");
		my_itr = my.find(2);
		printPairnl(my_itr);

		purplenl("std_itr = ori.find(2)");
		ori_itr = ori.find(2);
		printPairnl(ori_itr);
		//---------------------------------------------------------------------
		highlight("Method : count");
		cyannl("my.count(2)");
		std::cout << "my.count(2) = " << my.count(2) << "\n";
		purplenl("ori.count(2)");
		std::cout << "ori.count(2) = " << ori.count(2) << "\n";
		//---------------------------------------------------------------------
		highlight("Method : lower_bound");
		cyannl("my");
		printMap(my);
		cyannl("my_itr = my.lower_bound(2)");
		my_itr = my.lower_bound(2);
		if (my_itr != my.end())
			printPairnl(my_itr);
		else
			std::cout << "end()" << "\n";

		purplenl("ori");
		printMap(ori);
		purplenl("ori_itr = ori.lower_bound(2)");
		ori_itr = ori.lower_bound(2);
		if (ori_itr != ori.end())
			printPairnl(ori_itr);
		else
			std::cout << "end()" << "\n";
		//---------------------------------------------------------------------
		highlight("Method : upper_bound");
		cyannl("my");
		printMap(my);
		cyannl("my_itr = my.upper_bound(2)");
		my_itr = my.upper_bound(2);
		if (my_itr != my.end())
			printPairnl(my_itr);
		else
			std::cout << "end()" << "\n";

		purplenl("ori");
		printMap(ori);
		purplenl("ori_itr = ori.upper_bound(2)");
		ori_itr = ori.upper_bound(2);
		if (ori_itr != ori.end())
			printPairnl(ori_itr);
		else
			std::cout << "end()" << "\n";
		//---------------------------------------------------------------------
		highlight("Method : equal range");
		cyannl("my_subsequence = my.equal_range(2)");
		ft::pair<
			ft::map<int, char>::iterator,
			ft::map<int, char>::iterator
			> my_subsequence = my.equal_range(2);
		cyannl("first: ");
		printPairnl(my_subsequence.first);
		cyannl("second: ");
		printPairnl(my_subsequence.second);
		std::pair<
			std::map<int, char>::iterator,
			std::map<int, char>::iterator
			> ori_subsequence = ori.equal_range(2);
		purplenl("ori_subsequence = ori.equal_range(2)");
		purplenl("first: ");
		printPairnl(ori_subsequence.first);
		purplenl("second: ");
		printPairnl(ori_subsequence.second);
	}
}

