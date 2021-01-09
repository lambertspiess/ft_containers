#ifndef ITERATOR_BASE_FUNCS_HPP
# define ITERATOR_BASE_FUNCS_HPP

# include <cstddef>

namespace ft
{
	// ========== ITERATOR BASE FUNCTIONS ==========
	// general iterator-related utility functions

	template<typename _InputIterator>
	inline typename iterator_traits<_InputIterator>::difference_type
	__distance(_InputIterator __first, _InputIterator __last, input_iterator_tag)
	{
		typename iterator_traits<_InputIterator>::difference_type __n = 0;
		
	}

} // namespace ft

#endif // ITERATOR_BASE_FUNCS_HPP
