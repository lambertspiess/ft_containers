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
	std::pair<int, char> std_pairs[] = {
		std::make_pair(1, 'a'),
		std::make_pair(2, 'b'),
		std::make_pair(3, 'c'),
		std::make_pair(4, 'd'),
		std::make_pair(5, 'e')};
	ft::pair<int, char> ft_pairs[] = {
		ft::make_pair(1, 'a'),
		ft::make_pair(2, 'b'),
		ft::make_pair(3, 'c'),
		ft::make_pair(4, 'd'),
		ft::make_pair(5, 'e')};

	std::pair<int, char> std2_pairs[] = {
		std::make_pair(3, 'a'),
		std::make_pair(5, 'b'),
		std::make_pair(7, 'c'),
		std::make_pair(9, 'd'),
		std::make_pair(11, 'e')};
	ft::pair<int, char> ft2_pairs[] = {
		ft::make_pair(3, 'a'),
		ft::make_pair(5, 'b'),
		ft::make_pair(7, 'c'),
		ft::make_pair(9, 'd'),
		ft::make_pair(11, 'e')};

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
		highlight("Constructor : from iterator range of elems (pairs)");
		cyannl("my");
		ft::map<int, char> my(ft_pairs, ft_pairs + 5);
		printMap(my);
		std::map<int, char> ori(std_pairs, std_pairs + 5);
		purplenl("std");
		printMap(ori);

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

		highlight("Operator : assignement");
		cyannl("ft::map<int, char> my_assign = my");
		ft::map<int, char> my_assign = my;
		printMap(my_assign);
		cyannl("my_assign.clear()");
		my_assign.clear();
		cyannl("my");
		printMap(my);

		cyannl("std::map<int, char> std_assign = ori");
		std::map<int, char> std_assign = ori;
		printMap(std_assign);
		cyannl("std_assign.clear()");
		std_assign.clear();
		cyannl("ori");
		printMap(ori);

		highlight("Method : empty");
		cyannl("my_assign.empty()");
		if (my_assign.empty() == true) { std::cout << "empty\n"; }
		else { std::cout << "not empty\n"; }
		purplenl("std_assign.empty()");
		if (std_assign.empty() == true) { std::cout << "empty\n"; }
		else { std::cout << "not empty\n"; }

		highlight("Method : max_size");
		cyannl("my.max_size()");
		std::cout << my.max_size() << "\n";
		purplenl("ori.max_size()");
		std::cout << ori.max_size() << "\n";

		highlight("Operator : access on existing key");
		cyannl("char my_access = my[3]");
		char my_access = my[3]; std::cout << my_access << "\n";
		cyannl("char std_access = ori[3]");
		char std_access = my[3]; std::cout << std_access << "\n";

		highlight("Operator : access on non-existing key (insert)");
		cyannl("char my_access2 = my[42]");
		char my_access2 = my[42]; std::cout << my_access2 << "\n";
		cyannl("char std_access2 = std[42]");
		char std_access2 = my[42]; std::cout << std_access2 << "\n";

		highlight("Method : insert value");
		cyannl("my.insert(ft::make_pair(10, h))");
		my.insert(ft::make_pair(10, 'h'));
		printMap(my);
		purplenl("ori.insert(std::make_pair(10, h))");
		ori.insert(std::make_pair(10, 'h'));
		printMap(ori);

