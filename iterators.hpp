#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iostream>

namespace ft
{
	// ITERATOR BASE CLASS :
	// Base template class that will be used to derive iterator classes.
	// Defines types that are used in the iterator_traits template class
	// to generate the appropriate instantiation automatically.
	template <
		class Category, // will hold an iterator tag
		class T, // type of elements pointed to by the iterator
		class Distance = std::ptrdiff_t, // type of diff between two itr
		class Pointer = T*, // pointer to an elem pointed to by the itr
		class Reference = T& // ref to an elem pointed to by the itr
	> class iterator
	{
		public:
			typedef T				value_type;
			typedef Distance		difference_type;
			typedef Pointer			pointer;
			typedef Reference		reference;
			typedef Category		iterator_category;
	};

	// ITERATOR TAGS :
	// Empty classes definitions that serve as identifiers for iterators
	// that can provide particular operations. From least to most powerful :
	class input_iterator_tag {}; // read + increment (single pass)
	class forward_iterator_tag {}; // + increment (multiple passes)
	class bidirectional_iterator_tag {}; // + decrement
	class random_access_iterator_tag {}; // + random access
	// iterators that fall in the above categories and also meet the below
	// requirements are called mutable iterators
	class output_iterator_tag {}; // write + increment (single pass)
	// todo : implement iterator derivated classes and write them down

} // namespace ft


#endif //ITERATORS_HPP
