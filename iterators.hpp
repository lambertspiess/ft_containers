#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iostream>

namespace ft
{
	// *** ITERATOR BASE CLASS ***
	// Base template class that will be used to derive iterator classes.
	// Defines types that are used in the iterator_traits template class
	// to generate the appropriate instantiation automatically.
	template
	<
		class Category, // will hold an iterator tag
		class T, // type of elements pointed to by the iterator
		class Distance = std::ptrdiff_t, // type of diff between two itr
		class Pointer = T*, // pointer to an elem pointed to by the itr
		class Reference = T& // ref to an elem pointed to by the itr
	>
	class Iterator
	{
		public:
			typedef T				value_type;
			typedef Distance		difference_type;
			typedef Pointer			pointer;
			typedef Reference		reference;
			typedef Category		iterator_category;
	};

	// *** ITERATOR TRAITS ***
	// Empty classes definitions that serve as identifiers for categories
	// of iterators that can provide particular operations.
	// From least to most powerful :
	class Input_iterator_tag {};			// read + increment (single pass)
	class Forward_iterator_tag {};			// + increment (multiple passes)
	class Bidirectional_iterator_tag {};	// + decrement
	class Random_access_iterator_tag {};	// + random access
	// nb : iterators that fall in the above categories and also meet the
	// below requirements are called mutable iterators :
	class Output_iterator_tag {};			// write + increment (single pass)
	// todo : implement iterator derivated classes

	template <class T>
	class Bidirectional_iterator :
	public ft::Iterator<ft::Bidirectional_iterator_tag, T>
	{
		public: //qualifying inherited types...
			using typename ft::Iterator<ft::Bidirectional_iterator_tag, T>::
																value_type;
			using typename ft::Iterator<ft::Bidirectional_iterator_tag, T>::
															difference_type;
			using typename ft::Iterator<ft::Bidirectional_iterator_tag, T>::
																	pointer;
			using typename ft::Iterator<ft::Bidirectional_iterator_tag, T>::
																	reference;
			using typename ft::Iterator<ft::Bidirectional_iterator_tag, T>::
															iterator_category;
		private:
			pointer _elem;
	};

	template <class T>
	class Reverse_iterator
	{
	};

	template <class T>
	class List_iterator
	{
	};
} // namespace ft


#endif //ITERATORS_HPP
