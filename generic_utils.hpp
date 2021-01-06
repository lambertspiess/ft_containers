#ifndef GENERIC_UTILS_HPP
# define GENERIC_UTILS_HPP

// template programming utilities

namespace ft
{
	// =================== ENABLE_IF TRAIT ====================
	// Ensures when instantiating templates that the condition B 
	// is met before proceeding (SFINAE).
	// 
	templace <bool B, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T		type;
	}
}

#endif //GENERIC_UTILS_HPP
