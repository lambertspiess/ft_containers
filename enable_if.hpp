#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft {

	/*
	 * The enable_if idiom allows for the checking at compile-time of arbitrary
	 * properties of parameterized types
	 */
	template <bool B, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> // If the condition is true, define the type T
	{
		typedef T type;
	};

	// is_integral : return true if the type T is integral
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

	template <typename value_type>
	bool less_than(value_type const &a, value_type const &b)
	{
		return (a < b);
	}

}; //namespace ft

#endif // ENABLE_IF_HPP
