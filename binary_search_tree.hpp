#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "iterators.hpp"

namespace ft
{
	template <typename T>
	struct bst_node
	{
		T value;	typedef T value_type;	bst_node *parent, *left, *right;

		bst_node()
		: value(), parent(nullptr), left(nullptr), right(nullptr)
		{}

		bst_node(bst_node * parent = nullptr, bst_node * left = nullptr,
												bst_node * right = nullptr)
		: value(), parent(parent), left(left), right(right)
		{}

		bst_node(const T & value, bst_node * parent = nullptr,
					bst_node * left = nullptr, bst_node * right = nullptr)
		: value(value), parent(parent), left(left), right(right)
		{}

		bst_node(const bst_node & other)
		: value(other.value), parent(other.parent), left(other.left), right(other.right)
		{}

		virtual ~bst_node() {}

		bst_node & operator=(const bst_node & rhs) {
			if (*this == rhs) { return (*this); }
			value = rhs.value; parent = rhs.parent; left = rhs.left, right = rhs.right;
			return (*this);
		}
		bool operator==(const bst_node & rhs) { return (value == rhs.value); }

	}; // struct bst_node

	template <typename T1, typename T2>
	struct pair
	{
		T1 first; T2 second;

		pair() : first(), second() {}

		template <typename U1, typename U2>
		pair(const pair<U1, U2> & p)
		: first(p.first), second(p.second) {}

		pair(const T1 & a, const T2 & b) : first(a), second(b) {}

		pair & operator=(const pair & other) {
			if (*this == other) { return (*this); }
			first = other.first; second = other.second; return (*this);
		}
	}; // struct pair

	template <typename T>
	struct less : std::binary_function<T, T, bool>
	{
		bool operator()(const T & x, const T & y) const { return (x < y); }
	};

	template <class T, class Compare = ft::less<T>, class Node = ft::bst_node<T>,
			 class Alloc = std::allocator<T>, class Node_alloc = std::allocator<Node> >
	class bst
	{
		public:
			typedef ft::bst_iterator<Node, Compare>				iterator;
			typedef ft::bst_const_iterator<Node, Compare>		const_iterator;
			typedef size_t										size_type;

			Node *												_lastnode;
			Node_alloc											_node_alloc;

		bst(const Node_alloc & node_alloc = Node_alloc())
		:_node_alloc(node_alloc)
		{
			_lastnode = _node_alloc.allocate(1);
			_node_alloc.construct(_lastnode, Node(_lastnode, _lastnode, _lastnode));
		}

		~bst() { _node_alloc.destroy(_lastnode); _node_alloc.deallocate(_lastnode, 1); }

		// LALALALALALAL
		ft::pair<iterator, bool> insertPair(T elem)
		{
			Node * newnode = _node_alloc.allocate(1);
			Node * prev = _lastnode;
			Node * root = _lastnode->parent;
		}
	}; // class bst

















	template <typename T, typename Compare>
	class bst_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename ft::iterators<ft::bidirectional_iterator_tag, T>
															_iter;
			typedef typename _iter::value_type				value_type;
			typedef typename _iter::difference_type			difference_type;
			typedef typename _iter::pointer					pointer;
			typedef typename _iter::reference				reference;

		protected:
			T *												_node;
			T *												_lastnode;
			Compare											_comp;

		public:
			bst_iterator(const Compare & comp = Compare())
			: _node(nullptr), _lastnode(nullptr), _comp(comp)
			{}

			bst_iterator(T * node, T * lastnode, const Compare & comp = Compare())
			: _node(node1), _lastnode(lastnode), _comp(comp)
			{}

			bst_iterator(const bst_iterator & other)
			: _node(other._node), _lastnode(other._lastnode), _comp(other._comp)
			{}

			virtual ~bst_iterator() {}

			bst_iterator & operator=(const bst_iterator & rhs)
			{
				if (*this == rhs) { return (*this); }
				_node = rhs._node;
				_lastnode = rhs._lastnode;
				_comp = rhs._comp;
				return (*this);
			}

			bool operator==(const bst_iterator & rhs)
				{ return (_node == rhs._node); }

			bool operator!=(const bst_iterator & rhs)
				{ return (_node != rhs._node); }

			bool operator*() const 
				{ return (_node->value); }

			bool operator->(const bst_iterator & rhs)
				{ return (&(node->value)); }

			// WHAT IS LAST NODE ?
			// (see /Users/lspiess/containers/gnu/libstdc++-v3/src/c++98/tree.cc
			bst_iterator & operator++(void)
			{
				T * head = _node;
				if (head->right != nullptr)
				{
					head = head->right;
					while (head->left != nullptr)
					{
						head = head->left;
					}
				}
				else
				{
//					head = head->parent;
//					while (
//				}
			}


	}; // class bst_iterator

}; // namespace ft

#endif // BINARY_SEARCH_TREE_HPP
