#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include "iterators.hpp"
# include "random_access_iterator.hpp"
# include "enable_if.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T										value_type;
			typedef Alloc									allocator_type;;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef ft::random_access_iterator<T>			iterator;
			typedef ft::random_access_iterator<const T>		const_iterator;
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
			explicit vector(const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _start(nullptr), _end(nullptr), _memend(nullptr) {}

			explicit vector(size_type n, const value_type & val = value_type(),
							const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _start(nullptr), _end(nullptr), _memend(nullptr)
			{
				_start = _alloc.allocate(n); _memend = _start + n;
				_end = _start;
				size_type i = 0; while (i++ < n) { _alloc.construct(_end++, val); }
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
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
				while (itr != last) { _alloc.construct(_end++, (*first)++); }
			}

			vector (const vector & other)
			: _alloc(other._alloc), _start(nullptr), _end(nullptr), _memend(nullptr)
			{
				insert(begin(), other.begin(), other.end());
			}

			~vector()
			{
				if (_start != nullptr)
				{
					size_type nbytes = size();
					clear(); // destroy
					_alloc.deallocate(_start, nbytes);
				}
			}

			vector & operator=(const vector & other)
			{
				if (*this == other) { return *this; }
				clear(); insert(end(), other.begin(), other.end());
				return (*this);
			}

			iterator begin() { return (_start); }
			const_iterator begin() const { return (_start); }
			iterator end() { return (_start); }
			const_iterator end() const { return (_start); }

			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return reverse_iterator(begin()); }

			size_type size(void) const { return (_end - _start); }

			size_type max_size(void) const { return (allocator_type().max_size()); }

			size_type capacity(void) const { return (_memend - _start); }

			bool empty(void) const { return (size() == 0 ? true : false); }

			void reserve(size_type n)
			{
				if (n > max_size()) { throw (std::length_error("vector::reserve")); }
				else if (n > capacity())
				{
					pointer old_start = _start, old_end = _end;
					size_type old_capacity = capacity();
					_start = _alloc.allocate(n);
					_end = _start; _memend =  _start + n;
					pointer swap, itr = old_start;
					while (itr != old_end)
					{
						swap = itr++;
						_alloc.construct(_end++, *swap);
						_alloc.destroy(swap);
					}
					_alloc.deallocate(old_start, old_capacity);
				}
			}

			void resize(size_type n, value_type val = value_type())
			{
				size_type cur = size();
				if (cur > n) { erase(begin() + n, end()); }
				if (cur < n) { insert(end(), n - cur, val); }
			}

			void clear()
			{
				pointer ptr = _start;
				while (ptr != _end) { _alloc.destroy(ptr++); }
			}

			reference operator[] (size_type n) { return(_start[n]); }
			const_reference operator[] (size_type n) const { return(_start[n]); }
			reference at(size_type n)
			{
				if (n >= size()) { throw std::out_of_range("out of range"); }
				return (_start[n]);
			}
			const_reference at(size_type n) const
			{
				if (n >= size()) { throw std::out_of_range("out of range"); }
				return (_start[n]);
			}
			reference front() { return (*begin()); }
			const_reference front() const { return (*begin()); }
			reference back() { return (*--end()); }
			const_reference back() const { return (*--end()); }

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
						typename ft::enable_if<
									!ft::is_integral<InputIterator>::value, InputIterator
											>::type * = nullptr)
			{
				clear();
				while (first != last) { insert(_end++, 1, (*first)++); }
			}

			void assign(size_type n, const value_type & val)
			{
				clear(); if (capacity() < n) { reserve(n); }
				insert(end(), n, val);
			}

			void push_back(const value_type & val) { insert(end(), val); }
			void pop_back() { erase(--end()); }

			iterator insert(iterator pos, const value_type & val)
				{ insert(pos, 1, val); return (pos); }

			void insert(iterator position, size_type n, const value_type & val)
			{
				if (size() + n > capacity())
				{
					pointer old_start = _start, old_end = _end;
					size_type old_size = size(), old_capacity = capacity();
					_start = _alloc.allocate(old_size + n);
					_end = _start; _memend = _start + old_size + n;
					pointer tmp;
					while (old_start != old_end)
					{
						if (old_start == position.base())
						{
							while (n-- > 0) { _alloc.construct(_end++, val); }
						}
						tmp = old_start++;
						_alloc.construct(_end++, *tmp);
						_alloc.destroy(tmp);
					}
					_alloc.deallocate(old_start, old_capacity);
				}
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<
									!ft::is_integral<InputIterator>::value, InputIterator
								>::type * = nullptr)
			{
				size_type n = distance(first, last);
				if (size() + n > capacity())
				{
					pointer old_start = _start, old_start_save = _start, old_end = _end;
					size_type old_size = size(), old_capacity = capacity();
					_start = _alloc.allocate(old_size + n);
					_end = _start; _memend = _start + old_size + n;
					pointer tmp;
					while (old_start != old_end)
					{
						if (old_start == position.base())
						{
							while (first != last)
							{
								_alloc.construct(_end++, *first);
								++first;
							}
						}
						tmp = old_start++;
						_alloc.construct(_end++, *tmp);
						_alloc.destroy(tmp);
					}
					_alloc.deallocate(old_start_save, old_capacity);
				}
			}

			iterator erase(iterator position) { return erase(position, position + 1); }

			iterator erase(iterator first, iterator last)
			{
				iterator itr = first, tmp;
				while (itr != last) { tmp = itr++; _alloc.destroy(tmp.base()); }
				if (last != end())
				{
					iterator old_end = end(); _end = first.base();
					while (last != old_end)
					{
						tmp = last++;
						_alloc.construct(_end++, *tmp);
						_alloc.destroy(tmp.base());
					}
				}
				return (first);
			}

	}; // class vector

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		if (lhs.size() != rhs.size()) { return false; }
		typename vector<T, Alloc>::size_type i = 0;
		while (i < lhs.size())
		{
			if (lhs[i] == rhs[i]) { ++i; } else  { return false; }
		}
		return true ;
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		if (lhs.size() != rhs.size()) { return false; }
		typename vector<T, Alloc>::size_type i = 0;
		while (i < lhs.size())
		{
			if (lhs[i] == rhs[i]) { ++i; } else  { return false; }
		}
		return true ;
	}

}; // namespace ft


#endif
