#ifndef TYPE_TRAITS
# define TYPE_TRAITS

# include <cstddef>
# include <typeinfo>
# include <limits>
# include "cpp_type_traits.hpp"

namespace ft
{
	/*
	 * ========== ENABLE_IF ==========
	 * Ensures at compile-time that parameterized types contain certain traits.
	 */

	// Define a nested type if some predicate holds.
	template<bool, typename>
	struct enable_if 
	{ };

	template<typename Tp>
	struct enable_if<true, Tp>
	{ typedef Tp type; };

	// Conditional expression for types. If true, first, if false, second.
	template<bool Cond, typename Iftrue, typename Iffalse>
	struct conditional_type
	{ typedef Iftrue type; };

  template<typename Iftrue, typename Iffalse>
	struct conditional_type<false, Iftrue, Iffalse>
	{ typedef Iffalse type; };


	// Given an integral builtin type, return the corresponding unsigned type.
	template<typename Tp>
	struct add_unsigned
	{ 
		private:
			typedef enable_if<is_integer<Tp>::value, Tp> if_type;
		public:
			typedef typename if_type::type type; 
	};

	template<>
	struct add_unsigned<char>
	{ typedef unsigned char type; };

	template<>
	struct add_unsigned<signed char>
	{ typedef unsigned char type; };

	template<>
	struct add_unsigned<short>
	{ typedef unsigned short type; };

	template<>
	struct add_unsigned<int>
	{ typedef unsigned int type; };

	template<>
	struct add_unsigned<long>
	{ typedef unsigned long type; };

	template<>
	struct add_unsigned<long long>
	{ typedef unsigned long long type; };

	// Declare but don't define.
	template<>
	struct add_unsigned<bool>;

	template<>
	struct add_unsigned<wchar_t>;


	// Given an integral builtin type, return the corresponding signed type.
	template<typename Tp>
	struct remove_unsigned
	{ 
		private:
			typedef enable_if<is_integer<Tp>::value, Tp> if_type;
		public:
			typedef typename if_type::type type; 
	};

	template<>
	struct remove_unsigned<char>
	{ typedef signed char type; };

	template<>
	struct remove_unsigned<unsigned char>
	{ typedef signed char type; };

	template<>
	struct remove_unsigned<unsigned short>
	{ typedef short type; };

	template<>
	struct remove_unsigned<unsigned int>
	{ typedef int type; };

	template<>
	struct remove_unsigned<unsigned long>
	{ typedef long type; };

	template<>
	struct remove_unsigned<unsigned long long>
	{ typedef long long type; };

	// Declare but don't define.
	template<>
	struct remove_unsigned<bool>;

	template<>
	struct remove_unsigned<wchar_t>;

	// For use in string and vstring.
	template<typename Type>
	inline bool
	is_null_pointer(Type* ptr)
	{ return ptr == 0; }

	template<typename Type>
	inline bool
	is_null_pointer(Type)
	{ return false; }

	// For complex and cmath
	template<typename Tp, bool = is_integer<Tp>::value>
	struct promote
	{ typedef double type; };

#endif // TYPE_TRAITS
