#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include "iterators.hpp"
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
			typedef ft::iterator_traits<iterator>::difference_type	difference_type;

		private:
			allocator_type									_alloc;
			pointer											_start;
			pointer											_end;
			pointer											_memend;

		public:
			explicit vector(const allocator_type & alloc)
			: _alloc(alloc), _start(nullptr), _end(nullptr), _memend(nullptr) {}

			explicit vector(size_type n, const value_type & val = value_type(),
							cons allocator_type & alloc = allocator_type())
			: _alloc(alloc), _start(nullptr), _end(nullptr), _memend(nullptr) {}
			{
				_start = _alloc.allocate(n); _memend = _start + n;
				_end = start;
				size_type i = 0; while (i++ < n) { _alloc.construct(_end++, val); }
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type & alloc = allocator_type(),
					typename ft::enable_if<
									!ft::is_integral<InputIterator>::value, InputIterator
								>::type * = nullptr)
			: _alloc(alloc), _start(nullptr), _end(nullptr), _memend(nullptr) {}
			{
				_start = _alloc.allocate(n); _memend = _start + n;
				_end = start;
				iterator itr = first;
				while (itr != last) { _alloc.construct(_end++, (*first)++); }
			}

			vector (const vector & other)
			: _alloc(other.alloc), _start(other._start), _end(other._end),
				_memend(other._memend)
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
			}

			iterator begin() { return (_start); }
			const_iterator begin() const { return (_start); }
			iterator end() { return (_start); }
			const_iterator begin() const { return (_start); }

			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return reverse_iterator(begin()); }

			size_type size(void) { return (_end - _start); }

			void clear()
			{
				pointer ptr = _start;
				while (ptr != _end) { _alloc.destroy(ptr++); }
			}
	}
}; // namespace ft


#endif
