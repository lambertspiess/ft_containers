#ifndef UTILS_HPP
# define UTILS_HPP

	//========== ENABLE_IF ========== 
	// This is a SFINAE-based constraint. It blocks compilation of 
	// templates if the parameterized type doesn't fulfill the condition B.
	// This is achieved by not declaring the member T type when the 
	// condition isn't met. Used notably when instantiating Iterators.

	template<bool B, class T = void>
	struct enable_if
	{};
	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	//========== TYPE CHECKING ========== 
	// Templates used in conjunction with enable_if to do compile-time
	// type-checking

	// 

#endif // UTILS_HPP
