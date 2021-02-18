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
	class vector
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
			explicit vector(const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _start(nullptr), _end(nullptr), _memend(nullptr)
			{}

			explicit vector(size_type n, const value_type & val = value_type(),
							const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _start(nullptr), _end(nullptr), _memend(nullptr)
			{
				_start = _alloc.allocate(n); _memend = _start + n;
				_end = _start;
				size_type i = 0;
				while (i++ < n) { _alloc.construct(_end++, val); }
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
				while (itr != last) { _alloc.construct(_end++, *itr); itr++; }
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

			iterator end()
			{
//				std::cout << "In end(), _end = " << _end << "\n";
				return (_end);
			}

			const_iterator end() const { return (_end); }

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
					size_type old_cap = capacity();
					_start = _alloc.allocate(n); _end = _start; _memend = _start + n;
					pointer swap, itr = old_start;
					while (itr != old_end)
					{
						swap = itr++;
						_alloc.construct(_end++, *swap);
					}
					_alloc.deallocate(old_start, old_cap);
				}
//				std::cout << "AFTER RESERVE" << "\n";
//				pointer ptr = _start;
//				while (ptr != _end)
//				{
//					std::cout << *ptr << ", "; ptr++;
//				}
//				std::cout << "\n";
			}

			void resize(size_type n, value_type val = value_type())
			{
				size_type cur = size();
				if (cur > n) { erase(begin() + n, end()); }
				if (cur < n) { insert(end(), n - cur, val); }
			}

			void clear() { erase(begin(), end()); }

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

			// handle assign
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
						typename ft::enable_if<
								!ft::is_integral<InputIterator>::value, InputIterator
											>::type * = nullptr)
			{
				clear();
				int i = 0;
				while (first != last)
				{
					insert(begin() + i, 1, *first); ++i; ++first;
				}
			}

			void assign(size_type n, const value_type & val)
				{ clear(); insert(end(), n, val); }

			void push_back(const value_type & val) { insert(end(), val); }

			void pop_back() { erase(--end()); }

			iterator insert(iterator pos, const value_type & val)
				{ insert(pos, 1, val); return (pos); }

			void insert(iterator position, size_type n, const value_type & val)
			{
				int dist_to_pos = &*position - _start;
				size_type newsize = size() + n;
				pointer pos = &*position;
				if (newsize > capacity())
				{
					reserve(newsize);
					pos = _start + dist_to_pos;
				}
				if (empty())
				{
					size_type i = 0;
					while (i < n)
						{ _alloc.construct(_start + i, val); i++; }
					_end = _start + n;
				}
				else
				{
					pointer old_end = _end; _end += n; pointer ptr = _end;
					if (old_end != pos)
					{
						while (old_end-- != pos)
							{ *(--ptr) = *old_end; _alloc.destroy(old_end); }
					}
					ptr = pos;
					while (n--)
						{ _alloc.construct(ptr++, val); }
				}
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<
									!ft::is_integral<InputIterator>::value, InputIterator
								>::type * = nullptr)
			{
				size_type n = distance(first, last);
				size_type newsize = size() + n;
				pointer pos = &*position;
				int dist_to_pos = pos - _start;
				if (newsize > capacity())
				{
					reserve(newsize); pos = _start + dist_to_pos;
				}
				if (empty())
				{
					size_type i = 0;
					while (i < n)
					{
						_alloc.construct(_start + i, *first); i++; first++;
					}
					_end = _start + n;
				}
				else
				{
					pointer old_end = _end; _end += n; pointer ptr = _end;
					if (old_end != pos)
					{
						while (old_end-- != pos)
						{
							*(--ptr) = *old_end; _alloc.destroy(old_end);
						}
					}
					ptr = pos;
					while (n--)
					{
						_alloc.construct(ptr++, *first); first++;
					}
				}
			}

			iterator erase(iterator position) { return erase(position, position + 1); }

			iterator erase(iterator first, iterator last)
			{
				size_type diff = ft::distance(first, last);
				iterator itr = first, tmp;
				while (itr != last)
				{
					tmp = itr; ++itr;
					_alloc.destroy(tmp.base());
				}
				itr = first;
				while (last != end())
				{
					_alloc.construct(itr.base(), *last);
					_alloc.destroy(last.base());
					++itr; ++last;
				}
				_end -= diff;
				return (first);
			}

			void swap(vector & other)
			{
				if (*this == other) { return ; }

				allocator_type		swap_alloc = other._alloc;
				pointer				swap_start = other._start;
				pointer				swap_end = other._end;
				pointer				swap_memend = other._memend;

				other._alloc = this->_alloc;
				other._start = this->_start;
				other._end = this->_end;
				other._memend = this->_memend;

				this->_alloc = swap_alloc;
				this->_start = swap_start;
				this->_end = swap_end;
				this->_memend = swap_memend;
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
