#ifndef LIST_HPP
# define LIST_HPP

# include "iterators.hpp"
# include "enable_if.hpp"
# include <memory>
# include <limits>

namespace ft
{
	template <typename T>
	struct list_node // a circular doubly-linked list
	{
		list_node<T> *prev, *next; T elem;

		list_node()
			: prev(nullptr), next(nullptr) {}
		list_node(const T & elem) :
			prev(nullptr), next(nullptr), elem(elem) {}
		list_node(list_node<T> *prev, list_node<T> *next, const T & elem)
			: prev(prev), next(next), elem(elem) {}
		list_node(list_node<T> *node)
			: prev(node->prev), next(node->next), elem(node->elem) {}

		// compares the adresses of the objects
		list_node<T> & operator=(const list_node<T> & rhs) {
			if (*this == rhs) { return *this; }
			this->prev = rhs.prev; this->next = rhs.next; this->elem = rhs.elem;
			return *this;
		}
	};
 
	template <typename T>
	struct list_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef list_iterator<T>							self;
		list_node<T>										*node;

		typedef ft::iterator<ft::bidirectional_iterator_tag, T>	iterator;
		typedef typename iterator::difference_type			difference_type;
		typedef typename iterator::iterator_category		iterator_category;
		typedef typename iterator::value_type				value_type;
		typedef typename iterator::pointer					pointer;;
		typedef typename iterator::reference				reference;

		list_iterator() : node(nullptr) {}
		list_iterator(list_node<T> * srcnode) : node(srcnode) {}
		list_iterator(const self & other) : node(other.node) {}
		virtual ~list_iterator() {}

