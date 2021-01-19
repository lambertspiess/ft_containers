#ifndef TYPE_TRAITS
# define TYPE_TRAITS

//# include <cstddef>
//# include <typeinfo>
//# include <limits>
//
//namespace ft
//{
// // ===================== BITS CPP TYPE TRAITS ===================== 
//
//	struct true_type { };
//	struct false_type { };
//
//	template<bool>
//    struct truth_type
//    { typedef false_type type; };
//
//	template<>
//    struct truth_type<true>
//    { typedef true_type type; };
//
//	template<class Sp, class Tp>
//    struct traitor
//    {
//      enum { value = bool(Sp::value) || bool(Tp::value) };
//      typedef typename truth_type<value>::type type;
//    };
//
//  // Compare for equality of types.
//	template<typename, typename>
//	struct are_same
//	{
//		enum { value = 0 };
//		typedef false_type type;
//	};
//
//	template<typename Tp>
//	struct are_same<Tp, Tp>
//	{
//		enum { value = 1 };
//		typedef true_type type;
//	};
//
//	// Holds if the template-argument is a void type.
//	template<typename Tp>
//	struct is_void
//	{
//		enum { value = 0 };
//		typedef false_type type;
//	};
//
//	template<>
//	struct is_void<void>
//	{
//		enum { value = 1 };
//		typedef true_type type;
//	};
//
////
//// Integer types
////
//	template<typename Tp>
//	struct is_integer
//	{
//		enum { value = 0 };
//		typedef false_type type;
//	};
//
//// Thirteen specializations (yes there are eleven standard integer
//// types; <em>long long</em> and <em>unsigned long long</em> are
//// supported as extensions).  Up to four target-specific int<N>
//// types are supported as well.
//template<>
//	struct is_integer<bool>
//	{
//		enum { value = 1 };
//		typedef true_type type;
//	};
//
//	template<>
//	struct is_integer<char>
//	{
//		enum { value = 1 };
//		typedef true_type type;
//	};
//
//template<>
//struct is_integer<signed char>
//{
//	enum { value = 1 };
//	typedef true_type type;
//};
//
//template<>
//  struct is_integer<unsigned char>
//  {
//    enum { value = 1 };
//    typedef true_type type;
//  };
//
//  template<>
//    struct is_integer<short>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_integer<unsigned short>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_integer<int>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_integer<unsigned int>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_integer<long>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_integer<unsigned long>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_integer<long long>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_integer<unsigned long long>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  //
//  // Floating point types
//  //
//  template<typename Tp>
//    struct is_floating
//    {
//      enum { value = 0 };
//      typedef false_type type;
//    };
//
//  // three specializations (float, double and 'long double')
//  template<>
//    struct is_floating<float>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_floating<double>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_floating<long double>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  //
//  // Pointer types
//  //
//  template<typename Tp>
//    struct is_pointer
//    {
//      enum { value = 0 };
//      typedef false_type type;
//    };
//
//  template<typename Tp>
//    struct is_pointer<Tp*>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  //
//  // An arithmetic type is an integer type or a floating point type
//  //
//  template<typename Tp>
//    struct is_arithmetic
//    : public traitor<is_integer<Tp>, is_floating<Tp> >
//    { };
//
//  //
//  // A scalar type is an arithmetic type or a pointer type
//  //
//  template<typename Tp>
//    struct is_scalar
//    : public traitor<is_arithmetic<Tp>, is_pointer<Tp> >
//    { };
//
//  //
//  // For use in std::copy and std::find overloads for streambuf iterators.
//  //
//  template<typename Tp>
//    struct is_char
//    {
//      enum { value = 0 };
//      typedef false_type type;
//    };
//
//  template<>
//    struct is_char<char>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<typename Tp>
//    struct is_byte
//    {
//      enum { value = 0 };
//      typedef false_type type;
//    };
//
//  template<>
//    struct is_byte<char>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_byte<signed char>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<>
//    struct is_byte<unsigned char>
//    {
//      enum { value = 1 };
//      typedef true_type type;
//    };
//
//  template<typename> struct iterator_traits;
//
//  //
//  // Move iterator type
//  //
//  template<typename Tp>
//    struct is_move_iterator
//    {
//      enum { value = 0 };
//      typedef false_type type;
//    };
//
//  // Fallback implementation of the function in bits/stl_iterator.h used to
//  // remove the move_iterator wrapper.
//  template<typename Iterator>
//    inline Iterator
//    miter_base(Iterator it)
//    { return it; }
//
//
//
//
// // ===================== EXT TYPE TRAITS ===================== 
//	/*
//	 * ========== ENABLE_IF ==========
//	 * Ensures at compile-time that parameterized types contain certain traits.
//	 */
//
//	// Define a nested type if some predicate holds.
//	template<bool, typename>
//	struct enable_if 
//	{ };
//
//	template<typename Tp>
//	struct enable_if<true, Tp>
//	{ typedef Tp type; };
//
//	// Conditional expression for types. If true, first, if false, second.
//	template<bool Cond, typename Iftrue, typename Iffalse>
//	struct conditional_type
//	{ typedef Iftrue type; };
//
//  template<typename Iftrue, typename Iffalse>
//	struct conditional_type<false, Iftrue, Iffalse>
//	{ typedef Iffalse type; };
//
//
//	// Given an integral builtin type, return the corresponding unsigned type.
//	template<typename Tp>
//	struct add_unsigned
//	{ 
//		private:
//			typedef enable_if<is_integer<Tp>::value, Tp> if_type;
//		public:
//			typedef typename if_type::type type; 
//	};
//
//	template<>
//	struct add_unsigned<char>
//	{ typedef unsigned char type; };
//
//	template<>
//	struct add_unsigned<signed char>
//	{ typedef unsigned char type; };
//
//	template<>
//	struct add_unsigned<short>
//	{ typedef unsigned short type; };
//
//	template<>
//	struct add_unsigned<int>
//	{ typedef unsigned int type; };
//
//	template<>
//	struct add_unsigned<long>
//	{ typedef unsigned long type; };
//
//	template<>
//	struct add_unsigned<long long>
//	{ typedef unsigned long long type; };
//
//	// Declare but don't define.
//	template<>
//	struct add_unsigned<bool>;
//
//	template<>
//	struct add_unsigned<wchar_t>;
//
//
//	// Given an integral builtin type, return the corresponding signed type.
//	template<typename Tp>
//	struct remove_unsigned
//	{ 
//		private:
//			typedef enable_if<is_integer<Tp>::value, Tp> if_type;
//		public:
//			typedef typename if_type::type type; 
//	};
//
//	template<>
//	struct remove_unsigned<char>
//	{ typedef signed char type; };
//
//	template<>
//	struct remove_unsigned<unsigned char>
//	{ typedef signed char type; };
//
//	template<>
//	struct remove_unsigned<unsigned short>
//	{ typedef short type; };
//
//	template<>
//	struct remove_unsigned<unsigned int>
//	{ typedef int type; };
//
//	template<>
//	struct remove_unsigned<unsigned long>
//	{ typedef long type; };
//
//	template<>
//	struct remove_unsigned<unsigned long long>
//	{ typedef long long type; };
//
//	// Declare but don't define.
//	template<>
//	struct remove_unsigned<bool>;
//
//	template<>
//	struct remove_unsigned<wchar_t>;
//
//	// For use in string and vstring.
//	template<typename Type>
//	inline bool is_null_pointer(Type* ptr)
//	{ return ptr == 0; }
//
//	template<typename Type>
//	inline bool is_null_pointer(Type)
//	{ return false; }
//
//	// For complex and cmath
//	template<typename Tp, bool = is_integer<Tp>::value>
//	struct promote
//	{ typedef double type; };
//
//} // namespace ft
//
#endif // TYPE_TRAITS
