/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:45:17 by lspiess           #+#    #+#             */
/*   Updated: 2021/02/09 18:19:12 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "iterators.hpp"
# include "enable_if.hpp"
# include "random_access_iterator.hpp"
# include <sstream>
# include <typeinfo>
# include <iostream>
# include <cstddef>
# include <limits>

namespace ft
{
	template <typename T1, typename T2>
	struct pair // a pair of objects
	{
		typedef T1 first_type; typedef T2 second_type;
		T1 first; T2 second;

		pair() : first(), second() {}
		~pair() {}
		pair(const T1 & first, const T2 & second) : first(first), second(second) {}
		pair(const pair &other) : first(other.first), second(other.second) {}

		// this ctor works with iterator types
		template <typename A, typename B>
		pair(const pair<A, B> & ptr)
		: first(ptr.first), second(ptr.second) {}

		pair & operator=(const pair & other) {
			if (*this == other) { return (*this); }
			first = other.first; second = other.second;  return (*this);
		}
	}; // struct pair

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(const T1 t1, const T2 t2)
		{ return (pair<T1, T2>(t1, t2)); }

	template <typename T1, typename T2>
	bool operator==(const ft::pair<T1, T2> & lhs, const ft::pair<T1, T2> & rhs)
		{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <typename T>
	struct bst_node // a standard binary tree node
	{
		T elem;		typedef T elem_type;	bst_node *parent, *left, *right;
		bst_node() {}
		bst_node(T elem, bst_node *parent, bst_node *left, bst_node *right)
		: elem(elem), parent(parent), left(left), right(right)
		{}
		bst_node(const bst_node & other)
		: elem(other.elem), parent(other.parent), left(other.left), right(other.right) {}
		bst_node(const bst_node * other)
		: elem(other->elem), parent(other->parent), left(other->left), right(other->right) {}
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
				: _tree(other._tree), _node(other._node) {}
			bool operator==(const bst_iter<T, Compare> & rhs) const
				{ return (_node == rhs._node); }
			bool operator!=(const bst_iter<T, Compare> & rhs) const
				{ return (_node != rhs._node); }
			bst_node<T> * getP() const { return (_node); }
			bst<T, Compare> * getTree() const { return (_tree); }
		private:
			bst_iter();
	}; // bst_iter

	template <typename T, typename Compare>
	class bst_iterator : public bst_iter<T, Compare>
	{
		public:
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
				Node *root = this->_tree->getRoot();
				 // if tree is empty, iterator will point to the init node
				if (root == NULL) { this->_node = this->_tree->getInit(); return (*this); }
				// if _node is NULL or out of bounds, go to the smallest node
				if (this->_node == NULL || this->_node == this->_tree->getInit())
				{
					this->_node = root;
					while (this->_node->left) { this->_node = this->_node->left; }
					return (*this);
				}
					std::cout << "\t\t\tIn increment...\n";
					std::cout << "\t\t\tthis->_node = " << this->_node << "\n";
					std::cout << "\t\t\tthis->_node->right = " << this->_node->right << "\n";
				// if there is a subtree on the right...
				if (this->_node->right != NULL)
				{
					// iterator will point to the smallest value in that subtree
					this->_node = this->_node->right;
					while (this->_node->left) { this->_node = this->_node->left; }
					return (*this);
				}
				// this->node is the rightmost node of its branch. Gotta look
				// for a bigger parent.
				// While the parent is smaller than the child, go up...
				while (this->_node->parent && this->_node->parent->right == this->_node)
					{ this->_node = this->_node->parent; }
				// then go to that parent
				this->_node = this->_node->parent;
				// if we haven't found a bigger parent, return init
				if (this->_node == NULL) { this->_node = this->_tree->getInit(); }
				return (*this);
			}

			bst_iterator operator++(int)
				{ bst_iterator ret(*this); operator++(); return (ret); }

			bst_iterator &operator--(void)
			{
				Node *root = this->_tree->getRoot(), *tmp;
				 // if tree is empty, iterator will point to the init node
				if (root == NULL) { this->_node = this->_tree->getInit(); return (*this); }
				// if _node is NULL or out of bounds, go to the biggest node
				if (this->_node == NULL || this->_node == this->_tree->getInit())
				{
					this->_node = root;
					while (this->_node->right) { this->_node = this->_node->right; }
					return (*this);
				}
				// if there is a subtree on the left...
				if (this->_node->left != NULL)
				{
					// iterator will point to the biggest value in that subtree
					this->_node = this->_node->left;
					while (this->_node->right) { this->_node = this->_node->right; }
					return (*this);
				}
				// if _node is a leaf, look for the next smaller parent
				tmp = this->_node->parent;
				// while the parent is bigger, go up
				while (tmp != NULL && tmp->left == this->_node)
					{ this->_node = tmp; tmp = this->_node->parent; }
				this->_node = tmp;
				// if we have reached the root, iterator will just point to init
				if (tmp == NULL) { this->_node = this->_tree.getInit(); }
				// otherwise iterator points to the closest smaller parent
				return (*this);
			}

			bst_iterator operator--(int)
				{ bst_iterator ret(*this); operator--(); return (ret); }

			T & operator*() const { return (this->_node->elem); }
			T * operator->() const { return (&(this->_node->elem)); }
	}; // bst_iterator

	template <typename T, typename Compare>
	class bst_const_iterator : public bst_iter<T, Compare>
	{
		public:
			typedef T value_type; typedef T * pointer; typedef T & reference;
			typedef std::ptrdiff_t						difference_type;
			typedef ft::bidirectional_iterator_tag		iterator_category;
			typedef bst<T, Compare>						Tree;
			typedef bst_node<T>							Node;

			// ctor works by calling the ctor of base class bst_iter
			bst_const_iterator()
				: bst_iter<T, Compare>(NULL, NULL) {}
			bst_const_iterator(Tree * tree)
				: bst_iter<T, Compare>(tree, NULL) {}
			bst_const_iterator(Tree * tree, Node * node)
				: bst_iter<T, Compare>(tree, node) {}
			bst_const_iterator(const bst_iterator<T, Compare> & other)
				: bst_iter<T, Compare>(other) {}
			~bst_const_iterator() {}

			bst_const_iterator & operator=(const bst_const_iterator & other) {
				if (*this == other) { return (*this); }
				this->_node = other._node; this->_tree = other._tree; return (*this);
			}

			T & operator*() const { return (this->_node->elem); }
			T & operator->() const { return (&(this->_node->elem)); }

			// increment to the closest bigger node according to Compare
			bst_const_iterator & operator++(void)
			{
				Node *root = this->_tree->getRoot(), *tmp;
				 // if tree is empty, iterator will point to the init node
				if (root == NULL) { this->_node = this->_tree->getInit(); return (*this); }
				// if _node is NULL or out of bounds, go to the smallest node
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
				// if _node is a leaf look for the closest bigger parent
				tmp = this->_node->parent;
				// while the parent is smaller, go up
				while (tmp != NULL && tmp->right == this->_node)
					{ this->_node = tmp; tmp = this->_node->parent; }
				this->_node = tmp;
				// if we have reached the root, iterator will just point to init
				if (tmp == NULL) { this->_node = this->_tree.getInit(); }
				// otherwise iterator points to the closest bigger parent
				return (*this);
			}

			bst_const_iterator operator++(int)
				{ bst_const_iterator ret(*this); operator++(); return (ret); }

			bst_const_iterator &operator--(void)
			{
				Node *root = this->_tree->getRoot(), *tmp;
				 // if tree is empty, iterator will point to the init node
				if (root == NULL) { this->_node = this->_tree->getInit(); return (*this); }
				// if _node is NULL or out of bounds, go to the biggest node
				if (this->_node == NULL || this->_node == this->_tree->getInit())
				{
					this->_node = root;
					while (this->_node->right) { this->_node = this->_node->right; }
					return (*this);
				}
				// if there is a subtree on the left...
				if (this->_node->left != NULL)
				{
					// iterator will point to the biggest value in that subtree
					this->_node = this->_node->left;
					while (this->_node->right) { this->_node = this->_node->right; }
					return (*this);
				}
				// if _node is a leaf, look for the next smaller parent
				tmp = this->_node->parent;
				// while the parent is bigger, go up
				while (tmp != NULL && tmp->left == this->_node)
					{ this->_node = tmp; tmp = this->_node->parent; }
				this->_node = tmp;
				// if we have reached the root, iterator will just point to init
				if (tmp == NULL) { this->_node = this->_tree.getInit(); }
				// otherwise iterator points to the closest smaller parent
				return (*this);
			}

			bst_const_iterator operator--(int)
				{ bst_const_iterator ret(*this); operator--(); return (ret); }
	}; // bst_iterator

	template <typename T, typename Compare>
	class bst
	{
		public:
			typedef T									value_type;
			typedef bst_node<T> 						Node;
			typedef bst<T, Compare>						Tree;
			typedef size_t								size_type;
			typedef bst_iterator<T, Compare>			iterator;
			typedef bst_const_iterator<T, Compare>		const_iterator;

			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef std::allocator<T>					TypeAlloc;
			typedef std::allocator<Node>				NodeAlloc;
		private:
			NodeAlloc								_node_alloc;
			Compare									_cmp;
			// _root is the first node in the binary tree
			Node									*_root;
			// _init represents the past-the-end elem of the container
			Node									*_init;
			bst() {};

			// recursively free a tree/subtree starting at root (inclusive)
			void deep_free(Node * root)
			{
				if (root == NULL) { return ; }
				deep_free(root->left); deep_free(root->right);
				_node_alloc.destroy(root); _node_alloc.deallocate(root, 1);
			}

			// recursively create a deep copy of a tree/subtree starting at src
			Node *deep_copy(Node *parent, Node *src)
			{
				if (src == NULL) { return (NULL); }
				Node * newnode = _node_alloc.allocate(1);
				_node_alloc.construct(newnode, Node(src->elem, parent, NULL, NULL));
				newnode->left = deep_copy(newnode, src->left);
				newnode->right = deep_copy(newnode, src->right);
				return (newnode);
			}

		public:
			Node * getRoot() { return (_root); }
			Node * getInit() { return (_init); }

			bst(Compare comp) : _cmp(comp), _root(NULL)
			{
				_init = _node_alloc.allocate(1);
				_node_alloc.construct(_init, Node(T(), NULL, NULL, NULL));
			}

			bst(const bst & other)
			: _cmp(other._cmp)
			{
				_root = deep_copy(NULL, other._root);
				_init = _node_alloc.allocate(1);
				_node_alloc.construct(_init, Node(T(),  NULL, NULL, NULL));
			}

			bst & operator=(const bst & other)
			{
				if (this == &other) { return (*this); }
				deep_free(_root);
				_root = deep_copy(NULL, other._root); _cmp = other._cmp;
				return (*this);
			}

			virtual ~bst() { deep_free(_root); _node_alloc.deallocate(_init, 1); }

			// Look for a pre-existing node whose key equals val's.
			// If not present, create and insert it in the tree.
			// Return a pair comprising the iterator to the relevant node and
			// a boolean, set to true if a new node was created, false otherwise.
			pair<iterator, bool> insert(const value_type & val)
			{
				Node *newnode, *head = _root;
				if (_root == NULL)
				{
					_root = _node_alloc.allocate(1);
					_node_alloc.construct(_root, Node(val, NULL, NULL, NULL));
					return (make_pair(iterator(this, _root), true));
				}
				while (1)
				{
					// if the current node's key is same as our value's key
					if (head->elem.first == val.first)
						return (make_pair(iterator(this, head), false));
					// if val is less than head->elem
					if (_cmp(val, head->elem))
					{
						if (head->left != NULL) { head = head->left; }
						else
						{
							newnode = _node_alloc.allocate(1);
							_node_alloc.construct(newnode, Node(val, head, NULL, NULL));
							head->left = newnode; break ;
						}
					}
					else
					{
						if (head->right != NULL) { head = head->right; }
						else
						{
							newnode = _node_alloc.allocate(1);
							_node_alloc.construct(newnode, Node(val, head, NULL, NULL));
							head->right = newnode; break ;
						}
					}
				}
				return (make_pair(iterator(this, newnode), true));
			}

			bool remove(const value_type & val)
			{
				std::cout << "===============================\n";
				printTree();
				std::cout << "===============================\n";
				bool ret = remove(_root, val);
//				return (remove(_root, val));
				std::cout << "===============================\n";
				printTree();
				std::cout << "===============================\n";
				return (ret);
			}

			bool remove(Node * root, const value_type & val)
			{
				std::cout << "-----\nIn remove, target = " << val.first << "\n";
				if (root == NULL) { return (false); } Node * head = root;
				// go through the tree and find the matching key
				while (head)
				{
					if (head->elem.first == val.first)
						break ;
					if (_cmp(val, head->elem))
						head = head->left;
					else
						head = head->right;
				}

				if (head == NULL) { std::cout << "\tHead == NULL, returning\n" << "\n"; }
				else {
					std::cout << "\tHead arrived to : " << head << ", "<< head->elem.first
						<< ", " << head->elem.second << "\n";
				}

				// if no node with a matching key was not found, return
				if (head == NULL) { return (false); }
				// save some info needed to rearrange the tree...
				Node *leftchild = head->left, *rightchild = head->right;
				std::cout << "leftchild = " << leftchild << ", rightchild = " << rightchild
					<< "\n";
				Node *parent = head->parent;
				std::cout << "parent = " << parent << "\n";
				bool headside = 0; // the node's position relative to its parent

				if (parent)
				{
					if (parent->left == head)
						{ parent->left = NULL; headside = 0; }
					else if (parent->right == head)
						{ parent->right = NULL; headside = 1; }
				}
//				std::cout << "After zeroing, parent (" << parent << ") left = "
//					<< parent->left << ", right = " << parent->right << "\n";


//				if (parent)
//				{
//					std::cout << "parent = " << parent << "parent->left = "
//					<< parent->left << ", " << "parent->right = " << parent->right << "\n";
//					std::cout << "head = " << head << "\n";
//					if (parent->left == head)
//					{
//						headside = 0;
//					}
//					else { headside = 1; }
//					std::cout << "\theadside = " << headside << "\n";
//				}
//				// just zeroing the parent's pointer to the node
//				if (parent) 
//				{
//					std::cout << "\tzeroing parent branch\n";
//					if (headside == 0) { parent->left = NULL; }
//					else { parent->right = NULL; }
//					std::cout << "parent->left = " << parent->left
//						<< ", parent->right = " << parent->right << "\n";
//				}

				// deleting the node
				std::cout << "\tdeallocating " << head << "\n";
				Node * to_free = head;
				_node_alloc.destroy(head); _node_alloc.deallocate(head, 1); head = NULL;
				std::cout << "\tdeallocated, headside = " << headside << "\n";

				// if the deleted node was not a leaf, rearrange the tree :
				Node * substitute; bool subtreeside;
				if (leftchild)
				{
					std::cout << "\t\tfinding max in leftchild...";
					substitute = find_max(leftchild); subtreeside = 0;
					std::cout << " substitute = " << substitute->elem.first
						<< ", " << substitute->elem.second << "\n";
				}
				else if (rightchild)
				{
					std::cout << "\t\tfinding min in rightchild...";
					substitute = find_min(rightchild); subtreeside = 1;
					std::cout << " substitute = " << substitute->elem.first
						<< ", " << substitute->elem.second << "\n";
				}
				else // no subtrees means we removed a leaf node
				{
					std::cout << "\tjust deleted a leaf, returning...\n";
					return (true); // no repositioning needed
				}

				if (parent != NULL)
				{
					if ( headside == 0)
					{
						parent->left = _node_alloc.allocate(1);
						_node_alloc.construct(parent->left, Node(substitute->elem,
							parent, leftchild, rightchild));
						head = parent->left;
					}
					else
					{
						parent->right = _node_alloc.allocate(1);
						_node_alloc.construct(parent->right, Node(substitute->elem,
							parent, leftchild, rightchild));
						head = parent->right;
					}
				}
				else
				{
					_root = _node_alloc.allocate(1);
					_node_alloc.construct(_root, Node(substitute->elem,
						NULL, leftchild, rightchild));
					head = _root;
				}
				head->left = leftchild; head->right = rightchild;
				if (leftchild) { leftchild->parent = head; }
				if (rightchild) { rightchild->parent = head; }

				std::cout << "Substituted the deleted node. Printing :\n";
				printTree();
				std::cout << "Removing the double...\n";
				// now that we have copied the substitute in the deleted
				// node's place, we remove the original down in the subtree
				if (subtreeside == 0)
					remove(head->left, head->elem);
				else
					remove(head->right, head->elem);
				return (true);
			}

			Node * find_max(Node * root)
			{
				Node * head = root; if (root == NULL) { return NULL; }
				while (head->right) { head = head->right; }
				return (head);
			}
			Node * find_min(Node * root)
			{
				Node * head = root; if (root == NULL) { return NULL; }
				while (head->left) { head = head->right; }
				return (head);
			}

			size_type getTreeSize(Node *node) const
			{
				if (node == NULL) { return (0); }
				return (1 + getTreeSize(node->left) + getTreeSize(node->right));
			}

			size_type getSize() const
			{
				Node * node = _root;
				return (getTreeSize(node));
			}

			void printTree(Node *node, int space) const
			{
				if (node)
				{
					if (node->right) { printTree(node->right, 0); }
				}
//				std::cout << node->elem.first << ", " <<  node->elem.second
//					<< " [" << node << "]\n";
//				if (!node) { return ; }
//				if (node->right)
//				{
//					printTree(node->right, space + 1);
//				}
//				for (int i = 0; i < space; i++) { std::cout << "\t"; }
//				std::cout << node->elem.first << ", " <<  node->elem.second
//					<< " [" << node << "]\n";
//				if (node->left)
//				{
//					printTree(node->right, space + 1);
//				}
			}

			void printTree(Node * node) const { printTree(node, 0); }

			void printTree() const { printTree(_root); }
	}; // class bst

	template <class T>
	struct less : std::binary_function<T, T, bool>
	{
		bool operator()(const T & x, const T & y) const { return x < y; }
	}; // struct less

	// Key : type of the key object
	// T : type of the mapped object
	// Compare : comparison functor
	template <typename Key, typename T, class Compare = ft::less<Key>,
				class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
		public:
			typedef Key key_type; typedef T mapped_type;
			typedef Compare key_compare; typedef Alloc allocator_type;
			typedef pair<const Key, T>						value_type;

			// this is just a wrapper around typename Compare.
			// Given two pairs, it accesses and compares their keys to see
			// which comes before the other.
			class value_compare
			{
				private:
					Compare comp;
					value_compare() {}
				public:
					typedef pair<const Key, T>			first_argument_type;
					typedef pair<const Key, T>			second_argument_type;;
					value_compare(const Compare & c)
					: comp(c) {}
					bool operator() (const value_type & x, const value_type & y) const
					{ return (comp(x.first, y.first)); }
			}; // class value_compare

			typedef std::ptrdiff_t						difference_type;
			typedef size_t								size_type;
			typedef typename bst<value_type, value_compare>::iterator
														iterator;
			typedef typename bst<value_type, value_compare>::const_iterator
														const_iterator;
			typedef typename bst<value_type, value_compare>::reverse_iterator
														reverse_iterator;
			typedef typename bst<value_type, value_compare>::const_reverse_iterator
														const_reverse_iterator;
			typedef bst_node< pair<const Key, T> >		Node;

		private:
			bst< pair<const Key, T>, value_compare>			_tree;
			Alloc											_alloc;
		public:
			// create a map with no elements
			explicit map(const key_compare & comp = key_compare(),
						const allocator_type & alloc = allocator_type())
			: _tree(value_compare(comp)), _alloc(alloc)
			{}

			// create a map consisting of copies of elements from [first, last)
			template <typename InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare & comp = key_compare(),
				const allocator_type & alloc = allocator_type())
			: _tree(value_compare(comp)), _alloc(alloc)
			{
				while (first != last) { _tree.insert(*first); ++first; }
			}

			map(const map & other)
			: _tree(other._tree), _alloc(other._alloc)
			{}

			~map() {}

			map & operator=(const map & rhs)
			{
				if (this == &rhs) { return (*this); }
				_tree = rhs._tree; _alloc = rhs._alloc; return (*this);
			}

			iterator begin()
			{
				Node *head = _tree.getRoot();
				if (!head) { return (iterator(&_tree, _tree.getInit())); }
				while (head->left) { head = head->left; }
				return (iterator(&_tree, head));
			}
			iterator begin() const { Node *head = _tree.getRoot();
				if (!head) { return (const_iterator(&_tree, _tree.getInit())); }
				while (head->left) { head = head->left; }
				return (const_iterator(&_tree, head)); }

			iterator end() { return (iterator(&_tree, _tree.getInit())); }
			iterator end() const { return (const_iterator(&_tree, _tree.getInit())); }

			reverse_iterator rbegin() { return (reverse_iterator(end())); }
			reverse_iterator rbegin() const { return (reverse_const_iterator(end())); }
			reverse_iterator rend() { return (reverse_iterator(begin())); }
			reverse_iterator rend() const { return (reverse_const_iterator(begin())); }

			bool empty() const { return (_tree.getSize() == 0); }

			size_type size() const { return (_tree.getSize()); }

			size_type max_size() const { return (allocator_type().max_size()); }

			// return the value associated with the key k.
			// If no node holding that key exists, a node with that key is
			// created using default value which is then returned.
			T & operator[] (const Key & k)
			{
				iterator itr = find(k);
				if (itr == end())
				{ itr = _tree.insert(ft::make_pair(k, mapped_type())).first; }
				return ((*itr).second);
			}

			pair<iterator, bool> insert(const value_type & val)
			{ return (_tree.insert(val)); }

			pair<iterator, bool> insert(iterator hint, const value_type & val)
			{ static_cast<void>(hint); return (_tree.insert(val)); }

			void insert(iterator first, iterator last)
			{ while (first != last) { _tree.insert(*first); ++first; } }

			void erase(iterator position) { _tree.remove(*position); }

			void erase(const Key & k)
			{
				std::cout << "Calling erase on key : " << k << "\n";
				_tree.remove(ft::make_pair(k, mapped_type()));
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
				{
					std::cout << "sfsg\n";
					std::cout << "erasing : " << (*first).first << "\n";
					erase((*first).first);
					std::cout << "about to ++first....\n";
					++first;
				}
			}

			void swap(map & other)
			{
				std::swap(_alloc, other._alloc); std::swap(_tree, other._tree);
			}

			void clear() { erase(begin(), end()); }

			key_compare key_comp() const { return (key_compare()); }

			value_compare value_comp() const { return (value_compare(key_compare())); }

			iterator find(const key_type & k) 
			{
				Node * head = _tree.getRoot(); key_compare comp;
				while (head)
				{
					if (head->elem.first == k) { return (iterator(&_tree, head)); }
					if (comp(k, head->elem.first) == true)
						head = head->left;
					else
						head = head->right;
				}
				return (end());
			}

			const_iterator find(const key_type & k) const {
				Node * head = _tree.getRoot();
				while (head) {
					if (head->elem->first == k) { return (const_iterator(&_tree, head)); }
					if (comp(k, head->elem->first) == true)
						head = head->left;
					else
						head = head->right;
				} return (end());
			}

			// find the number of elements with a given key. This only makes
			// sense for multimaps, as basic map does not allow doubles.
			size_type count(const key_type & k)
			{
				iterator itr = find(k);
				if (itr != end()) { return (1); } else { return (0); }
			}

			// return an iterator to the first element equal to or greater
			// than key, or end()
			iterator lower_bound(const key_type & k)
			{
				Node *head = _tree.getRoot(); key_compare comp;
				while (head)
				{
					if (head->elem.first == k) { return (iterator(&_tree, head)); }
					if (comp(head->elem.first, k) == true)
						head = head->left;
					else if (head->right)
					{
						head = head->right;
						while (head->left) { head = head->left; }
						return (iterator(&_tree, head));
					}
				}
				return (end());
			}
			const_iterator lower_bound(const key_type & k) const
			{
				Node *head = _tree.getRoot(); key_compare comp;
				while (head)
				{
					if (head->elem.first == k) { return (const_iterator(&_tree, head)); }
					if (comp(head->elem.first, k) == true)
						head = head->left;
					else if (head->right)
					{
						head = head->right;
						while (head->left) { head = head->left; }
						return (const_iterator(&_tree, head));
					}
				}
				return (end());
			}

			// return an iterator to the first element equal to or smaller
			// than key, or end()
			iterator upper_bound(const key_type & k)
			{
				Node *head = _tree.getRoot(); key_compare comp;
				while (head)
				{
					if (head->elem.first == k) { return (iterator(&_tree, head)); }
					if (comp(k, head->elem.first) == true)
						head = head->right;
					else if (head->left)
					{
						head = head->left;
						while (head->right) { head = head->right; }
						return (iterator(&_tree, head));
					}
				}
				return (end());
			}
			const_iterator upper_bound(const key_type & k) const
			{
				Node *head = _tree.getRoot(); key_compare comp;
				while (head)
				{
					if (head->elem.first == k) { return (const_iterator(&_tree, head)); }
					if (comp(k, head->elem.first) == true)
						head = head->right;
					else if (head->left)
					{
						head = head->left;
						while (head->right) { head = head->right; }
						return (const_iterator(&_tree, head));
					}
				}
				return (end());
			}

			// return a pair of iterator that possibly point to the subsequence
			// matching the given key. Again, only makes sense for multimaps.
			pair<const_iterator, const_iterator> equal_range(const key_type & k) const
			{ return (ft::make_pair(lower_bound(k), upper_bound(k))); }

			// return a pair of iterator that possibly point to the subsequence
			// matching the given key. Again, only makes sense for multimaps.
			pair<iterator, iterator> equal_range(const key_type & k)
			{ return (ft::make_pair(lower_bound(k), upper_bound(k))); }

			void printMap() const { _tree.printTree(); }

	}; // class map

}; // namespace ft

#endif // BINARY_SEARCH_TREE_HPP
