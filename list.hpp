#ifndef LIST_HPP
# define LIST_HPP

namespace detail
{
	struct List_node_base
	{
		List_node_base * next;
		List_node_base * prev;

		static void swap(List_node_base& __x, _List_node_base& __y);

		void _M_transfer(_List_node_base* const __first,
						List_node_base* const __last);

		void _M_reverse() ;

		void _M_hook(List_node_base* const __position);

		void _M_unhook() _GLIBCXX_USE_NOEXCEPT;
	};

    /// The %list node header.
    struct _List_node_header : public _List_node_base
    {
      _List_node_header() 
      { _M_init(); }

      void _M_init() 
      {
	this->_M_next = this->_M_prev = this;
      }

    private:
      _List_node_base* _M_base() { return this; }
} // namespace detail

namespace ft
{
	// ============= BITS STL ITERATOR LIST =============
 
	// Supporting structures are split into common and templated
	// types; the latter publicly inherits from the former in an
	// effort to reduce code duplication.  This results in some
	// "needless" static_cast'ing later on, but it's all safe
	// downcasting.

_GLIBCXX_BEGIN_NAMESPACE_CONTAINER

  /// An actual node in the %list.
  template<typename _Tp>
    struct _List_node : public __detail::_List_node_base
    {
      _Tp _M_data;
      _Tp*       _M_valptr()       { return std::__addressof(_M_data); }
      _Tp const* _M_valptr() const { return std::__addressof(_M_data); }
    };

  /**
   *  @brief A list::iterator.
   *
   *  All the functions are op overloads.
  */
  template<typename _Tp>
    struct _List_iterator
    {
      typedef _List_iterator<_Tp>		_Self;
      typedef _List_node<_Tp>			_Node;

      typedef ptrdiff_t				difference_type;
      typedef std::bidirectional_iterator_tag	iterator_category;
      typedef _Tp				value_type;
      typedef _Tp*				pointer;
      typedef _Tp&				reference;

      _List_iterator() _GLIBCXX_NOEXCEPT
      : _M_node() { }

      explicit
      _List_iterator(__detail::_List_node_base* __x) _GLIBCXX_NOEXCEPT
      : _M_node(__x) { }

      _Self
      _M_const_cast() const _GLIBCXX_NOEXCEPT
      { return *this; }

      // Must downcast from _List_node_base to _List_node to get to value.
      reference
      operator*() const _GLIBCXX_NOEXCEPT
      { return *static_cast<_Node*>(_M_node)->_M_valptr(); }

      pointer
      operator->() const _GLIBCXX_NOEXCEPT
      { return static_cast<_Node*>(_M_node)->_M_valptr(); }

      _Self&
      operator++() _GLIBCXX_NOEXCEPT
      {
	_M_node = _M_node->_M_next;
	return *this;
      }

      _Self
      operator++(int) _GLIBCXX_NOEXCEPT
      {
	_Self __tmp = *this;
	_M_node = _M_node->_M_next;
	return __tmp;
      }

      _Self&
      operator--() _GLIBCXX_NOEXCEPT
      {
	_M_node = _M_node->_M_prev;
	return *this;
      }

      _Self
      operator--(int) _GLIBCXX_NOEXCEPT
      {
	_Self __tmp = *this;
	_M_node = _M_node->_M_prev;
	return __tmp;
      }

