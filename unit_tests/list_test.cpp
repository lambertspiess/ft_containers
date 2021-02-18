#include "../list.hpp"
#include <list>
#include <random>
#include <iostream>
#include "utils.hpp"

template <class Cont>
void print_contnl(Cont & c)
{
	typename Cont::iterator itr = c.begin(), end = c.end();
	while (itr != end) { std::cout << *itr << ' '; ++itr; } std::cout << "\n";
}
template <class Cont>
void print_cont(Cont & c)
{
	typename Cont::iterator itr = c.begin(), end = c.end();
	while (itr != end) { std::cout << *itr << ' '; ++itr; }
}

int main()
{
	{
		highlight("Default constructor : empty list");
		cyannl("ft::list<int> my");
		ft::list<int> my;
		print_cont(my);
		purplenl("std::list<int> ori");
		std::list<int> ori;
		print_cont(ori);
		//--------------------------------------------------------------------
		highlight("Constructor : fill witn n times val");
		cyannl("ft::list<int> my_ctor_nval(8, 42)");
		ft::list<int> ctor_nval(8, 42);
		print_contnl(ctor_nval);
		purplenl("std::list<int> std_ctor_nval(8, 42)");
		std::list<int> std_ctor_nval(8, 42);
		print_contnl(std_ctor_nval);
		//--------------------------------------------------------------------
		highlight("Method : Push-back");
		cyannl("i = 0; while (i < 10) { my.push_back(i); ++i; }");
		for (int i = 0; i < 10; ++i) { my.push_back(i); }
		print_contnl(my);
		purplenl("i = 0; while (i < 10) { ori.push_back(i); ++i; }");
		for (int i = 0; i < 10; ++i) { ori.push_back(i); }
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Constructor : from a range of iterators");
		cyannl("ft::list<int> my_range_ctor(my.begin(), my.end())");
		ft::list<int> my_range_ctor(my.begin(), my.end());
		print_contnl(my_range_ctor);
		purplenl("ft::list<int> std_range_ctor(ori.begin(), ori.end())");
		ft::list<int> std_range_ctor(ori.begin(), ori.end());
		print_contnl(std_range_ctor);
		//--------------------------------------------------------------------
		highlight("Constructor : copy from other container");
		cyannl("ft::list<int> my_copy(my)");
		ft::list<int> my_copy(my);
		print_contnl(my_copy);
		purplenl("std::list<int> std_copy(0)");
		std::list<int> std_copy(ori);
		print_contnl(std_copy);
		//--------------------------------------------------------------------
		highlight("Method : empty");
		cyan("my.size() before : ");
		std::cout << my.size() << " ";
		cyan("after my.empty() : ");
		my.empty();  std::cout << my.empty() << "\n";
		purple("ori.size() before : ");
		std::cout << ori.size() << " ";
		purple("after ori.empty() : ");
		ori.empty();  std::cout << ori.empty() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : max size");
		cyan("my.max_size() : ");
		std::cout << my.max_size() << "\n";
		purple("ori.max_size() : ");
		std::cout << ori.max_size() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : front() and back()");
		cyan("my.front() = "); std::cout << my.front() << " ";
		cyan("my.back() = "); std::cout << my.back() << "\n";
		purple("ori.front() = "); std::cout << ori.front() << " ";
		purple("ori.back() = "); std::cout << ori.back() << "\n";
		//--------------------------------------------------------------------
		highlight("Method : push/pop front/back");
		cyannl("my.push_front(42)");
		my.push_front(42);
		print_contnl(my);
		cyannl("my.pop_front()");
		my.pop_front();
		print_contnl(my);
		cyannl("my.push_back(24)");
		my.push_back(24);
		print_contnl(my);
		cyannl("my.pop_back()");
		my.pop_back();
		print_contnl(my);

		purplenl("ori.push_front(42)");
		ori.push_front(42);
		print_contnl(ori);
		purplenl("ori.pop_front()");
		ori.pop_front();
		print_contnl(ori);
		purplenl("ori.push_back(24)");
		ori.push_back(24);
		print_contnl(ori);
		purplenl("ori.pop_back()");
		ori.pop_back();
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : insert T element at iterator position");
		cyannl("my.insert(my.end(), 21)");
		my.insert(my.end(), 21);
		print_contnl(my);

		purplenl("ori.insert(ori.end(), 21)");
		ori.insert(ori.end(), 21);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : insert(position, n, val)");
		cyannl("my.insert(my.begin(), 1, 44)");
		my.insert(my.end(), 4, 44);
		print_contnl(my);
		purplenl("ori.insert(ori.begin(), 1, 44)");
		ori.insert(ori.end(), 4, 44);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : insert(position, first, last)");
		cyannl("my.insert(my.begin(), ++my.begin(), my.end());");
		my.insert(my.begin(), ++my.begin(), my.end());
		print_contnl(my);
		purplenl("ori.insert(ori.begin(), ++ori.begin(), ori.end());");
		ori.insert(ori.begin(), ++ori.begin(), ori.end());
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : erase(position) test");
		cyannl("my.erase(--(my.end()))");
		my.erase(--my.end());
		print_contnl(my);

		purplenl("ori.erase(--(ori.end()))");
		ori.erase(--ori.end());
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : erase(first, last)");
		ft::list<int>::iterator my_itr = my.end();
		for (int i = 0; i < 3; i++) { --my_itr; }

		std::list<int>::iterator ori_itr = ori.end();
		for (int i = 0; i < 3; i++) { --ori_itr; }

		cyannl("my.erase(my.end() - 3, my.end())");
		my.erase(my_itr, my.end());
		print_contnl(my);

		purplenl("ori.erase(my.end() - 3, ori.end())");
		ori.erase(ori_itr, ori.end()); 
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : splicing an element from cont at given position");
		ft::list<int> my2(3, 42);
		cyan("ft::list<int> my2(3, 42) : "); print_contnl(my2);
		cyan("my : "); print_contnl(my);
		my.splice(my.end(), my2, my2.begin());
		cyannl("after my.splice(my.end(), my2, my2.begin())");
		cyan("my2 : "); print_contnl(my2);
		cyan("my : "); print_contnl(my);

		std::list<int> ori2(3, 42);
		purple("ft::list<int> ori2(3, 42) : "); print_contnl(ori2);
		purple("ori : "); print_contnl(ori);
		cyannl("after ori.splice(ori.end(), ori2, ori2.begin())");
		ori.splice(ori.end(), ori2, ori2.begin());
		purple("ori2 : "); print_contnl(ori2);
		purple("ori : "); print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : splicing a whole other container");
		cyannl("Before :");
		cyan("my2 : "); print_contnl(my2);
		cyan("my : "); print_contnl(my);
		cyannl("after my.splice(my.end(), my2");
		my.splice(my.end(), my2);
		cyan("my2 : "); print_contnl(my2);
		cyan("my : "); print_contnl(my);

		purplenl("After");
		purple("ori2 : "); print_contnl(ori2);
		purple("ori : "); print_contnl(ori);
		purplenl("ori.splice(ori.end(), ori2)");
		ori.splice(ori.end(), ori2);
		purple("ori2 : "); print_contnl(ori2);
		purple("ori : "); print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : remove value from container");
		cyannl("my.remove(44)");
		my.remove(44);
		print_contnl(my);
		purplenl("ori.remove(44)");
		ori.remove(44);
		print_contnl(ori);

		cyannl("my.remove(42)");
		my.remove(42);
		print_contnl(my);
		purplenl("ori.remove(42)");
		ori.remove(42);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : remove from container according to predicate");
		cyannl("my.remove_if(predicate_true_over_12)");
		my.remove_if(predicate_true_over_12);
		print_contnl(my);

		purplenl("ori.remove_if(remove_over)");
		ori.remove_if(predicate_true_over_12);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : sort test");
		cyannl("my.sort()");
		print_contnl(my);
		my.sort();
		print_contnl(my);
		purplenl("ori.sort()");
		print_contnl(ori);
		ori.sort();
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : unique");
		cyannl("my before : ");
		print_contnl(my); 
		cyannl("my.unique()");
		my.unique();
		print_contnl(my);

		purplenl("ori before : "); print_contnl(ori);
		purplenl("ori.unique()");
		ori.unique();
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : merge two containers");
		for(int i = 1; i < 10; i += 2)
		{
			my2.push_back(i); ori2.push_back(i);
		}
		cyan("my : "); print_contnl(my);
		cyan("my2 : "); print_contnl(my2);
		my.merge(my2);
		cyannl("after my.merge(my2), my : "); print_contnl(my);

		std::cout << "\n";
		purple("ori : "); print_contnl(ori);
		purple("ori2 : "); print_contnl(ori2);
		ori.merge(ori2);
		purplenl("after ori.merge(ori2), ori : "); print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : merge two sorted lists");
		for(int i = 1; i < 12; i += 3)
		{
			my2.push_back(i); ori2.push_back(i);
		}
		my.unique(); ori.unique();

		cyannl("my"); print_contnl(my);
		cyannl("my2"); print_contnl(my2);
		cyannl("my.merge(my2, less_than)");
		my.merge(my2, less_than);
		print_contnl(my);

		purplenl("ori"); print_contnl(ori);
		purplenl("ori2"); print_contnl(ori2);
		purplenl("ori.merge(ori2, less_than");
		ori.merge(ori2, less_than);
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("Method : reverse");
		cyannl("my.reverse()");
		my.reverse();
		print_contnl(my);
		purplenl("ori.reverse()");
		ori.reverse();
		print_contnl(ori);
		//--------------------------------------------------------------------
		highlight("clear test");
		my.clear();
		cyannl("my.clear()");
		cyan("my : "); print_contnl(my);
		std::cout << "my size: " << my.size() << std::endl;

		std::cout << "\n";
		ori.clear();
		purplenl("ori.clear()");
		purple("ori : "); print_contnl(ori);
		std::cout << "o size: " << ori.size() << std::endl;
	}
}
