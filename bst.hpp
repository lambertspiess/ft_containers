#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "iterators.hpp"

namespace ft
{

//	template <typename T>
//	struct bst_node
//	{
//		typedef T value_type;	T value;	bst_node *parent, *left, *right;
//
//		bst_node() : value(), parent(nullptr), left(nullptr), right(nullptr) {}
//		bst_node(bst_node * parent = nullptr, bst_node * left = nullptr,
//												bst_node * right = nullptr)
//		: value(), parent(parent), left(left), right(right) {}
//		bst_node(const bst_node & other)
//		: value(), parent(other.parent), left(other.left), right(other.right) {}
//		~virtual bst_node() {}
//		bst_node & operator=(const bst_node & rhs)
//		{
//			if (*this == rhs) { return (*this); }
//			value = rhs.value; parent = rhs.parent; left = rhs.left; right = rhs.right;
//			return (*this);
//		}
//		bool operator==(const bst_node & rhs) { return (value == rhs.value); }
//	}; // struct bst_node
//
//	template <class T, class Compare = ft::less<T>, class Node = ft::bst_node<T>,
//				class TAlloc = std::allocator<T>, class NodeAlloc = std::allocator<Node> >
//	class bst
//	{
//		public :
//
//		typedef bst self; typedef bst & self_reference; typedef T value_type;
//		typedef Node *											node_pointer;
//		typedef ft::bst_iterator<Node, Compare>					iterator;
//		typedef ft::bst_const_iterator<Node, Compare>			const_iterator;
//		private:
//			node_pointer _root, _init;
//
//		bst(const NodeAlloc * node_alloc
//	}; // class bst
//
//	template <typename T, class Compare>
//	class bst_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
//	{
//		private:
//			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T> _iter;
//		public:
//			typedef T										value_type;
//			typedef typename _iter::difference_type			difference_type;
//			typedef typename _iter::pointer					pointer;
//			typedef typename _iter::reference				reference;
//
//			bst_iterator(const Compare & cmp = Compare())
//			: _node(), _lastnode(), _cmp(cmp)
//			{}
//
//			bst_iterator(T * node, T * lastnode, const Compare & cmp = Compare())
//			: _node(node), _lastnode(lastnode), _cmp(cmp)
//			{}
//
//			bst_iterator(const bst_iterator & other)
//			: _node(other._node), _lastnode(other._lastnode), _cmp(other._cmp)
//			{}
//
//			virtual ~bst_iterator() {}
//
//			bst_iterator & operator=(const bst_iterator & rhs)
//			{
//				if (*this == rhs) { return (*this); }
//				_node = rhs._node; _lastnode = rhs._lastnode; _cmp = rhs._cmp;
//				return (*this);
//			}
//
//			bool operator==(const bst_iterator & rhs)
//			{ return (_node == rhs._node); }
//
//			bool operator!=(const bst_iterator * rhs)
//			{ return (_node != rhs._node); }
//
//			reference operator*() const { return (_node->value); }
//			reference operator->() const { return (&(_node->value)); }
//
//			// the mistery of the self pointing node. Lastnode seems to be init
//			bst_iterator & operator++(void)
//			{
//			}
//	}; // bst_iterator


	template <typename T>
	struct bst_node // a standard binary tree node
	{
		T elem;		typedef T elem_type;	bst_node *parent, *left, *right;
		bst_node() {}
		bst_node(T elem, bst_node parent, bst_node left, bst_node right)
		: elem(elem), parent(parent), left(left), right(right) {}
		bst_node(const bst_node & other)
		: elem(other.elem), parent(other.parent), left(other.left), right(other.right) {}
	}; // struct bst_node

	template <typename T, typename Compare> class bst;

	template <typename T, typename Compare>
	class bst_iter // base iterator class
	{
		protected:
			bst<T, Compare> 							* _tree;
			bst_node<T>									* _node;
		public:
			bst_iter(bst<T, Compare> *tree, bst_node<T> *node)
				: _tree(tree), _node(node) {}
			bst_iter(const bst_iter<T, Compare> & other)
				: _tree(other.tree), _node(other.node) {}
			bool operator==(const bst_iter<T, Compare> & rhs) const
				{ return (_node == rhs.node); }
			bool operator!=(const bst_iter<T, Compare> & rhs) const
				{ return (_node != rhs.node); }
			bst_node<T> * getP() const { return (_node); }
			bst<T, Compare> * getTree() const { return (_tree); }
		private:
			bst_iter();
	}; // bst_iter

	template <typename T, typename Compare>
	class bst_iterator : public bst_iter<T, Compare>
	{
		public:
//			typedef bst_iterator						iterator;
			typedef T value_type; typedef T * pointer; typedef T & reference;
			typedef std::ptrdiff_t						difference_type;
			typedef ft::bidirectional_iterator_tag		iterator_category;
			typedef bst<T, Compare>						Tree;
			typedef bst_node<T>							Node;

			// ctor works by calling the ctor of base class bst_iter
			bst_iterator()
				: bst_iter<T, Compare>(NULL, NULL) {}
			bst_iterator(Tree * tree)
				: bst_iter<T, Compare>(tree, NULL) {}
			bst_iterator(Tree * tree, Node * node)
				: bst_iter<T, Compare>(tree, node) {}
			bst_iterator(const bst_iterator & other)
				: bst_iter<T, Compare>(other) {}
			~bst_iterator() {}
			bst_iterator & operator=(const bst_iterator & other) {
				if (*this == other) { return (*this); }
				this->_node = other._node; this->_tree = other._tree; return (*this);
			}
			// increment to the closest bigger node according to Compare
			bst_iterator & operator++(void)
			{
				Node *root = this->_tree->getRoot(), *tmp;
				 // if tree is empty, iterator will point to the init node
				if (root == NULL) { this->_node = this->_tree->getInit(); return (*this); }
				// if _node is NULL or past the end, go to the smallest node
				if (this->_node == NULL || this->_node == this->_tree->getInit())
				{
					this->_node = root;
					while (this->_node->left) { this->_node = this->_node->left; }
					return (*this);
				}
				// if there is a subtree on the right...
				if (this->_node->right != NULL)
				{
					// iterator will point to the smallest value in that subtree
					this->_node = this->_node->right;
					while (this->_node->left) { this->_node = this->_node->left; }
					return (*this);
				}
				// if _node is a leaf look for the bigger parent
				tmp = this->_node->parent;
				// while the parent is smaller, go up
				while (tmp != NULL && tmp->right == this->_node)
					{ this->_node = tmp; tmp = this->_node->parent; }
				// if we have reached the root, iterator will just point to init
				if (tmp == NULL) { this->_node = this->_tree.getInit(); }
				// otherwise return the bigger parent :)
				return (*this);
			}

	}; // bst_iterator

	template <typename T, typename Compare>
	class bst
	{
		public:
			typedef T								value_type;
			typedef bst_node<T> 					Node;
			typedef bst<T, Compare>					Tree;
			typedef size_t							size_type;
			typedef bst_iterator<T, Compare>		iterator;
			typedef reverse_iterator<iterator>		reverse_iterator;
		private:
			Compare									_comp;
			Node									*_root;
			Node									*_init;
		public:
			Node * getRoot() { return (_root); }
			Node * getInit() { return (_init); }
	}; // class bst

}; // namespace ft

#endif // BINARY_SEARCH_TREE_HPP
