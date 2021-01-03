#ifndef LIST_HPP
# define LIST_HPP
# include <memory>

namespace ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class List
	{
		public:
			// types
			typedef T						value_type;
			typedef Allocator				allocator_type;
			typedef typename std::allocator_traits<Allocator>::pointer
											pointer;
			typedef typename std::allocator_traits<Allocator>::const_pointer
											const_pointer;
			typedef T &						reference;
			typedef const T &				const_reference;
			typedef typename std::size_t	size_type;
			typedef typename std::ptrdiff_t	difference_type;
			typedef typename ft::Bidirectionnal_iterator<T>
											iterator;
			// find and reimplement Bidirectionnal_iterator
			typedef const iterator			const_iterator;
			typedef typename ft::Reverse_iterator<T>
											reverse_iterator;
			typedef const reverse_iterator	reverse_iterator;

			// construct/copy/destroy
	};
}

#endif //LIST_HPP
