#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iostream>

namespace ft
{
//============================================================================
	// ========== Iterator ==========
	// base class template used to derive iterator classes. Provides typedefs.
	template
	<
		class Category, // for holding iterator tags
		class T, // type representing the difference between two itr
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	>
	struct Iterator
	{
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
		typedef Category		iterator_category;
	};

//============================================================================
	// ========== Iterator_traits ==========
	// provides uniform interface to the properties of LegacyIterator types.
	// This makes possible to implement algorithms only in terms of iterators. 
	// This template can be specialized for user-defined iterators so that
	// info about the iterator is retrievable even when the type doesn't
	// provide the usual typedefs
	template <class Iterator>
	class Iterator_traits
	{
		public:
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};
	template <class T>
	class Iterator_traits<T *>
	{
		public:
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef T *							pointer;
			typedef T &							reference;
			typedef Random_access_iterator_tag	iterator_category;
	};
	template <class T>
	class Iterator_traits<const T *>
	{
		public:
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef const T *					pointer;
			typedef const T &					reference;
			typedef Random_access_iterator_tag	iterator_category;
	};

	// ========== Iterator_tags ==========
	// Empty classes definitions to serve as identifier as to what
	// set of operations an iterator is capable of.
	// From least to most powerful :
	struct Input_iterator_tag {};			// read + increment (single pass)
	struct Forward_iterator_tag {};			// + increment (multiple passes)
	struct Bidirectional_iterator_tag {};	// + decrement
	struct Random_access_iterator_tag {};	// + random access
	struct Output_iterator_tag {};			// write + increment (single pass)

//============================================================================

	// ========== list iterator ==========
	// 


}

#endif //ITERATORS_HPP
