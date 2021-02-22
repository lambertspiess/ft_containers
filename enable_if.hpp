#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft {

	/*
	 * The enable_if idiom is used by the compiler to check if template
	 * types have certain predetermined properties.
	 * It is a form of type-checking but at compile time.
	 */

	// default state of enable_if : the type T isn't defined (doesn't compile)
	template <bool B, typename T = void>
	struct enable_if {};

	// if the predicate B is true, the type T is defined (can compile)
	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/*
	 * This is the predicate (and its specializations) used in place of 
	 * Bool B in the enable_if idiom. 
	 * They set the condition that the type T must verify.
	 */

	// The predicate is_integral evaluates to true if the type T is an
	// integral type
	template <typename T>
	struct is_integral
		{ static const bool value = false; };
	template <>
	struct is_integral<bool>
		{ static const bool value = true; };
	template <>
	struct is_integral<char>
		{ static const bool value = true; };
	template <>
	struct is_integral<wchar_t>
		{ static const bool value = true; };
	template <>
	struct is_integral<signed char>
		{ static const bool value = true; };
	template <>
	struct is_integral<short int>
		{ static const bool value = true; };
	template <>
	struct is_integral<int>
		{ static const bool value = true; };
	template <>
	struct is_integral<long int>
		{ static const bool value = true; };
	template <>
	struct is_integral<long long int>
		{ static const bool value = true; };
	template <>
	struct is_integral<unsigned char>
		{ static const bool value = true; };
	template <>
	struct is_integral<unsigned short int>
		{ static const bool value = true; };
	template <>
	struct is_integral<unsigned int>
		{ static const bool value = true; };
	template <>
	struct is_integral<unsigned long int>
		{ static const bool value = true; };
	template <>
	struct is_integral<unsigned long long int>
		{ static const bool value = true; };

	/*
	 * The less_than predicate is used by the list container for sorting
	 */

	template <typename value_type>
	bool less_than(value_type const &a, value_type const &b)
	{
		return (a < b);
	}

}; //namespace ft

#endif // ENABLE_IF_HPP
