/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 14:36:56 by sanam             #+#    #+#             */
/*   Updated: 2021/01/23 23:55:15 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../list.hpp"
#include <list>
#include <random>
#include <iostream>
#include "test.hpp"

template <typename L>
void print(L& l)
{
	std::cout << "\033[1;36;40m==================================\033[0m\n";
	typename L::iterator it = l.begin();
	for (; it != l.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n\033[1;36;40m==================================\033[0m" << std::endl;
}

int main()
{
	{
		title("Default construct test");
		blue("ft::list<int> my");
		ft::list<int> m;
		print(m);

		yellow("std::list<int> o");
		std::list<int> o;
		print(o);


		title("fill constructor test");
		blue("ft::list<int> fill(10, 10)");
		ft::list<int> fill(10, 10);
		print(fill);

		yellow("std::list<int> ofill(10, 10)");
		std::list<int> ofill(10, 10);
		print(ofill);

		blue("m, o push_back 0 to 9");
		for (int i = 0; i < 10; ++i) {
			m.push_back(i);
			o.push_back(i);
		}
		print(m);

		title("range constructor test");
		blue("ft::list<int> range(m.begin(), m.end())");
		ft::list<int> range(m.begin(), m.end());
		print(range);

		yellow("std::list<int> orange(o.begin(), o.end())");
		ft::list<int> orange(o.begin(), o.end());
		print(orange);

		title("Copy constructor test");
		blue("ft::list<int> copy(m)");
		ft::list<int> copy(m);
		print(copy);
		yellow("std::list<int> ocopy(0)");
		std::list<int> ocopy(o);
		print(ocopy);

		title("empty and size check");
		std::cout << "m.size(): " << m.size() << std::endl;
		std::cout << "o.size(): " << o.size() << std::endl;
		if (m.empty())
			std::cout << "empty" << std::endl;
		else
			std::cout << "Not empty" << std::endl;

		title("max size");
		std::cout << "m.max_size(): " << m.max_size() << std::endl;
		std::cout << "o.max_size(): " << o.max_size() << std::endl;

		title("front and back test");
		std::cout << "m.front(): " << m.front() << " m.back(): " << m.back() << std::endl;
		std::cout << "o.front(): " << o.front() << " o.back(): " << o.back() << std::endl;

		title("push_front and pop_front test");
		blue("m.push_front(100)");
		m.push_front(100);
		print(m);
		blue("m.pop_front()");
		m.pop_front();
		print(m);

		yellow("o.push_front(100)");
		o.push_front(100);
		print(o);
		yellow("o.pop_front()");
		o.pop_front();
		print(o);

		title("push_back and pop_back test");
		blue("m.push_back(100)");
		m.push_back(100);
		print(m);
		blue("m.pop_back()");
		m.pop_back();
		print(m);

		yellow("o.push_back(100)");
		o.push_back(100);
		print(o);
		yellow("o.pop_back()");
		o.pop_back();
		print(o);

		title("single element insert(position, val)");
		blue("m.insert(m.end(), 30)");
		m.insert(m.end(), 30);
		print(m);

		yellow("o.insert(o.end(), 30)");
		o.insert(o.end(), 30);
		print(o);

		title("fill insert(position, n, val)");
		blue("m.insert(m.begin(), 5, 55)");
		m.insert(m.begin(), 5, 55);
		print(m);
		yellow("o.insert(o.begin(), 5, 55)");
		o.insert(o.begin(), 5, 55);
		print(o);

		title("range insert(position, first, last)");
		blue("m.insert(m.begin(), ++m.begin(), m.end());");
		m.insert(m.begin(), ++m.begin(), m.end());
		print(m);
		yellow("o.insert(o.begin(), ++o.begin(), o.end());");
		o.insert(o.begin(), ++o.begin(), o.end());
		print(o);


		title("erase(position) test");
		blue("m.erase(m.end())");
		m.erase(--m.end());
		print(m);
		yellow("o.erase(o.end())");
		o.erase(--o.end());
		print(o);


		title("erase(first, last) test");
		ft::list<int>::iterator ftIter = m.begin();
		ftIter++; ftIter++; ftIter++; ftIter++;

		std::list<int>::iterator stdIter = o.begin();
		stdIter++; stdIter++; stdIter++; stdIter++;

		blue("m.erase(m.begin(), begin + 5)");
		m.erase(m.begin(), ftIter);
		print(m);

		yellow("o.erase(o.begin(), begin + 5)");
		o.erase(o.begin(), stdIter);
		print(o);

		title("sigle element splice(position, x, i)");
		ft::list<int> m2(5, 123);
		print(m2);
		blue("m.splice(m.end(), m2, m2.begin())");
		m.splice(m.end(), m2, m2.begin());
		print(m);

		std::list<int> o2(5, 123);
		print(o2);
		blue("o.splice(o.end(), o2, o2.begin())");
		o.splice(o.end(), o2, o2.begin());
		print(o);

		title("entire splice test");
		blue("m.splice(m.end(), m2)");
		m.splice(m.end(), m2);
		print(m);

		yellow("o.splice(o.end(), o2)");
		o.splice(o.end(), o2);
		print(o);

		title("remove test");
		blue("m.remove(123)");
		m.remove(123);
		print(m);
		yellow("o.remove(123)");
		o.remove(123);
		print(o);

		blue("m.remove(55)");
		m.remove(55);
		print(m);
		yellow("o.remove(55)");
		o.remove(55);
		print(o);

		title("remove_if test (remove if ele over 15)");
		blue("m.remove_if(remove_over)");
		m.remove_if(remove_over);
		print(m);

		yellow("o.remove_if(remove_over)");
		o.remove_if(remove_over);
		print(o);

		title("sort test");
		blue("m.sort()");
		m.sort();
		print(m);
		yellow("o.sort()");
		o.sort();
		print(o);

		title("unique test");
		blue("m.unique()");
		m.unique();
		print(m);

		yellow("o.unique()");
		o.unique();
		print(o);

		title("merge test");
		for(int i = 1; i < 10; i += 2)
		{
			m2.push_back(i);
			o2.push_back(i);
		}
		blue("m2 and o2");
		print(m2);
		print(o2);
		blue("m.merge(m2)");
		m.merge(m2);
		print(m);
		yellow("o.merge(o2)");
		o.merge(o2);
		print(o);

		title("merge test2");
		m.unique();
		o.unique();
		for(int i = 1; i < 10; i += 2)
		{
			m2.push_back(i);
			o2.push_back(i);
		}
		blue("m.merge(m2, comp)");
		m.merge(m2, comp);
		print(m);
		yellow("o.merge(o2, comp)");
		o.merge(o2, comp);
		print(o);

		title("reverse test");
		blue("m.reverse()");
		m.reverse();
		print(m);
		yellow("o.reverse()");
		o.reverse();
		print(o);

		title("clear test");
		blue("m.clear()");
		m.clear();
		std::cout << "m size: " << m.size() << std::endl;
		yellow("o.clear()");
		o.clear();
		std::cout << "o size: " << o.size() << std::endl;
	}
}
