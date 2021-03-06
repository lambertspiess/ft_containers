#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP
# include <cstddef>
# include "my_nullptr.hpp"
# include "iterators.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>
															_iter;
			typedef typename _iter::value_type				value_type;
			typedef typename _iter::difference_type			difference_type;
			typedef T *										pointer;
			typedef T &										reference;
		private:
			pointer											_elem;

		public:
			random_access_iterator(void)
			: _elem(my_nullptr) {}

			random_access_iterator(pointer elem)
			: _elem(elem) {}

			random_access_iterator(const random_access_iterator & src)
			: _elem(src._elem) {}

			random_access_iterator & operator=(const random_access_iterator & other)
			{
				if (*this == other) { return *this; }
				this->_elem = other._elem;
				return (*this);
			}

			virtual ~random_access_iterator() {}

			pointer base() const { return (this->_elem); }

			reference operator*(void) const { return (*_elem); }

			reference operator->(void) const { return (_elem); }

			random_access_iterator & operator++(void)
				{ _elem++; return (*this); }

			random_access_iterator operator++(int)
				{ random_access_iterator ret(*this); _elem++; return (ret); }

			random_access_iterator & operator--(void)
				{ _elem--; return (*this); }

			random_access_iterator operator--(int)
				{ random_access_iterator ret(*this); _elem--; return (ret); }

			random_access_iterator operator+(difference_type n) const
				{ return (_elem + n); }

			random_access_iterator & operator+=(difference_type n) const
				{ _elem += n; return (*this); }

			random_access_iterator & operator-=(difference_type n) const
				{ _elem -= n; return (*this); }

			reference operator[](difference_type n) const
				{ return (*(_elem + n)); }

	}; // random_access_iterator

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator==(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() == rhs.base()); }

	template <typename T, typename T_const>
	typename ft::random_access_iterator<T>::difference_type
		operator==(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T_const> rhs)
	{ return (lhs.base() == rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator!=(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() != rhs.base()); }

	template <typename T, typename T_const>
	typename ft::random_access_iterator<T>::difference_type
		operator!=(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T_const> rhs)
	{ return (lhs.base() != rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator<(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() < rhs.base()); }

	template <typename T, typename T_const>
	typename ft::random_access_iterator<T>::difference_type
		operator<(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T_const> rhs)
	{ return (lhs.base() < rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator<=(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() <= rhs.base()); }

	template<typename T, typename T_const>
	typename ft::random_access_iterator<T>::difference_type
		operator<=(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T_const> rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator>(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() > rhs.base()); }

	template <typename T, typename T_const>
	typename ft::random_access_iterator<T>::difference_type
		operator>(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T_const> rhs)
	{ return (lhs.base() > rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator>=(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <typename T, typename T_const>
	typename ft::random_access_iterator<T>::difference_type
		operator>=(const ft::random_access_iterator<T> lhs,
					const ft::random_access_iterator<T_const> rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>
		operator+(typename ft::random_access_iterator<T>::difference_type n,
					typename ft::random_access_iterator<T> & rhs)
	{
		return (rhs + n);
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator-(const ft::random_access_iterator<T> lhs,
				const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <typename T, typename T_const>
	typename ft::random_access_iterator<T>::difference_type
	operator-(const ft::random_access_iterator<T> lhs,
				const ft::random_access_iterator<T_const> rhs)
	{
		return (lhs.base() - rhs.base());
	}

}; // namespace ft

#endif // RANDOM_ACCESS_ITERATOR_HPP
