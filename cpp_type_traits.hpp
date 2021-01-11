# ifndef CPP_TYPE_TRAITS_H
# define CPP_TYPE_TRAITS_H

# include "type_traits.hpp"

namespace ft
{
	struct true_type { };
	struct false_type { };

	template<bool>
    struct truth_type
    { typedef false_type type; };

	template<>
    struct truth_type<true>
    { typedef true_type type; };

  // N.B. The conversions to bool are needed due to the issue
  // explained in c++/19404.
	template<class Sp, class Tp>
    struct traitor
    {
      enum { value = bool(Sp::value) || bool(Tp::value) };
      typedef typename truth_type<value>::type type;
    };

  // Compare for equality of types.
	template<typename, typename>
	struct are_same
	{
		enum { value = 0 };
		typedef false_type type;
	};

	template<typename Tp>
	struct are_same<Tp, Tp>
	{
		enum { value = 1 };
		typedef true_type type;
	};

	// Holds if the template-argument is a void type.
	template<typename Tp>
	struct is_void
	{
		enum { value = 0 };
		typedef false_type type;
	};

	template<>
	struct is_void<void>
	{
		enum { value = 1 };
		typedef true_type type;
	};

//
// Integer types
//
	template<typename Tp>
	struct is_integer
	{
		enum { value = 0 };
		typedef false_type type;
	};

// Thirteen specializations (yes there are eleven standard integer
// types; <em>long long</em> and <em>unsigned long long</em> are
// supported as extensions).  Up to four target-specific int<N>
// types are supported as well.
template<>
	struct is_integer<bool>
	{
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<char>
	{
		enum { value = 1 };
		typedef true_type type;
	};

template<>
struct is_integer<signed char>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
  struct is_integer<unsigned char>
  {
    enum { value = 1 };
    typedef true_type type;
  };

  template<>
    struct is_integer<short>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_integer<unsigned short>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_integer<int>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_integer<unsigned int>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_integer<long>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_integer<unsigned long>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_integer<long long>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_integer<unsigned long long>
    {
      enum { value = 1 };
      typedef true_type type;
    };

//#define INT_N(TYPE) 			\
//  template<>				\
//    struct is_integer<TYPE>		\
//    {					\
//      enum { value = 1 };		\
//      typedef true_type type;	\
//    };					\
//  template<>				\
//    struct is_integer<unsigned TYPE>	\
//    {					\
//      enum { value = 1 };		\
//      typedef true_type type;	\
//    };
//
//#ifdef GLIBCXX_TYPE_INT_N_0
//INT_N(GLIBCXX_TYPE_INT_N_0)
//#endif
//#ifdef GLIBCXX_TYPE_INT_N_1
//INT_N(GLIBCXX_TYPE_INT_N_1)
//#endif
//#ifdef GLIBCXX_TYPE_INT_N_2
//INT_N(GLIBCXX_TYPE_INT_N_2)
//#endif
//#ifdef GLIBCXX_TYPE_INT_N_3
//INT_N(GLIBCXX_TYPE_INT_N_3)
//#endif
//
//#undef INT_N

  //
  // Floating point types
  //
  template<typename Tp>
    struct is_floating
    {
      enum { value = 0 };
      typedef false_type type;
    };

  // three specializations (float, double and 'long double')
  template<>
    struct is_floating<float>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_floating<double>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_floating<long double>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  //
  // Pointer types
  //
  template<typename Tp>
    struct is_pointer
    {
      enum { value = 0 };
      typedef false_type type;
    };

  template<typename Tp>
    struct is_pointer<Tp*>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  //
  // An arithmetic type is an integer type or a floating point type
  //
  template<typename Tp>
    struct is_arithmetic
    : public traitor<is_integer<Tp>, is_floating<Tp> >
    { };

  //
  // A scalar type is an arithmetic type or a pointer type
  // 
  template<typename Tp>
    struct is_scalar
    : public traitor<is_arithmetic<Tp>, is_pointer<Tp> >
    { };

  //
  // For use in std::copy and std::find overloads for streambuf iterators.
  //
  template<typename Tp>
    struct is_char
    {
      enum { value = 0 };
      typedef false_type type;
    };

  template<>
    struct is_char<char>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<typename Tp>
    struct is_byte
    {
      enum { value = 0 };
      typedef false_type type;
    };

  template<>
    struct is_byte<char>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_byte<signed char>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<>
    struct is_byte<unsigned char>
    {
      enum { value = 1 };
      typedef true_type type;
    };

  template<typename> struct iterator_traits;

  //
  // Move iterator type
  //
  template<typename Tp>
    struct is_move_iterator
    {
      enum { value = 0 };
      typedef false_type type;
    };

  // Fallback implementation of the function in bits/stl_iterator.h used to
  // remove the move_iterator wrapper.
  template<typename Iterator>
    inline Iterator
    miter_base(Iterator it)
    { return it; }

} // namespace ft

#endif //_CPP_TYPE_TRAITS_H