		iterator & operator=(const self & rhs) {
			if (*this == rhs) { return *this; }
			this->node = rhs.node; return *this;
		}
		reference operator*() const { return (this->node)->elem; }
		pointer operator->() const { return &(this->operator*()); }
		iterator & operator++() { this->node = this->node->next; return *this; }
		iterator & operator++(int)
		{	iterator tmp(this->node); this->node = this->node->next; return tmp; }
		iterator & operator--() { this->node = this->node->prev; return *this; }
		iterator & operator--(int)
		{	iterator tmp = *this; this->node = this->node->prev; return tmp; }
		// friend so the operator can access private parts (i.e traits_type)
		friend bool operator==(const self & x, const self & y)
		{	return (x.node == y.node); }
		friend bool operator!=(const self & x, const self & y)
		{	return (x.node != y.node); }
	};

	// Same as list_iterator but const
	template <typename T>
	struct list_const_iterator
					: public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		const list_node<T>									*node;
		typedef list_const_iterator<T>						self;

		typedef ft::iterator<ft::bidirectional_iterator_tag, T>	iterator;
		typedef typename iterator::difference_type			difference_type;
		typedef typename iterator::iterator_category		iterator_category;
		typedef typename iterator::value_type				value_type;
		typedef const T *									pointer;
		typedef const T &									reference;

		list_const_iterator() : node() {}
		list_const_iterator(list_node<T> *srcnode) : node(srcnode) {}
		list_const_iterator(const list_iterator<T> other) : node(other.node) {}
		virtual ~list_const_iterator() {}

		self & operator=(const self & rhs) {
			if (*this == rhs) { return *this; }
			this->node = rhs.node; return *this;
		}
		reference	operator*() const { return ((this->node)->elem); }
		pointer	operator->() const { return (&(this->operator*())); }
		self &	operator++() { this->node = this->node->next; return *this; }
		self &	operator++(int)
			{ self tmp = *this; this->node = this->node->next; return tmp; }
		self &	operator--() { this->node = this->node->prev; return *this; }
		self &	operator--(int)
			{ self tmp = *this; this->node = this->node->prev; return tmp; }
		friend bool	operator==(const self & x, const self & y)
			{ return (x.node == y.node); }
		friend bool	operator!=(const self & x, const self & y)
			{ return !(x.node == y.node); }
	};

	template <typename T, typename Alloc = std::allocator<T> >
	class list
	{
		public:
			typedef Alloc									allocator_type;;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef T										value_type;
			typedef typename ft::list_iterator<T>			iterator;
			typedef typename ft::list_const_iterator<T>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>	reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>
														const_reverse_iterator;
			typedef size_t									size_type;
			typedef ptrdiff_t								difference_type;
		protected:
			typedef list_node<T>							node;
			typedef typename Alloc::template rebind<list_node<T> >::other
															_node_allocator;
			_node_allocator									_node_alloc;
			typedef typename _node_allocator::pointer		node_pointer;

		private:
			node											*_last;
			allocator_type									_alloc;

// see : https://stackoverflow.com/questions/5628059/c-stl-allocator-vs-operator-new
			node_pointer _allocateNode(const T & elem, node * prev = nullptr,
														node * next = nullptr)
			{
				node * newnode = _node_alloc.allocate(1);
				_node_alloc.construct(newnode, node(elem));
				newnode->prev = prev; newnode->next = next; return newnode;
			}
			node_pointer _copyNode(const node * src)
			{
				node * newnode = _node_alloc.allocate(1);
				_node_alloc.construct(newnode, list_node<T>(src->elem));
				newnode->prev = src->prev; newnode->next = src->next; return newnode;
			}
			void		_deleteNode(node *node)
			{
				node->prev->next = node->next; node->next->prev = node->prev;
				_node_alloc.destroy(node); _node_alloc.deallocate(node, 1);
			}
			void 		_unlinkNode(node *node)
			{ node->prev->next = node->next; node->next->prev = node->prev; }

		public:
			// empty container (_last doubly linked to itself)
			explicit list(const allocator_type & a = allocator_type())
			: _alloc(a)
			{
				_last = _node_alloc.allocate(1);
				_node_alloc.construct(_last, node());
				_last->prev = _last; _last->next = _last;
			}

			// Constructs a container with n elements which are copies of val.
			explicit list(size_type n, const value_type val = value_type(),
							const allocator_type & a = allocator_type())
			: _alloc(a)
			{
				_last = _node_alloc.allocate(1);
				_node_alloc.construct(_last, list_node<T>());
				_last->prev = _last; _last->next = _last;
				insert(end(), n, val);
			}

			// range ctor.
			// enable_if idiom makes sure InputIterator isn't an integral type
			template <typename InputIterator>
			list(InputIterator first, InputIterator last,
				const allocator_type & a = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value,
							InputIterator>::type iter = InputIterator())
			: _alloc(a)
			{ static_cast<void>(iter);
				_last = _node_alloc.allocate(1);
				_node_alloc.construct(_last, list_node<T>());
				_last->prev = _last; _last->next = _last;
				insert(end(), first, last);
			}

			// copy ctor
			list (const list & src)
			: _alloc(src._alloc)
			{
				_last = _node_alloc.allocate(1);
				_node_alloc.construct(_last, list_node<T>());
				_last->prev = _last; _last->next = _last;
				insert(end(), src.begin(), src.end());
			}

			~list() { clear(); delete _last; }

			list & operator=(const list & rhs)
			{
				if (*this == rhs) { return *this; }
				clear(); insert(begin(), rhs.begin(), rhs.end()); return *this;
			}

			// return an iterator to the first element
			iterator begin() { return (iterator(_last->next)); }
			const_iterator begin() const { return (const_iterator(_last->next)); }
			// return an iterator to the past-the-end element
			iterator end() { return (iterator(_last)); }
			const_iterator end() const { return (const_iterator(_last)); }
			reverse_iterator rbegin() { return (reverse_iterator(_last->next)); }
			reverse_iterator rbegin() const { return (const_reverse_iterator(_last->next)); }
			reverse_iterator rend() { return (reverse_iterator(_last)); }
			reverse_iterator rend() const { return (const_reverse_iterator(_last)); }

			// Capacity
			bool empty() const { return (_last->next == _last ? true : false); }

			size_type size() const
			{
				size_type n = 0; node_pointer ptr = _last->next;
				while (ptr != _last) { n++; ptr = ptr->next; }
				return (n);
			}

			size_type max_size() const
			{ return (static_cast<size_type>(SIZE_MAX / sizeof(list_node<T>))); }

			// Element access
			reference front() { return (_last->next->elem); }
			const_reference front() const { return (_last->next->elem); }
			reference back() { return (_last->prev->elem); }
			const_reference back() const { return (_last->prev->elem); }

			// clear the container of leftovers elements and reassign
			template <typename InputIterator>
			void assign(InputIterator first, InputIterator last,
				typename ft::enable_if<
								!is_integral<InputIterator>::value,
								InputIterator
									>::type iter = InputIterator())
				{
					static_cast<void>(iter);
					insert(end(), first, last);
				}

			// same but reassign with n copies of element val
			void assign(size_type n, const value_type & val)
				{ clear(); insert(end(), n, val); }

			void push_front(const value_type & val)
				{ insert(begin(), val); }

			void pop_front() { erase(begin()); }

			void push_back(const value_type & val)
				{ insert(begin(), val); }

			void pop_back() { iterator itr(end()); --itr; erase(itr); }

			// insert node before position
			iterator insert(iterator position, const value_type & val)
			{
				node *newnode = _allocateNode(val);
				node *before = position.node->prev;

				before->next = newnode; newnode->prev = before;
				newnode->next = position.node; position.node->prev = newnode;
				return (--position);
			}

			// insert n copies of element val before position
			void insert(iterator position, size_type n, const value_type & val)
				{ while (n--) { insert(position, val); } }

			// insert [first, last) before position
			template <typename InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!is_integral<InputIterator>::value,
									InputIterator>::type iter = InputIterator())
			{ static_cast<void>(iter);
				InputIterator itr = first;
				while (itr != last)
					{ insert(position++, *itr); ++itr; }
			}

			// delete an element at @position
			iterator erase(iterator position)
			{
				iterator next(position.node->next);
				node * node = position.node; _unlinkNode(node);
				_node_alloc.destroy(node); _node_alloc.deallocate(node, 1);
				return (next);
			}

			// delete a range of elements [first, last)
			iterator erase(iterator first, iterator last)
			{
				iterator itr = first; while (++itr != last) { erase(itr); }
				return (iterator(last));
			}

			void swap(list & other)
			{
				allocator_type swap_allocator_type = other.allocator_type;
				_node_allocator swap_node_allocator = other._node_allocator;
				node * swap_last = other._last;

				other.allocator_type = this->allocator_type;
				other._node_allocator = this->_node_allocator;
				other._last = this->_last;

				this->allocator_type = swap_allocator_type;
				this->_node_allocator = swap_node_allocator;
				this->_last = swap_last;
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n < size())
				{
					size_type diff = size() - n;
					while (diff--) { pop_back(); }
				}
				else
				{
					size_type diff = n - size();
					while (diff--) { push_back(val); }
				}
			}

			void clear() { erase(begin(), end()); }

			// splicing removes elements and insert them elsewhere
			void splice(iterator position, list & other)
			{
				insert(position, other.begin(), other.end()); other.clear();
			}

			void splice(iterator position, list & other, iterator itr)
			{
				insert(position, *itr); other.erase(itr);
			}

			void splice(iterator position, list & other, iterator first, iterator last)
			{
				insert(position, first, last); other.erase(first, last);
			}

			void remove(const value_type & val)
			{
				iterator itr = begin();
				while (itr != end())
					{ if (*itr == val) { erase(itr); } else { ++itr; } }
			}

			template <class Predicate>
			void remove_if(Predicate pred)
			{
				iterator itr = begin();
				while (itr != end())
					{ if (pred(*itr) == true) { erase(itr); } else { ++itr; } }
			}

			void unique()
			{
				iterator i, j; i = begin(); j = i;
				while (i != end())
				{
					j = i; ++j; while (j != end() && *j == *i) { erase(j); }
					++i;
				}
			}

			// merges two lists which are assumed to be sorted.
			void merge(list & x) { merge(x, &less_than<T>); }

			template <class Compare>
			void merge(list & x, Compare comp)
			{
				if (*this == x)
					return ;
				if (_last->next == _last)
					{ assign(x.begin(), x.end()); x.clear(); return ; }
				iterator i, j;
				i = begin(); j = x.begin();
				while (i != end())
				{
					while ((j != x.end()) && (comp(*j, *i) == true))
					{
						insert(i++, j++);
					}
					i++;
				}
				x.clear();
			}

			void sort(void) { sort(&less_than<T>); }

			template <class Compare>
			void sort(Compare comp)
			{
				if (_last->next == _last) { return ; }
				iterator i, j; i = begin();
				while (i != end())
				{
					j = i;
					while (j != end())
					{
						if (comp(*j, *i))
							splice(i, *this, j);
						else
							j++;
					}
					i++;
				}
			}

			void reverse()
			{
				size_type n = size() / 2;
				node * i, j, swap; i = _last->next; j = _last->prev;
				while (n--)
				{
					swap = i->elem; i = j->elem; j->elem = swap;
					i = i->next; j = j->prev;
				}
			}

	}; // class list

	template <typename T, class Alloc>
	bool operator==(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs)
	{
		if (lhs.size() != rhs.size()) { return (false) ; }
		typename ft::list<T, Alloc>::const_iterator i = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator j = rhs.begin();
		while (i != lhs.end() && j != rhs.end())
		{
			if (*i != *j) { return (false); }
			i++; j++;
		}
	}

	template <typename T, class Alloc>
	bool operator!=(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs)
	{
		return (!(rhs == lhs));
	}

	// compare two lists element by element
	template <typename T, class Alloc>
	bool operator<(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs)
	{
		typename ft::list<T, Alloc>::const_iterator i = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator j = rhs.begin();
		while (i != lhs.end() && j != rhs.end())
		{
			if (*i != *j) { return (*i < *j); }
			i++; j++;
		}
		if (lhs.size() == rhs.size()) { return (false); }
		return (lhs.size() < rhs.size());
	}

	template <typename T, class Alloc>
	bool operator<=(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs)
	{
		return (!(lhs > rhs));
	}

	template <typename T, class Alloc>
	bool operator>(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs)
	{
		typename ft::list<T, Alloc>::const_iterator i = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator j = rhs.begin();
		while (i != lhs.end() && j != rhs.end())
		{
			if (*i != *j) { return (*i > *j); }
			i++; j++;
		}
		if (lhs.size() == rhs.size()) { return (false); }
		return (lhs.size() > rhs.size());
	}

	template <typename T, class Alloc>
	bool operator>=(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename T, class Alloc>
	void swap(list<T, Alloc> & lhs, list<T, Alloc> & rhs)
	{
		lhs.swap(rhs);
	}

}; // namespace ft

#endif // LIST_HPP