      friend bool
      operator==(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
      { return __x._M_node == __y._M_node; }

#if __cpp_impl_three_way_comparison < 201907L
      friend bool
      operator!=(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
      { return __x._M_node != __y._M_node; }
#endif

      // The only member points to the %list element.
      __detail::_List_node_base* _M_node;
    };

  /**
   *  @brief A list::const_iterator.
   *
   *  All the functions are op overloads.
  */
  template<typename _Tp>
    struct _List_const_iterator
    {
      typedef _List_const_iterator<_Tp>		_Self;
      typedef const _List_node<_Tp>		_Node;
      typedef _List_iterator<_Tp>		iterator;

      typedef ptrdiff_t				difference_type;
      typedef std::bidirectional_iterator_tag	iterator_category;
      typedef _Tp				value_type;
      typedef const _Tp*			pointer;
      typedef const _Tp&			reference;

      _List_const_iterator() _GLIBCXX_NOEXCEPT
      : _M_node() { }

      explicit
      _List_const_iterator(const __detail::_List_node_base* __x)
      : _M_node(__x) { }

      _List_const_iterator(const iterator& __x)
      : _M_node(__x._M_node) { }

      iterator
      _M_const_cast() const
      { return iterator(const_cast<__detail::_List_node_base*>(_M_node)); }

      // Must downcast from List_node_base to _List_node to get to value.
      reference
      operator*() const
      { return *static_cast<_Node*>(_M_node)->_M_valptr(); }

      pointer
      operator->() const
      { return static_cast<_Node*>(_M_node)->_M_valptr(); }

      _Self&
      operator++()
      {
	_M_node = _M_node->_M_next;
	return *this;
      }

      _Self
      operator++(int)
      {
	_Self __tmp = *this;
	_M_node = _M_node->_M_next;
	return __tmp;
      }

      _Self&
      operator--()
      {
	_M_node = _M_node->_M_prev;
	return *this;
      }

      _Self
      operator--(int)
      {
	_Self __tmp = *this;
	_M_node = _M_node->_M_prev;
	return __tmp;
      }

      friend bool
      operator==(const _Self& __x, const _Self& __y)
      { return __x._M_node == __y._M_node; }

#if __cpp_impl_three_way_comparison < 201907L
      friend bool
      operator!=(const _Self& __x, const _Self& __y)
      { return __x._M_node != __y._M_node; }
#endif

      // The only member points to the %list element.
      const __detail::_List_node_base* _M_node;
    };

_GLIBCXX_BEGIN_NAMESPACE_CXX11
  /// See bits/stl_deque.h's _Deque_base for an explanation.
  template<typename _Tp, typename _Alloc>
    class _List_base
    {
    protected:
      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
	rebind<_Tp>::other				_Tp_alloc_type;
      typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>	_Tp_alloc_traits;
      typedef typename _Tp_alloc_traits::template
	rebind<_List_node<_Tp> >::other _Node_alloc_type;
      typedef __gnu_cxx::__alloc_traits<_Node_alloc_type> _Node_alloc_traits;

#if !_GLIBCXX_INLINE_VERSION
      static size_t
      _S_distance(const __detail::_List_node_base* __first,
		  const __detail::_List_node_base* __last)
      {
	size_t __n = 0;
	while (__first != __last)
	  {
	    __first = __first->_M_next;
	    ++__n;
	  }
	return __n;
      }
#endif

      struct _List_impl
      : public _Node_alloc_type
      {
	__detail::_List_node_header _M_node;

	_List_impl() _GLIBCXX_NOEXCEPT_IF(
	    is_nothrow_default_constructible<_Node_alloc_type>::value)
	: _Node_alloc_type()
	{ }

	_List_impl(const _Node_alloc_type& __a) _GLIBCXX_NOEXCEPT
	: _Node_alloc_type(__a)
	{ }

      };

      _List_impl _M_impl;

#if _GLIBCXX_USE_CXX11_ABI
      size_t _M_get_size() const { return _M_impl._M_node._M_size; }

      void _M_set_size(size_t __n) { _M_impl._M_node._M_size = __n; }

      void _M_inc_size(size_t __n) { _M_impl._M_node._M_size += __n; }

      void _M_dec_size(size_t __n) { _M_impl._M_node._M_size -= __n; }

# if !_GLIBCXX_INLINE_VERSION
      size_t
      _M_distance(const __detail::_List_node_base* __first,
		  const __detail::_List_node_base* __last) const
      { return _S_distance(__first, __last); }

      // return the stored size
      size_t _M_node_count() const { return _M_get_size(); }
# endif
#else
      // dummy implementations used when the size is not stored
      size_t _M_get_size() const { return 0; }
      void _M_set_size(size_t) { }
      void _M_inc_size(size_t) { }
      void _M_dec_size(size_t) { }

# if !_GLIBCXX_INLINE_VERSION
      size_t _M_distance(const void*, const void*) const { return 0; }

      // count the number of nodes
      size_t _M_node_count() const
      {
	return _S_distance(_M_impl._M_node._M_next,
			   std::__addressof(_M_impl._M_node));
      }
# endif
#endif

      typename _Node_alloc_traits::pointer
      _M_get_node()
      { return _Node_alloc_traits::allocate(_M_impl, 1); }

      void
      _M_put_node(typename _Node_alloc_traits::pointer __p) _GLIBCXX_NOEXCEPT
      { _Node_alloc_traits::deallocate(_M_impl, __p, 1); }

  public:
      typedef _Alloc allocator_type;

      _Node_alloc_type&
      _M_get_Node_allocator() _GLIBCXX_NOEXCEPT
      { return _M_impl; }

      const _Node_alloc_type&
      _M_get_Node_allocator() const _GLIBCXX_NOEXCEPT
      { return _M_impl; }

      _List_base() { }

      _List_base(const _Node_alloc_type& __a) _GLIBCXX_NOEXCEPT
      : _M_impl(__a)
      { }

      // This is what actually destroys the list.
      ~_List_base() _GLIBCXX_NOEXCEPT
      { _M_clear(); }

      void
      _M_clear() _GLIBCXX_NOEXCEPT;

      void
      _M_init() _GLIBCXX_NOEXCEPT
      { this->_M_impl._M_node._M_init(); }
    };

  /**
   *  @brief A standard container with linear time access to elements,
   *  and fixed time insertion/deletion at any point in the sequence.
   *
   *  @ingroup sequences
   *
   *  @tparam _Tp  Type of element.
   *  @tparam _Alloc  Allocator type, defaults to allocator<_Tp>.
   *
   *  Meets the requirements of a <a href="tables.html#65">container</a>, a
   *  <a href="tables.html#66">reversible container</a>, and a
   *  <a href="tables.html#67">sequence</a>, including the
   *  <a href="tables.html#68">optional sequence requirements</a> with the
   *  %exception of @c at and @c operator[].
   *
   *  This is a @e doubly @e linked %list.  Traversal up and down the
   *  %list requires linear time, but adding and removing elements (or
   *  @e nodes) is done in constant time, regardless of where the
   *  change takes place.  Unlike std::vector and std::deque,
   *  random-access iterators are not provided, so subscripting ( @c
   *  [] ) access is not allowed.  For algorithms which only need
   *  sequential access, this lack makes no difference.
   *
   *  Also unlike the other standard containers, std::list provides
   *  specialized algorithms %unique to linked lists, such as
   *  splicing, sorting, and in-place reversal.
   *
   *  A couple points on memory allocation for list<Tp>:
   *
   *  First, we never actually allocate a Tp, we allocate
   *  List_node<Tp>'s and trust [20.1.5]/4 to DTRT.  This is to ensure
   *  that after elements from %list<X,Alloc1> are spliced into
   *  %list<X,Alloc2>, destroying the memory of the second %list is a
   *  valid operation, i.e., Alloc1 giveth and Alloc2 taketh away.
   *
   *  Second, a %list conceptually represented as
   *  @code
   *    A <---> B <---> C <---> D
   *  @endcode
   *  is actually circular; a link exists between A and D.  The %list
   *  class holds (as its only data member) a private list::iterator
   *  pointing to @e D, not to @e A!  To get to the head of the %list,
   *  we start at the tail and move forward by one.  When this member
   *  iterator's next/previous pointers refer to itself, the %list is
   *  %empty.
  */
  template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class list : protected _List_base<_Tp, _Alloc>
    {
#ifdef _GLIBCXX_CONCEPT_CHECKS
      // concept requirements
      typedef typename _Alloc::value_type		_Alloc_value_type;
# if __cplusplus < 201103L
      __glibcxx_class_requires(_Tp, _SGIAssignableConcept)
# endif
      __glibcxx_class_requires2(_Tp, _Alloc_value_type, _SameTypeConcept)
#endif

      typedef _List_base<_Tp, _Alloc>			_Base;
      typedef typename _Base::_Tp_alloc_type		_Tp_alloc_type;
      typedef typename _Base::_Tp_alloc_traits		_Tp_alloc_traits;
      typedef typename _Base::_Node_alloc_type		_Node_alloc_type;
      typedef typename _Base::_Node_alloc_traits	_Node_alloc_traits;

    public:
      typedef _Tp					 value_type;
      typedef typename _Tp_alloc_traits::pointer	 pointer;
      typedef typename _Tp_alloc_traits::const_pointer	 const_pointer;
      typedef typename _Tp_alloc_traits::reference	 reference;
      typedef typename _Tp_alloc_traits::const_reference const_reference;
      typedef _List_iterator<_Tp>			 iterator;
      typedef _List_const_iterator<_Tp>			 const_iterator;
      typedef std::reverse_iterator<const_iterator>	 const_reverse_iterator;
      typedef std::reverse_iterator<iterator>		 reverse_iterator;
      typedef size_t					 size_type;
      typedef ptrdiff_t					 difference_type;
      typedef _Alloc					 allocator_type;

    protected:
      // Note that pointers-to-_Node's can be ctor-converted to
      // iterator types.
      typedef _List_node<_Tp>				 _Node;

      using _Base::_M_impl;
      using _Base::_M_put_node;
      using _Base::_M_get_node;
      using _Base::_M_get_Node_allocator;

      /**
       *  @param  __args  An instance of user data.
       *
       *  Allocates space for a new node and constructs a copy of
       *  @a __args in it.
       */
      _Node*
      _M_create_node(const value_type& __x)
      {
	_Node* __p = this->_M_get_node();
	__try
	  {
	    _Tp_alloc_type __alloc(_M_get_Node_allocator());
	    __alloc.construct(__p->_M_valptr(), __x);
	  }
	__catch(...)
	  {
	    _M_put_node(__p);
	    __throw_exception_again;
	  }
	return __p;
      }

#if _GLIBCXX_USE_CXX11_ABI
      static size_t
      _S_distance(const_iterator __first, const_iterator __last)
      { return std::distance(__first, __last); }

      // return the stored size
      size_t
      _M_node_count() const
      { return this->_M_get_size(); }
#else
      // dummy implementations used when the size is not stored
      static size_t
      _S_distance(const_iterator, const_iterator)
      { return 0; }

      // count the number of nodes
      size_t
      _M_node_count() const
      { return std::distance(begin(), end()); }
#endif

    public:
      // [23.2.2.1] construct/copy/destroy
      // (assign() and get_allocator() are also listed in this section)

      /**
       *  @brief  Creates a %list with no elements.
       */
      list() { }

      /**
       *  @brief  Creates a %list with no elements.
       *  @param  __a  An allocator object.
       */
      explicit
      list(const allocator_type& __a) _GLIBCXX_NOEXCEPT
      : _Base(_Node_alloc_type(__a)) { }

      /**
       *  @brief  Creates a %list with copies of an exemplar element.
       *  @param  __n  The number of elements to initially create.
       *  @param  __value  An element to copy.
       *  @param  __a  An allocator object.
       *
       *  This constructor fills the %list with @a __n copies of @a __value.
       */
      explicit
      list(size_type __n, const value_type& __value = value_type(),
	   const allocator_type& __a = allocator_type())
      : _Base(_Node_alloc_type(__a))
      { _M_fill_initialize(__n, __value); }

      /**
       *  @brief  %List copy constructor.
       *  @param  __x  A %list of identical element and allocator types.
       *
       *  The newly-created %list uses a copy of the allocation object used
       *  by @a __x (unless the allocator traits dictate a different object).
       */
      list(const list& __x)
      : _Base(_Node_alloc_traits::
	      _S_select_on_copy(__x._M_get_Node_allocator()))
      { _M_initialize_dispatch(__x.begin(), __x.end(), __false_type()); }

      /**
       *  @brief  Builds a %list from a range.
       *  @param  __first  An input iterator.
       *  @param  __last  An input iterator.
       *  @param  __a  An allocator object.
       *
       *  Create a %list consisting of copies of the elements from
       *  [@a __first,@a __last).  This is linear in N (where N is
       *  distance(@a __first,@a __last)).
       */
      template<typename _InputIterator>
	list(_InputIterator __first, _InputIterator __last,
	     const allocator_type& __a = allocator_type())
	: _Base(_Node_alloc_type(__a))
	{
	  // Check whether it's an integral type.  If so, it's not an iterator.
	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	  _M_initialize_dispatch(__first, __last, _Integral());
	}

      /**
       *  @brief  %List assignment operator.
       *  @param  __x  A %list of identical element and allocator types.
       *
       *  All the elements of @a __x are copied.
       *
       *  Whether the allocator is copied depends on the allocator traits.
       */
      list&
      operator=(const list& __x);

      /**
       *  @brief  Assigns a given value to a %list.
       *  @param  __n  Number of elements to be assigned.
       *  @param  __val  Value to be assigned.
       *
       *  This function fills a %list with @a __n copies of the given
       *  value.  Note that the assignment completely changes the %list
       *  and that the resulting %list's size is the same as the number
       *  of elements assigned.
       */
      void
      assign(size_type __n, const value_type& __val)
      { _M_fill_assign(__n, __val); }

      /**
       *  @brief  Assigns a range to a %list.
       *  @param  __first  An input iterator.
       *  @param  __last   An input iterator.
       *
       *  This function fills a %list with copies of the elements in the
       *  range [@a __first,@a __last).
       *
       *  Note that the assignment completely changes the %list and
       *  that the resulting %list's size is the same as the number of
       *  elements assigned.
       */
      template<typename _InputIterator>
	void
	assign(_InputIterator __first, _InputIterator __last)
	{
	  // Check whether it's an integral type.  If so, it's not an iterator.
	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	  _M_assign_dispatch(__first, __last, _Integral());
	}

      /// Get a copy of the memory allocation object.
      allocator_type
      get_allocator() const _GLIBCXX_NOEXCEPT
      { return allocator_type(_Base::_M_get_Node_allocator()); }

      // iterators
      /**
       *  Returns a read/write iterator that points to the first element in the
       *  %list.  Iteration is done in ordinary element order.
       */
      iterator
      begin() _GLIBCXX_NOEXCEPT
      { return iterator(this->_M_impl._M_node._M_next); }

      /**
       *  Returns a read-only (constant) iterator that points to the
       *  first element in the %list.  Iteration is done in ordinary
       *  element order.
       */
      const_iterator
      begin() const _GLIBCXX_NOEXCEPT
      { return const_iterator(this->_M_impl._M_node._M_next); }

      /**
       *  Returns a read/write iterator that points one past the last
       *  element in the %list.  Iteration is done in ordinary element
       *  order.
       */
      iterator
      end() _GLIBCXX_NOEXCEPT
      { return iterator(&this->_M_impl._M_node); }

      /**
       *  Returns a read-only (constant) iterator that points one past
       *  the last element in the %list.  Iteration is done in ordinary
       *  element order.
       */
      const_iterator
      end() const _GLIBCXX_NOEXCEPT
      { return const_iterator(&this->_M_impl._M_node); }

      /**
       *  Returns a read/write reverse iterator that points to the last
       *  element in the %list.  Iteration is done in reverse element
       *  order.
       */
      reverse_iterator
      rbegin() _GLIBCXX_NOEXCEPT
      { return reverse_iterator(end()); }

      /**
       *  Returns a read-only (constant) reverse iterator that points to
       *  the last element in the %list.  Iteration is done in reverse
       *  element order.
       */
      const_reverse_iterator
      rbegin() const _GLIBCXX_NOEXCEPT
      { return const_reverse_iterator(end()); }

      /**
       *  Returns a read/write reverse iterator that points to one
       *  before the first element in the %list.  Iteration is done in
       *  reverse element order.
       */
      reverse_iterator
      rend() _GLIBCXX_NOEXCEPT
      { return reverse_iterator(begin()); }

      /**
       *  Returns a read-only (constant) reverse iterator that points to one
       *  before the first element in the %list.  Iteration is done in reverse
       *  element order.
       */
      const_reverse_iterator
      rend() const _GLIBCXX_NOEXCEPT
      { return const_reverse_iterator(begin()); }


      // [23.2.2.2] capacity
      /**
       *  Returns true if the %list is empty.  (Thus begin() would equal
       *  end().)
       */
      _GLIBCXX_NODISCARD bool
      empty() const _GLIBCXX_NOEXCEPT
      { return this->_M_impl._M_node._M_next == &this->_M_impl._M_node; }

      /**  Returns the number of elements in the %list.  */
      size_type
      size() const _GLIBCXX_NOEXCEPT
      { return _M_node_count(); }

      /**  Returns the size() of the largest possible %list.  */
      size_type
      max_size() const _GLIBCXX_NOEXCEPT
      { return _Node_alloc_traits::max_size(_M_get_Node_allocator()); }

      /**
       *  @brief Resizes the %list to the specified number of elements.
       *  @param __new_size Number of elements the %list should contain.
       *  @param __x Data with which new elements should be populated.
       *
       *  This function will %resize the %list to the specified number
       *  of elements.  If the number is smaller than the %list's
       *  current size the %list is truncated, otherwise the %list is
       *  extended and new elements are populated with given data.
       */
      void
      resize(size_type __new_size, value_type __x = value_type());

      // element access
      /**
       *  Returns a read/write reference to the data at the first
       *  element of the %list.
       */
      reference
      front() _GLIBCXX_NOEXCEPT
      { return *begin(); }

      /**
       *  Returns a read-only (constant) reference to the data at the first
       *  element of the %list.
       */
      const_reference
      front() const _GLIBCXX_NOEXCEPT
      { return *begin(); }

      /**
       *  Returns a read/write reference to the data at the last element
       *  of the %list.
       */
      reference
      back() _GLIBCXX_NOEXCEPT
      {
	iterator __tmp = end();
	--__tmp;
	return *__tmp;
      }

      /**
       *  Returns a read-only (constant) reference to the data at the last
       *  element of the %list.
       */
      const_reference
      back() const _GLIBCXX_NOEXCEPT
      {
	const_iterator __tmp = end();
	--__tmp;
	return *__tmp;
      }

      // [23.2.2.3] modifiers
      /**
       *  @brief  Add data to the front of the %list.
       *  @param  __x  Data to be added.
       *
       *  This is a typical stack operation.  The function creates an
       *  element at the front of the %list and assigns the given data
       *  to it.  Due to the nature of a %list this operation can be
       *  done in constant time, and does not invalidate iterators and
       *  references.
       */
      void
      push_front(const value_type& __x)
      { this->_M_insert(begin(), __x); }

      /**
       *  @brief  Removes first element.
       *
       *  This is a typical stack operation.  It shrinks the %list by
       *  one.  Due to the nature of a %list this operation can be done
       *  in constant time, and only invalidates iterators/references to
       *  the element being removed.
       *
       *  Note that no data is returned, and if the first element's data
       *  is needed, it should be retrieved before pop_front() is
       *  called.
       */
      void
      pop_front() _GLIBCXX_NOEXCEPT
      { this->_M_erase(begin()); }

      /**
       *  @brief  Add data to the end of the %list.
       *  @param  __x  Data to be added.
       *
       *  This is a typical stack operation.  The function creates an
       *  element at the end of the %list and assigns the given data to
       *  it.  Due to the nature of a %list this operation can be done
       *  in constant time, and does not invalidate iterators and
       *  references.
       */
      void
      push_back(const value_type& __x)
      { this->_M_insert(end(), __x); }

      /**
       *  @brief  Removes last element.
       *
       *  This is a typical stack operation.  It shrinks the %list by
       *  one.  Due to the nature of a %list this operation can be done
       *  in constant time, and only invalidates iterators/references to
       *  the element being removed.
       *
       *  Note that no data is returned, and if the last element's data
       *  is needed, it should be retrieved before pop_back() is called.
       */
      void
      pop_back() _GLIBCXX_NOEXCEPT
      { this->_M_erase(iterator(this->_M_impl._M_node._M_prev)); }

      /**
       *  @brief  Inserts given value into %list before specified iterator.
       *  @param  __position  An iterator into the %list.
       *  @param  __x  Data to be inserted.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert a copy of the given value before
       *  the specified location.  Due to the nature of a %list this
       *  operation can be done in constant time, and does not
       *  invalidate iterators and references.
       */
      iterator
      insert(iterator __position, const value_type& __x);


      /**
       *  @brief  Inserts a number of copies of given data into the %list.
       *  @param  __position  An iterator into the %list.
       *  @param  __n  Number of elements to be inserted.
       *  @param  __x  Data to be inserted.
       *
       *  This function will insert a specified number of copies of the
       *  given data before the location specified by @a position.
       *
       *  This operation is linear in the number of elements inserted and
       *  does not invalidate iterators and references.
       */
      void
      insert(iterator __position, size_type __n, const value_type& __x)
      {
	list __tmp(__n, __x, get_allocator());
	splice(__position, __tmp);
      }

      /**
       *  @brief  Inserts a range into the %list.
       *  @param  __position  An iterator into the %list.
       *  @param  __first  An input iterator.
       *  @param  __last   An input iterator.
       *
       *  This function will insert copies of the data in the range [@a
       *  first,@a last) into the %list before the location specified by
       *  @a position.
       *
       *  This operation is linear in the number of elements inserted and
       *  does not invalidate iterators and references.
       */
      template<typename _InputIterator>
	void
	insert(iterator __position, _InputIterator __first,
	       _InputIterator __last)
	{
	  list __tmp(__first, __last, get_allocator());
	  splice(__position, __tmp);
	}

      /**
       *  @brief  Remove element at given position.
       *  @param  __position  Iterator pointing to element to be erased.
       *  @return  An iterator pointing to the next element (or end()).
       *
       *  This function will erase the element at the given position and thus
       *  shorten the %list by one.
       *
       *  Due to the nature of a %list this operation can be done in
       *  constant time, and only invalidates iterators/references to
       *  the element being removed.  The user is also cautioned that
       *  this function only erases the element, and that if the element
       *  is itself a pointer, the pointed-to memory is not touched in
       *  any way.  Managing the pointer is the user's responsibility.
       */
      iterator
      erase(iterator __position);

      /**
       *  @brief  Remove a range of elements.
       *  @param  __first  Iterator pointing to the first element to be erased.
       *  @param  __last  Iterator pointing to one past the last element to be
       *                erased.
       *  @return  An iterator pointing to the element pointed to by @a last
       *           prior to erasing (or end()).
       *
       *  This function will erase the elements in the range @a
       *  [first,last) and shorten the %list accordingly.
       *
       *  This operation is linear time in the size of the range and only
       *  invalidates iterators/references to the element being removed.
       *  The user is also cautioned that this function only erases the
       *  elements, and that if the elements themselves are pointers, the
       *  pointed-to memory is not touched in any way.  Managing the pointer
       *  is the user's responsibility.
       */
      iterator
      erase(iterator __first, iterator __last)
      {
	while (__first != __last)
	  __first = erase(__first);
	return __last._M_const_cast();
      }

      /**
       *  @brief  Swaps data with another %list.
       *  @param  __x  A %list of the same element and allocator types.
       *
       *  This exchanges the elements between two lists in constant
       *  time.  Note that the global std::swap() function is
       *  specialized such that std::swap(l1,l2) will feed to this
       *  function.
       *
       *  Whether the allocators are swapped depends on the allocator traits.
       */
      void
      swap(list& __x) _GLIBCXX_NOEXCEPT
      {
	__detail::_List_node_base::swap(this->_M_impl._M_node,
					__x._M_impl._M_node);

	size_t __xsize = __x._M_get_size();
	__x._M_set_size(this->_M_get_size());
	this->_M_set_size(__xsize);

	_Node_alloc_traits::_S_on_swap(this->_M_get_Node_allocator(),
				       __x._M_get_Node_allocator());
      }

      /**
       *  Erases all the elements.  Note that this function only erases
       *  the elements, and that if the elements themselves are
       *  pointers, the pointed-to memory is not touched in any way.
       *  Managing the pointer is the user's responsibility.
       */
      void
      clear() _GLIBCXX_NOEXCEPT
      {
	_Base::_M_clear();
	_Base::_M_init();
      }

      // [23.2.2.4] list operations
      /**
       *  @brief  Insert contents of another %list.
       *  @param  __position  Iterator referencing the element to insert before.
       *  @param  __x  Source list.
       *
       *  The elements of @a __x are inserted in constant time in front of
       *  the element referenced by @a __position.  @a __x becomes an empty
       *  list.
       *
       *  Requires this != @a __x.
       */
      void
      splice(iterator __position, list& __x)
      {
	if (!__x.empty())
	  {
	    _M_check_equal_allocators(__x);

	    this->_M_transfer(__position._M_const_cast(),
			      __x.begin(), __x.end());

	    this->_M_inc_size(__x._M_get_size());
	    __x._M_set_size(0);
	  }
      }

      /**
       *  @brief  Insert element from another %list.
       *  @param  __position  Iterator referencing the element to insert before.
       *  @param  __x  Source list.
       *  @param  __i  Iterator referencing the element to move.
       *
       *  Removes the element in list @a __x referenced by @a __i and
       *  inserts it into the current list before @a __position.
       */
      void
      splice(iterator __position, list& __x, iterator __i)
      {
	iterator __j = __i._M_const_cast();
	++__j;
	if (__position == __i || __position == __j)
	  return;

	if (this != std::__addressof(__x))
	  _M_check_equal_allocators(__x);

	this->_M_transfer(__position._M_const_cast(),
			  __i._M_const_cast(), __j);

	this->_M_inc_size(1);
	__x._M_dec_size(1);
      }

      /**
       *  @brief  Insert range from another %list.
       *  @param  __position  Iterator referencing the element to insert before.
       *  @param  __x  Source list.
       *  @param  __first  Iterator referencing the start of range in x.
       *  @param  __last  Iterator referencing the end of range in x.
       *
       *  Removes elements in the range [__first,__last) and inserts them
       *  before @a __position in constant time.
       *
       *  Undefined if @a __position is in [__first,__last).
       */
      void
      splice(iterator __position, list& __x, iterator __first,
	     iterator __last)
      {
	if (__first != __last)
	  {
	    if (this != std::__addressof(__x))
	      _M_check_equal_allocators(__x);

	    size_t __n = _S_distance(__first, __last);
	    this->_M_inc_size(__n);
	    __x._M_dec_size(__n);

	    this->_M_transfer(__position._M_const_cast(),
			      __first._M_const_cast(),
			      __last._M_const_cast());
	  }
      }


    private:
      typedef void __remove_return_type;
# define _GLIBCXX_LIST_REMOVE_RETURN_TYPE_TAG
    public:

      /**
       *  @brief  Remove all elements equal to value.
       *  @param  __value  The value to remove.
       *
       *  Removes every element in the list equal to @a value.
       *  Remaining elements stay in list order.  Note that this
       *  function only erases the elements, and that if the elements
       *  themselves are pointers, the pointed-to memory is not
       *  touched in any way.  Managing the pointer is the user's
       *  responsibility.
       */
      _GLIBCXX_LIST_REMOVE_RETURN_TYPE_TAG
      __remove_return_type
      remove(const _Tp& __value);

      /**
       *  @brief  Remove all elements satisfying a predicate.
       *  @tparam  _Predicate  Unary predicate function or object.
       *
       *  Removes every element in the list for which the predicate
       *  returns true.  Remaining elements stay in list order.  Note
       *  that this function only erases the elements, and that if the
       *  elements themselves are pointers, the pointed-to memory is
       *  not touched in any way.  Managing the pointer is the user's
       *  responsibility.
       */
      template<typename _Predicate>
	__remove_return_type
	remove_if(_Predicate);

      /**
       *  @brief  Remove consecutive duplicate elements.
       *
       *  For each consecutive set of elements with the same value,
       *  remove all but the first one.  Remaining elements stay in
       *  list order.  Note that this function only erases the
       *  elements, and that if the elements themselves are pointers,
       *  the pointed-to memory is not touched in any way.  Managing
       *  the pointer is the user's responsibility.
       */
      _GLIBCXX_LIST_REMOVE_RETURN_TYPE_TAG
      __remove_return_type
      unique();

      /**
       *  @brief  Remove consecutive elements satisfying a predicate.
       *  @tparam _BinaryPredicate  Binary predicate function or object.
       *
       *  For each consecutive set of elements [first,last) that
       *  satisfy predicate(first,i) where i is an iterator in
       *  [first,last), remove all but the first one.  Remaining
       *  elements stay in list order.  Note that this function only
       *  erases the elements, and that if the elements themselves are
       *  pointers, the pointed-to memory is not touched in any way.
       *  Managing the pointer is the user's responsibility.
       */
      template<typename _BinaryPredicate>
	__remove_return_type
	unique(_BinaryPredicate);

#undef _GLIBCXX_LIST_REMOVE_RETURN_TYPE_TAG

      /**
       *  @brief  Merge sorted lists.
       *  @param  __x  Sorted list to merge.
       *
       *  Assumes that both @a __x and this list are sorted according to
       *  operator<().  Merges elements of @a __x into this list in
       *  sorted order, leaving @a __x empty when complete.  Elements in
       *  this list precede elements in @a __x that are equal.
       */
      void
      merge(list& __x);

      /**
       *  @brief  Merge sorted lists according to comparison function.
       *  @tparam _StrictWeakOrdering Comparison function defining
       *  sort order.
       *  @param  __x  Sorted list to merge.
       *  @param  __comp  Comparison functor.
       *
       *  Assumes that both @a __x and this list are sorted according to
       *  StrictWeakOrdering.  Merges elements of @a __x into this list
       *  in sorted order, leaving @a __x empty when complete.  Elements
       *  in this list precede elements in @a __x that are equivalent
       *  according to StrictWeakOrdering().
       */
      template<typename _StrictWeakOrdering>
	void
	merge(list& __x, _StrictWeakOrdering __comp);

      /**
       *  @brief  Reverse the elements in list.
       *
       *  Reverse the order of elements in the list in linear time.
       */
      void
      reverse() _GLIBCXX_NOEXCEPT
      { this->_M_impl._M_node._M_reverse(); }

      /**
       *  @brief  Sort the elements.
       *
       *  Sorts the elements of this list in NlogN time.  Equivalent
       *  elements remain in list order.
       */
      void
      sort();

      /**
       *  @brief  Sort the elements according to comparison function.
       *
       *  Sorts the elements of this list in NlogN time.  Equivalent
       *  elements remain in list order.
       */
      template<typename _StrictWeakOrdering>
	void
	sort(_StrictWeakOrdering);

    protected:
      // Internal constructor functions follow.

      // Called by the range constructor to implement [23.1.1]/9

      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 438. Ambiguity in the "do the right thing" clause
      template<typename _Integer>
	void
	_M_initialize_dispatch(_Integer __n, _Integer __x, __true_type)
	{ _M_fill_initialize(static_cast<size_type>(__n), __x); }

      // Called by the range constructor to implement [23.1.1]/9
      template<typename _InputIterator>
	void
	_M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
			       __false_type)
	{
	  for (; __first != __last; ++__first)
	    push_back(*__first);
	}

      // Called by list(n,v,a), and the range constructor when it turns out
      // to be the same thing.
      void
      _M_fill_initialize(size_type __n, const value_type& __x)
      {
	for (; __n; --__n)
	  push_back(__x);
      }

      // Internal assign functions follow.

      // Called by the range assign to implement [23.1.1]/9

      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 438. Ambiguity in the "do the right thing" clause
      template<typename _Integer>
	void
	_M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
	{ _M_fill_assign(__n, __val); }

      // Called by the range assign to implement [23.1.1]/9
      template<typename _InputIterator>
	void
	_M_assign_dispatch(_InputIterator __first, _InputIterator __last,
			   __false_type);

      // Called by assign(n,t), and the range assign when it turns out
      // to be the same thing.
      void
      _M_fill_assign(size_type __n, const value_type& __val);


      // Moves the elements from [first,last) before position.
      void
      _M_transfer(iterator __position, iterator __first, iterator __last)
      { __position._M_node->_M_transfer(__first._M_node, __last._M_node); }

      // Inserts new element at position given and with value given.
      void
      _M_insert(iterator __position, const value_type& __x)
      {
	_Node* __tmp = _M_create_node(__x);
	__tmp->_M_hook(__position._M_node);
	this->_M_inc_size(1);
      }

      // Erases element at position given.
      void
      _M_erase(iterator __position) _GLIBCXX_NOEXCEPT
      {
	this->_M_dec_size(1);
	__position._M_node->_M_unhook();
	_Node* __n = static_cast<_Node*>(__position._M_node);
	_Tp_alloc_type(_M_get_Node_allocator()).destroy(__n->_M_valptr());

	_M_put_node(__n);
      }

      // To implement the splice (and merge) bits of N1599.
      void
      _M_check_equal_allocators(list& __x) _GLIBCXX_NOEXCEPT
      {
	if (std::__alloc_neq<typename _Base::_Node_alloc_type>::
	    _S_do_it(_M_get_Node_allocator(), __x._M_get_Node_allocator()))
	  __builtin_abort();
      }

      // Used to implement resize.
      const_iterator
      _M_resize_pos(size_type& __new_size) const;

    };

#if __cpp_deduction_guides >= 201606
  template<typename _InputIterator, typename _ValT
	     = typename iterator_traits<_InputIterator>::value_type,
	   typename _Allocator = allocator<_ValT>,
	   typename = _RequireInputIter<_InputIterator>,
	   typename = _RequireAllocator<_Allocator>>
    list(_InputIterator, _InputIterator, _Allocator = _Allocator())
      -> list<_ValT, _Allocator>;
#endif

_GLIBCXX_END_NAMESPACE_CXX11

