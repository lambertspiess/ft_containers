#ifndef LIST_HPP
# define LIST_HPP

# include "type_traits.hpp"
# include "iterators.hpp"
# include "misc.hpp"
# include <memory>
# include <limits>

namespace ft
{
	template <typename T>
	struct List_node // a circular doubly-linked list
	{
		List_node<T> *prev, *next; T elem;

		List_node()
			: prev(nullptr), next(nullptr) {}
		List_node(const T & elem) :
			prev(nullptr), next(nullptr), elem(elem) {}
		List_node(List_node<T> *prev, List_node<T> *next, const T & elem)
			: prev(prev), next(next), elem(elem) {}
		List_node(List_node<T> *node)
			: prev(node->prev), next(node->next), elem(node->elem) {}

		List_node<T> & operator=(const List_node<T> & rhs) {
			if (*this == rhs) { return *this; }
			this->prev = rhs.prev; this->next = rhs.next; this->elem = rhs.elem;
			return *this;
		}
	};
 
	template <typename T>
	struct List_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef List_iterator<T>							self;
		typedef List_node<T>								*node;

		typedef ft::iterator<ft::bidirectional_iterator_tag, T>	iterator;
		typedef typename iterator::difference_type			difference_type;
		typedef typename iterator::iterator_category		iterator_category;
		typedef typename iterator::value_type				value_type;
		typedef typename iterator::pointer					pointer;;
		typedef typename iterator::reference				reference;

		List_iterator() : node(nullptr) {}
		List_iterator(List_node<T> *srcnode) : node(srcnode) {}
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
		List_const_iterator(List_node<T> *srcnode) : node(srcnode) {}
		List_const_iterator(const List_iterator<T> other) : node(other.node) {}
		virtual ~List_const_iterator() {}

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
		friend bool	operator==(const self & x, const self & y)
			{ return (x.node != y.node); }
	};

	template <typename T, typename Alloc = std::allocator<T> >
	class List
	{
		public:
			typedef Alloc									allocator_type;;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef T										value_type;
			typedef typename ft::List_iterator<T>			iterator;
			typedef typename ft::List_const_iterator<T>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>	reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>
														const_reverse_iterator;
			typedef size_t									size_type;
			typedef ptrdiff_t								difference_type;
		protected:
			typedef List_node<T>							node;
		private:
			allocator_type									_alloc;
			List_node<T>									*_head;
			size_type										_size;

			// empty container constructor
			explicit List(const allocator_type & a = allocator_type())
			: _alloc(a), _size(0)
			{
				_head = new List_node<T>(nullptr, nullptr, value_type());
				_head->prev = _head; _head->next = _head;
			}
			// Constructs a container with n elements which are copies of val.
			explicit List(size_type n, const value_type val = value_type(),
							const allocator_type & a = allocator_type())
			: _alloc(a), _size(0)
			{
				_head = new List_node<T>(nullptr, nullptr, value_type());
				_head->prev = _head; _head->next = _head;
				insert(begin(), n, val);
			}
			// Range ctor.
			// enable_if idiom makes sure InputIterator isn't an integral type
			template <typename InputIterator>
			List (InputIterator first, InputIterator last,
				const allocator_type & a = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value,
							InputIterator>::type iter = InputIterator())
			: _alloc(a), _size(0)
			{
				iter = nullptr;
				_head->prev = _head; _head->next = _head;
				insert(end(), first, last);
			}
			// copy ctor
			List (const List & src)
			: _alloc(src._alloc), _size(0)
			{
				_head = new List_node<T>(nullptr, nullptr, value_type());
				_head->prev = _head; _head->next = _head;
				insert(end(), src.begin(), src.end());
			}
			// dtor
			~List() { clear(); delete _head; }
			// assignement operator
			List & operator=(const List & rhs)
			{
				if (*this == rhs) { return *this; }
				clear(); insert(begin(), rhs.begin(), rhs.end()); return *this;
			}
			// Iterators
			iterator begin() { return (iterator(_head->next)); }
			iterator begin() const { return (const_iterator(_head->next)); }
			iterator end() { return (iterator(_head)); }
			iterator end() const { return (const_iterator(_head)); }
			reverse_iterator rbegin() { return (reverse_iterator(_head->next)); }
			reverse_iterator rbegin() const { return (reverse_iterator(_head->next)); }
			reverse_iterator rend() { return (reverse_iterator(_head)); }
			reverse_iterator rend() const { return (reverse_iterator(_head)); }

			// Capacity
			bool empty() const { return (_size == 0 ? true : false); }
			size_type size() const { return (_size); }
			size_type max_size() const
			{ return (static_cast<size_type>(SIZE_MAX / sizeof(List_node<T>))); }

			// Element access
			reference front() { return (_head->next->elem); }
			const_reference front() const { return (_head->prev->elem); }
			reference back() { return (_head->next->elem); }
			const_reference front() const { return (_head->prev->elem); }

			// clear the container of leftovers elements and reassign
			template <typename InputIterator>
			void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!is_integral<InputIterator>::value,
								InputIterator>::type iter = InputIterator())
				{ iter = nullptr; clear(); insert(end(), first, last); }
			// same but reassign with n copies of element val
			void assign(size_type n, const value_type & val)
				{ clear(); insert(end(), n, val); }

			void push_front(const value_type & val) { insert(begin(), val); }
			void pop_front(const value_type & val) { remove(begin()); }
			void push_back(const value_type & val) { insert(begin(), val); }
			void pop_back(const value_type & val) { remove(begin()); }

			// insert element before position
			iterator insert(iterator position, const value_type & val)
				{ insert(position, 1, val); return (--position); }
			// insert n elements before position
			iterator insert(iterator position, size_type n, const value_type & val)
			{
				if (n > max_size() || n == 0) { return ; }
				List_node<T> * first, last, cur;
				first = new List_node<T>(val);
				first->prev = first; first->next = first; last = first;
				}
				for (size_type i = 1; i < n; i++)
				{
					cur = new List_node<T>(last, nullptr, val);
					last->next = cur; last = last->next;
				}
				if (_size == 0)
				{
					first->prev = last; last->next = first; _head = last;
				}
				else
				{
					position->prev->next = first;
					first->prev = position->prev;
					last->next = position;
					position->prev = last;
				}
				_size += n;
			}
			// insert a range of elements before position
			template <typename InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<
						!is_integral<InputIterator>::value, InputIterator
					>::type iter = InputIterator())
			{ iter = nullptr;
				//lala
			}


	}; // class list

}; // namespace ft

#endif // LIST_HPP
