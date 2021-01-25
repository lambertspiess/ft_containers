#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include "iterators.hpp"
# include "enable_if.hpp"

namespace ft
{
//	template <typename T, class Alloc = std::allocator<T> >
//	class vector
//	{
//		public:
//			typedef T										value_type;
//			typedef Alloc									allocator_type;;
//			typedef typename Alloc::pointer					pointer;
//			typedef typename Alloc::const_pointer			const_pointer;
//			typedef typename Alloc::reference				reference;
//			typedef typename Alloc::const_reference			const_reference;
//			typedef ft::random_access_iterator<T>			iterator;
//			typedef ft::random_access_iterator<const T>		const_iterator;
//			typedef ft::reverse_iterator<iterator>			reverse_iterator;
//			typedef ft::reverse_iterator<const_iterator>
//															const_reverse_iterator;
//			typedef size_t									size_type;
//			typedef ptrdiff_t								difference_type;
//		protected:
//			typedef list_node<T>							node;
//			typedef typename Alloc::template rebind<list_node<T> >::other
//															_node_allocator;
//			_node_allocator									_node_alloc;
//			typedef typename _node_allocator::pointer		node_pointer;
//
//		private:
//			node											*_last;
//			allocator_type									_alloc;
//	}
}; // namespace ft


#endif
