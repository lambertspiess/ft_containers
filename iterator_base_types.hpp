#ifndef ITERATOR_BASE_UTILS_HPP
# define ITERATOR_BASE_UTILS_HPP

# include <cstddef>

namespace ft
{
	/*
	 * ========== ITERATOR BASE TYPES ==========
	 * general iterator-related utility types
	 */
	/*
	 * iterator_tags :
	 * Empty types used to categorize iterators. Used by underlying STL 
	 * algorithms to determine if they can be used on a given iterator.
	 */
	struct output_iterator_tag {};
	struct input_iterator_tag {};
	// forward iterators support a superset of input iterator operations :
	struct forward_iterator_tag : public input_iterator_tag {};
	// bidirectional iterators support a superset of forward iterator
	// operations :
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	// random-access iterators support a superset of bidirectional iterator
	// operations :
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/*
	 * templates to check the tag of an iterator
	 */
	template <bool Condition, typename T>
	struct tag_is
	{
		typedef T type;
		const static bool vaa// lala
	}

	template <typename T>
	struct has_input_iterator_tag : public

	/*
	 * iterator :
	 * Provides nested typedefs that iterator classes will inherit.
	 * They will be used in template specialisation and overloading.
	 */
	template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
			typename _Pointer = _Tp*, typename _Reference = _Tp&>
	struct iterator
	{
		// holds an X_iterator_tag
		typedef _Category	iterator_category;
		// type representing the type of elem the iterator points to
		typedef _Tp			value_type;
		typedef _Distance  difference_type; // type representing a distance between two iterators
		typedef _Pointer	pointer; // type representing a  pointer-to-value_type.
		typedef _Reference reference; // type representing a reference-to-value_type.
	};

	/*
	 * iterator_traits :
	 * Simply "forwards" the nested typedefs from the Iterator template
	 * parameter. Syntaxic sugar.
	 */
	template <typename _Iterator>
	struct iterator_traits
	{
		typedef typename _Iterator::iterator_category		iterator_category;
		typedef typename _Iterator::value_type				value_type;
		typedef typename _Iterator::difference_type			difference_type;
		typedef typename _Iterator::pointer					pointer;
		typedef typename _Iterator::reference				reference;
	};
	template <typename _Tp>
	struct iterator_traits<_Tp*>
	{
		typedef random_access_iterator_tag			iterator_category;
		typedef _Tp									value_type;
		typedef ptrdiff_t							difference_type;
		typedef _Tp *								pointer;
		typedef _Tp &								reference;
	};
	template <typename _Tp>
	struct iterator_traits<const _Tp*>
	{
		typedef random_access_iterator_tag			iterator_category;
		typedef _Tp									value_type;
		typedef ptrdiff_t							difference_type;
		typedef _Tp *								pointer;
		typedef _Tp &								reference;
	};

	/*
	 * Access an iterator's tag easily. This is purely syntax.
	 */
	template <typename _Iter>
	inline typename iterator_traits<_Iter>::iterator_category __iterator_category(const _Iter &)
	{
		return typename iterator_traits<_Iter>::iterator_category();
	}


	/*
	 * ========== ENABLE_IF ========== 
	 * This is a SFINAE-based constraint. Blocks compilation of templates
	 * if the parameterized type doesn't fulfill the condition B.
	 * This is achieved by not declaring the typedef T type when the 
	 * condition isn't met. Used notably when instantiating Iterators.
	 */

	template<bool B, class T = void>
	struct enable_if
	{};
	template<class T>
	struct enable_if<true, T>
	{ typedef T type; };

	/*
	 * ========== TYPE CHECKING ========== 
	 * Templates used in conjunction with enable_if to do compile-time
	 * type-checking
	 */

	/*
	 * is_integral : Checks whether T is an integral type. This is achieved by
	 * setting the static member constant value to true if T is integral,
	 * false otherwise.
	 */
	template <bool is_integral, typename T>
	struct is_integral_

} // namespace ft

#endif // ITERATOR_BASE_FUNC_HPP
