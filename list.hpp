#ifndef LIST_HPP
# define LIST_HPP

# include "type_traits.hpp"
# include "iterators.hpp"
# include "misc.hpp"

namespace ft
{
	// ============= BITS STL LIST =============
	template <typename T>
	struct List_node
	{
		List_node<T>		*prev;
		List_node<T>		*next;
		T					elem;

		List_node()
		: prev(nullptr), next(nullptr) {}

		List_node(const T & elem)
		: prev(nullptr), next(nullptr), elem(elem) {}

		List_node(const T & elem, List_node<T> *prev, List_node<T> *next)
		: prev(prev), next(next), elem(elem) {}

		List_node(List_node<T> *node)
		: prev(node->prev), next(node->next), elem(node->elem) {}

		List_node<T> & operator=(const List_node<T> & rhs)
		{
			if (*this == rhs) { return *this; }
			this->prev = rhs.prev;
			this->next = rhs.next;
			this->elem = rhs.elem;
			return *this;
		}
	};
 
	template <typename T>
	struct List_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef List_iterator<T>							self;
		typedef List_node<T>								*node;

		typedef ft::iterator<ft::bidirectional_iterator_tag, T>		iterator;
		typedef typename iterator::difference_type			difference_type;
		typedef typename iterator::iterator_category		iterator_category;
		typedef typename iterator::value_type				value_type;
		typedef typename iterator::pointer					pointer;;
		typedef typename iterator::reference				reference;

		List_iterator() : node(nullptr) {}
		List_iterator(List_node<T> *srcnode) { this->node = *srcnode; }
		List_iterator(List_iterator<T> & other) : node(other.node) {}
		virtual ~List_iterator() {}

		self & operator=(const self & rhs) {
			if (*this == rhs) { return *this; }
			this->node = rhs.node; return *this;
		}
		reference operator*() const { return (this->node)->elem; }
		pointer operator->() const { return &(this->operator*()); }
		self & operator++() { this->node = this->node->next; return *this; }
		self & operator++(int)
		{	self tmp = *this; this->node = this->node->next; return tmp; }
		self & operator--() { this->node = this->node->prev; return *this; }
		self & operator--(int)
		{	self tmp = *this; this->node = this->node->prev; return tmp; }
		// friend so the operator can access private parts (i.e traits_type)
		friend bool operator==(const self & x, const self & y)
		{	return (x.node == y.node); }
		friend bool operator==(const self & x, const self & y)
		{	return (x.node != y.node); }
	};

	// Same as List_iterator but const
	template <typename T>
	struct List_const_iterator
					: public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef List_const_iterator<T>						self;
		typedef const List_node<T>							node;

		typedef ft::iterator<ft::bidirectional_iterator_tag, T>	iterator;
		typedef typename iterator::difference_type			difference_type;
		typedef typename iterator::iterator_category		iterator_category;
		typedef typename iterator::value_type				value_type;
		typedef const T *									pointer;
		typedef const T &									reference;

		List_const_iterator() : node() {}
		List_const_iterator(List_node<T> *srcnode) { this->node = *srcnode; }
		List_const_iterator(const List_iterator<T> other) : node(other.node) {}
		virtual ~List_const_iterator() {}

		self & operator=(const self & rhs) {
			if (*this == rhs) { return *this; }
			this->node = rhs.node; return *this;
		}
		reference operator*() const { return (this->node)->elem; }
		pointer operator->() const { return &(this->operator*()); }
		self & operator++() { this->node = this->node->next; return *this; }
		self & operator++(int)
		{	self tmp = *this; this->node = this->node->next; return tmp; }
		self & operator--() { this->node = this->node->prev; return *this; }
		self & operator--(int)
		{	self tmp = *this; this->node = this->node->prev; return tmp; }
		friend bool operator==(const self & x, const self & y)
		{	return (x.node == y.node); }
		friend bool operator==(const self & x, const self & y)
		{	return (x.node != y.node); }
	};

}; // namespace ft

#endif // LIST_HPP
