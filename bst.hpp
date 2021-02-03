#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "iterators.hpp"

namespace ft
{

	template <typename T>
	struct bst_node
	{
		typedef T value_type;	T value;	bst_node *parent, *left, *right;

		bst_node() : value(), parent(nullptr), left(nullptr), right(nullptr) {}
		bst_node(bst_node * parent = nullptr, bst_node * left = nullptr,
												bst_node * right = nullptr)
		: value(), parent(parent), left(left), right(right) {}
		bst_node(const bst_node & other)
		: value(), parent(other.parent), left(other.left), right(other.right) {}
		~virtual bst_node() {}
		bst_node & operator=(const bst_node & rhs)
		{
			if (*this == rhs) { return (*this); }
			value = rhs.value; parent = rhs.parent; left = rhs.left; right = rhs.right;
			return (*this);
		}
		bool operator==(const bst_node & rhs) { return (value == rhs.value); }
	}; // struct bst_node

	template <typename T, class Compare>
	class bst_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		private:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T> _iter;
		public:
			typedef T										value_type;
			typedef typename _iter::difference_type			difference_type;
			typedef typename _iter::pointer					pointer;
			typedef typename _iter::reference				reference;

			T												*_node;
			T												*_lastnode;;
			Compare											_cmp;

			bst_iterator(const Compare & cmp = Compare())
			: _node(), _lastnode(), _cmp(cmp)
			{}

			bst_iterator(T * node, T * lastnode, const Compare & cmp = Compare())
			: _node(node), _lastnode(lastnode), _cmp(cmp)
			{}

			bst_iterator(const bst_iterator & other)
			: _node(other._node), _lastnode(other._lastnode), _cmp(other._cmp)
			{}

			virtual ~bst_iterator() {}

			bst_iterator & operator=(const bst_iterator & rhs)
			{
				if (*this == rhs) { return (*this); }
				_node = rhs._node; _lastnode = rhs._lastnode; _cmp = rhs._cmp;
				return (*this);
			}

			bool operator==(const bst_iterator & rhs)
			{ return (_node == rhs._node); }

			bool operator!=(const bst_iterator * rhs)
			{ return (_node != rhs._node); }

			reference operator*() const { return (_node->value); }
			reference operator->() const { return (&(_node->value)); }

			bst_iterator & operator++(void)
			{
				T * head = _node;

			}



	}; // bst_iterator



//
//	template <typename T>
//	struct bst_node // a standard binary tree node
//	{
//		T elem;		typedef T elem_type;	bst_node *parent, *left, *right;
//		bst_node() {};
//		bst_node(T elem, bst_node parent, bst_node left, bst_node right)
//		: elem(elem), parent(parent), left(left), right(right) {}
//		bst_node(const bst_node & other)
//		: elem(other.elem), parent(other.parent), left(other.left), right(other.right) {}
//	}; // struct bst_node
//
//	template <typename T, typename Compare> class bst;
//	template <typename T, typename Compare>
//	class bst_iter // iterator holding a pointer to the tree and a pointer to a node
//	{
//		private:
//			bst_iter();
//		protected:
//			bst<T, Compare> 							* _tree;
//			bst_node<T>									* _node;
//		public:
//			bst_iter(bst<T, Compare> *tree, bst_node<T> *node)
//				: _tree(tree), _node(node) {}
//			bst_iter(const bst_iter<T, Compare> & other)
//				: _tree(other.tree), _node(other.node) {}
//			bool operator==(const bst_iter<T, Compare> & rhs) const
//				{ return (_node == rhs.node); }
//			bool operator!=(const bst_iter<T, Compare> & rhs) const
//				{ return (_node != rhs.node); }
//			bst_node<T> * getP() const { return (_node); }
//			bst<T, Compare> * getTree() const { return (_tree); }
//	}; // bst_iter
//
//	template <typename T, typename Compare>
//	class bst_iterator : public bst_iter<T, Compare>
//	{
//		public:
//			typedef bst_iterator<T, Compare>			iterator;
//			typedef bst_node<T>							Node;
//			typedef bst<T, Compare>						Tree;
//
//			typedef T value_type; typedef T * pointer; typedef T & reference;
//			typedef std::ptrdiff_t						difference_type;
//			typedef ft::bidirectional_iterator_tag		iterator_category;
//
//			iterator() : bst_iter<T, Compare>(NULL, NULL) {}
//			iterator(Tree * tree) : bst_iter<T, Compare>(tree, NULL) {}
//			iterator(Tree * tree, Node * node) : bst_iter<T, Compare>(tree, node) {}
//			iterator(const iterator & other) : bst_iter<T, Compare>(other) {}
//			~iterator() {}
//			iterator & operator=(const iterator & other) {
//				if (*this == other) { return (*this); }
//				_node = other._node; _tree = other._tree; return (*this);
//			}
//			iterators & operator++(void) {
//				Node * root = _tree->getR();	Node * tmp;
//			}
//	}; // bst_iterator
//
//	template <typename T, typename Compare>
//	class bst
//	{
//		public :
//			typedef T								value_type;
//			typedef bst_node<T> 					Node;
//			typedef bst<T, Compare>					Tree;
//			typedef size_t							size_type;
//			typedef bst_iterator<T, Compare>		iterator;
//			typedef reverse_iterator<iterator>		reverse_iterator;
//
//	}; // class bst

}; // namespace ft

#endif // BINARY_SEARCH_TREE_HPP
