#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include "iterators.hpp"
# include "random_access_iterator.hpp"
# include "enable_if.hpp"
# include <iostream>

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class map
	{
		public:
			typedef T										value_type;
			typedef Alloc									allocator_type;;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef ft::random_access_iterator<value_type>	iterator;
			typedef ft::random_access_iterator<const value_type>
															const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>
															const_reverse_iterator;
			typedef typename Alloc::size_type				size_type;
			typedef typename ft::iterator_traits<iterator>::difference_type
															difference_type;

		private:
			allocator_type									_alloc;
			pointer											_start;
			pointer											_end;
			pointer											_memend;

		public:
			explicit list(const allocator_type & alloc = allocator_type())
			{}

			explicit map(size_type n, const value_type & val = value_type(),
							const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _start(nullptr), _end(nullptr), _memend(nullptr)
			{
				_start = _alloc.allocate(n); _memend = _start + n;
				_end = _start;
				size_type i = 0;
				while (i++ < n) { _alloc.construct(_end++, val); }
			}

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
					const allocator_type & alloc = allocator_type(),
					typename ft::enable_if<
									!ft::is_integral<InputIterator>::value, InputIterator
								>::type * = nullptr)
			: _alloc(alloc), _start(nullptr), _end(nullptr), _memend(nullptr)
			{
				difference_type n = ft::distance(first, last);
				_start = _alloc.allocate(n); _memend = _start + n;
				_end = _start;
				iterator itr = first;
				while (itr != last) { _alloc.construct(_end++, *itr); itr++; }
			}

			map (const map & other)
			: _alloc(other._alloc), _start(nullptr), _end(nullptr), _memend(nullptr)
			{
				insert(begin(), other.begin(), other.end());
			}

			~map()
			{
				if (_start != nullptr)
				{
					size_type nbytes = size();
					clear(); // destroy
					_alloc.deallocate(_start, nbytes);
				}
			}

			map & operator=(const map & other)
			{
				if (*this == other) { return *this; }
				clear(); insert(end(), other.begin(), other.end());
				return (*this);
			}

	}; // class map

	template <class T, class Alloc>
	bool operator==(const map<T, Alloc> & lhs, const map<T, Alloc> & rhs)
	{
		if (lhs.size() != rhs.size()) { return false; }
		typename map<T, Alloc>::size_type i = 0;
		while (i < lhs.size())
		{
			if (lhs[i] == rhs[i]) { ++i; } else  { return false; }
		}
		return true ;
	}

	template <class T, class Alloc>
	bool operator!=(const map<T, Alloc> & lhs, const map<T, Alloc> & rhs)
	{
		if (lhs.size() != rhs.size()) { return false; }
		typename map<T, Alloc>::size_type i = 0;
		while (i < lhs.size())
		{
			if (lhs[i] == rhs[i]) { ++i; } else  { return false; }
		}
		return true ;
	}

}; // namespace ft


#endif