  /**
   *  @brief  List equality comparison.
   *  @param  __x  A %list.
   *  @param  __y  A %list of the same type as @a __x.
   *  @return  True iff the size and elements of the lists are equal.
   *
   *  This is an equivalence relation.  It is linear in the size of
   *  the lists.  Lists are considered equivalent if their sizes are
   *  equal, and if corresponding elements compare equal.
  */
  template<typename _Tp, typename _Alloc>
    inline bool
    operator==(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    {
#if _GLIBCXX_USE_CXX11_ABI
      if (__x.size() != __y.size())
	return false;
#endif

      typedef typename list<_Tp, _Alloc>::const_iterator const_iterator;
      const_iterator __end1 = __x.end();
      const_iterator __end2 = __y.end();

      const_iterator __i1 = __x.begin();
      const_iterator __i2 = __y.begin();
      while (__i1 != __end1 && __i2 != __end2 && *__i1 == *__i2)
	{
	  ++__i1;
	  ++__i2;
	}
      return __i1 == __end1 && __i2 == __end2;
    }

#if __cpp_lib_three_way_comparison
/**
   *  @brief  List ordering relation.
   *  @param  __x  A `list`.
   *  @param  __y  A `list` of the same type as `__x`.
   *  @return  A value indicating whether `__x` is less than, equal to,
   *           greater than, or incomparable with `__y`.
   *
   *  See `std::lexicographical_compare_three_way()` for how the determination
   *  is made. This operator is used to synthesize relational operators like
   *  `<` and `>=` etc.
  */
  template<typename _Tp, typename _Alloc>
    inline __detail::__synth3way_t<_Tp>
    operator<=>(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    {
      return std::lexicographical_compare_three_way(__x.begin(), __x.end(),
						    __y.begin(), __y.end(),
						    __detail::__synth3way);
    }
#else
  /**
   *  @brief  List ordering relation.
   *  @param  __x  A %list.
   *  @param  __y  A %list of the same type as @a __x.
   *  @return  True iff @a __x is lexicographically less than @a __y.
   *
   *  This is a total ordering relation.  It is linear in the size of the
   *  lists.  The elements must be comparable with @c <.
   *
   *  See std::lexicographical_compare() for how the determination is made.
  */
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return std::lexicographical_compare(__x.begin(), __x.end(),
					  __y.begin(), __y.end()); }

  /// Based on operator==
  template<typename _Tp, typename _Alloc>
    inline bool
    operator!=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return !(__x == __y); }