//		cyannl("insert already exist key\n");
//		cyannl("my.insert(ft::make_pair(3, h))");
//		my.insert(ft::make_pair(3, 'h'));
//		printMap(my);
//		
//		purplenl("ori.insert(std::make_pair(3, h))");
//		ori.insert(std::make_pair(3, 'h'));
//		printMap(ori);
//
//		highlight("insert(position, val)");
//		cyannl("ft::map<int, char>::iterator myIter = my.begin();\nit++;it++it++");
//		ft::map<int, char>::iterator ftIter = my.begin();
//		ftIter++; ftIter++; ftIter++;
//		cyannl("my.insert(myIter, ft::make_pair(15, 'z'));");
//		my.insert(ftIter, ft::make_pair(15, 'z'));
//		printMap(my);
//
//		std::map<int, char>::iterator stdIter = ori.begin();
//		stdIter++; stdIter++; stdIter++;
//		ori.insert(stdIter, std::make_pair(15, 'z'));
//		printMap(ori);
//
//		highlight("insert(first, last)");
//		ft::map<int, char> my2(ft2_pair, ft2_pair + 5);
//		std::map<int, char> ori2(std2_map, std2_map + 5);
//		cyannl("my2");
//		printMap(my2);
//		cyannl("ori2");
//		printMap(ori2);
//		cyannl("my.insert(my2.begin(), my2.end())");
//		my.insert(my2.begin(), my2.end());
//		printMap(my);
//		purplenl("ori.insert(ori2.begin(), ori2.end())");
//		ori.insert(ori2.begin(), ori2.end());
//		printMap(ori);
//
//		highlight("erase(position)");
//		cyannl("my.erase(my.begin())");
//		my.erase(my.begin());
//		printMap(my);
//		purplenl("ori.erase(ori.begin())");
//		ori.erase(ori.begin());
//		printMap(ori);
//
//		highlight("erase(key)");
//		cyannl("my.erase(2)");
//		my.erase(2);
//		printMap(my);
//	
//		purplenl("ori.erase(2)");
//		ori.erase(2);
//		printMap(ori);
//
//		highlight("erase(first, last) -> [first, last)");
//		cyannl("my.erase(my.begin(), ++my.begin()");
//		my.erase(my.begin(), ++my.begin());
//		printMap(my);
//		purplenl("ori.erase(ori.begin(), ++ori.begin())");
//		ori.erase(ori.begin(), ++ori.begin());
//		printMap(ori);
//
//		highlight("swap test");
//		cyan("my.swap(my2)");
//		cyannl("my"); printMap(my); cyannl("my2"); printMap(my2);
//		my.swap(my2);
//		cyannl("my"); printMap(my); cyannl("my2"); printMap(my2);
//
//		purplenl("ori.swap(ori2)");
//		purplenl("ori"); printMap(ori);
//		purplenl("ori2"); printMap(ori2);
//		ori.swap(ori2);
//		purplenl("ori"); printMap(ori);
//		purplenl("ori2"); printMap(ori2);
//
//		highlight("clear test");
//		cyannl("my2.clear()");
//		my2.clear();
//		printMap(my2);
//		printSize(my2);
//		purplenl("----------\nori2.clear()");
//		ori2.clear();
//		printMap(ori2);
//		printSize(ori2);
//
//		highlight("find test");
//		cyannl("ftIter = my.find(3)");
//		ftIter = my.find(3);
//		key_value(ftIter);
//
//		purplenl("stdIter = ori.find(3)");
//		stdIter = ori.find(3);
//		key_value(stdIter);
//		stdIter = ori.find(2);
//
//
//		highlight("count test (1 or 0)");
//		std::cout << "my.count(3): " << my.count(3) << std::endl;
//		std::cout << "my.count(2): " << my.count(2) << std::endl;
//		std::cout << "ori.count(3): " << ori.count(3) << std::endl;
//		std::cout << "ori.count(2): " << ori.count(2) << std::endl;
//
//		highlight("lower bound test (greater or equal to key)");
//		cyannl("ftIter = my.lower_bound(5);");
//		ftIter = my.lower_bound(5);
//		key_value(ftIter);
//		purplenl("stdIter = ori.lower_bound(5)");
//		stdIter = ori.lower_bound(5);
//		key_value(stdIter);
//
//		highlight("upper bound");
//		cyannl("ftIter = my.upper_bound(5);");
//		ftIter = my.upper_bound(5);
//		key_value(ftIter);
//		purplenl("stdIter = ori.upper_bound(5)");
//		stdIter = ori.upper_bound(5);
//		key_value(stdIter);
//
//		highlight("equal range test -> lower + upper");
//		cyannl("myPair = my.equal_range(5)");
//		ft::pair<ft::map<int, char>::iterator,ft::map<int, char>::iterator> myPair = my.equal_range(5);
//		cyannl("first: ");
//		key_value(myPair.first);
//		cyannl("second: ");
//		key_value(myPair.second);
//		std::pair<std::map<int, char>::iterator,std::map<int, char>::iterator> stdPair = ori.equal_range(5);
//		purplenl("stdPair = ori.equal_range(5)");
//		purplenl("first: ");
//		key_value(stdPair.first);
//		purplenl("second: ");
//		key_value(stdPair.second);
//
//		highlight("finish");
//		printMap(my);
//		cyannl("my size");
//		printSize(my);
//		printMap(ori);
//		purplenl("ori size");
//		printSize(ori);
	}
}

