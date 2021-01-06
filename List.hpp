#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include "Iterators.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class List
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename Alloc::reference			reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			// Alloc
	}
}
#endif //LIST_HPP