  /// Based on operator<
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return __y < __x; }

  /// Based on operator<
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return !(__y < __x); }

  /// Based on operator<
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return !(__x < __y); }
#endif // three-way comparison

  /// See std::list::swap().
  template<typename _Tp, typename _Alloc>
    inline void
    swap(list<_Tp, _Alloc>& __x, list<_Tp, _Alloc>& __y)
    _GLIBCXX_NOEXCEPT_IF(noexcept(__x.swap(__y)))
    { __x.swap(__y); }

_GLIBCXX_END_NAMESPACE_CONTAINER

#if _GLIBCXX_USE_CXX11_ABI

  // Detect when distance is used to compute the size of the whole list.
  template<typename _Tp>
    inline ptrdiff_t
    __distance(_GLIBCXX_STD_C::_List_iterator<_Tp> __first,
	       _GLIBCXX_STD_C::_List_iterator<_Tp> __last,
	       input_iterator_tag __tag)
    {
      typedef _GLIBCXX_STD_C::_List_const_iterator<_Tp> _CIter;
      return std::__distance(_CIter(__first), _CIter(__last), __tag);
    }

  template<typename _Tp>
    inline ptrdiff_t
    __distance(_GLIBCXX_STD_C::_List_const_iterator<_Tp> __first,
	       _GLIBCXX_STD_C::_List_const_iterator<_Tp> __last,
	       input_iterator_tag)
    {
      typedef __detail::_List_node_header _Sentinel;
      _GLIBCXX_STD_C::_List_const_iterator<_Tp> __beyond = __last;
      ++__beyond;
      const bool __whole = __first == __beyond;
      if (__builtin_constant_p (__whole) && __whole)
	return static_cast<const _Sentinel*>(__last._M_node)->_M_size;

      ptrdiff_t __n = 0;
      while (__first != __last)
	{
	  ++__first;
	  ++__n;
	}
      return __n;
    }
#endif

} // namespace ft

#endif // SHARED_UTILS_HPP
