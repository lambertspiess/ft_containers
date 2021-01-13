#ifndef SHARED_UTILS_HPP
# define SHARED_UTILS_HPP

namespace ft {

 // ============= BITS STL ITERATOR BASE TYPES =============
  //  Marking input iterators.
  struct input_iterator_tag { };
  //  Marking output iterators.
  struct output_iterator_tag { };
  // Forward iterators support a superset of input iterator operations.
  struct forward_iterator_tag : public input_iterator_tag { };
  // Bidirectional iterators support a superset of forward iterator operations.
  struct bidirectional_iterator_tag : public forward_iterator_tag { };
  // Random-access iterators support a superset of bidirectional
  // iterator operations.
  struct random_access_iterator_tag : public bidirectional_iterator_tag { };

  /*
   * Common iterator class.
   * This class does nothing but define nested typedefs. Iterator classes
   * can inherit from this class to save some work. The typedefs are then
   * used in specializations and overloading.
   */
  template<typename Category, typename Tp, typename Distance = ptrdiff_t,
           typename Pointer = Tp*, typename Reference = Tp&>
    struct iterator
    {
      // One of the @link iterator_tags tag types@endlink.
      typedef Category  iterator_category;
      // The type "pointed to" by the iterator.
      typedef Tp        value_type;
      // Distance between iterators is represented as this type.
      typedef Distance  difference_type;
      // This type represents a pointer-to-value_type.
      typedef Pointer   pointer;
      // This type represents a reference-to-value_type.
      typedef Reference reference;
    };

  /*
   * Traits class for iterators.
   * This class does nothing but define nested typedefs.  The general
   * version simply forwards the nested typedefs from the Iterator
   * argument. Specialized versions for pointers and pointers-to-const
   * provide tighter, more correct semantics.
   */
  template<typename _Iterator>
    struct iterator_traits;

  template<typename Iterator>
    struct iterator_traits
    {
      typedef typename Iterator::iterator_category iterator_category;
      typedef typename Iterator::value_type        value_type;
      typedef typename Iterator::difference_type   difference_type;
      typedef typename Iterator::pointer           pointer;
      typedef typename Iterator::reference         reference;
    };

  // Partial specialization for pointer types.
  template<typename Tp>
    struct iterator_traits<Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef Tp*                        pointer;
      typedef Tp&                        reference;
    };

  // Partial specialization for const pointer types.
  template<typename Tp>
    struct iterator_traits<const Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef const Tp*                  pointer;
      typedef const Tp&                  reference;
    };

  /*
   * Syntactic sugar to check an iterator's category tag.
   * Not standard C++, for internal library use only
   */
	template<typename Iter>
	typename iterator_traits<Iter>::iterator_category
		iterator_category(const Iter &)
	{
		return typename ft::iterator_traits<Iter>::iterator_category();
	}

 // ============= BITS STL ITERATOR BASE FUNCS =============

  // Forward declaration for the overloads of distance.
  template <typename> struct List_iterator;
  template <typename> struct List_const_iterator;

	template<typename InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename ft::iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			++first;
			++n;
		}
		return (n);
	}

	template<typename RandomAccessIterator>
	typename ft::iterator_traits<_RandomAccessIterator>::difference_type
		distance(RandomAccessIterator first, RandomAccessIterator last,
					random_access_iterator_tag)
	{
		return last - first;
	}

	template<typename InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last)
	{
		return ft::distance(first, last, ft::iterator_category(first));
	}

  template<typename InputIterator, typename Distance>
    void advance(InputIterator& i, _Distance __n, input_iterator_tag)
    {
      // concept requirements
      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
      __glibcxx_assert(__n >= 0);
      while (__n--)
	++__i;
    }

  template<typename _BidirectionalIterator, typename _Distance>
    inline _GLIBCXX14_CONSTEXPR void
    __advance(_BidirectionalIterator& __i, _Distance __n,
	      bidirectional_iterator_tag)
    {
      // concept requirements
      __glibcxx_function_requires(_BidirectionalIteratorConcept<
				  _BidirectionalIterator>)
      if (__n > 0)
        while (__n--)
	  ++__i;
      else
        while (__n++)
	  --__i;
    }

  template<typename _RandomAccessIterator, typename _Distance>
    inline _GLIBCXX14_CONSTEXPR void
    __advance(_RandomAccessIterator& __i, _Distance __n,
              random_access_iterator_tag)
    {
      // concept requirements
      __glibcxx_function_requires(_RandomAccessIteratorConcept<
				  _RandomAccessIterator>)
      if (__builtin_constant_p(__n) && __n == 1)
	++__i;
      else if (__builtin_constant_p(__n) && __n == -1)
	--__i;
      else
	__i += __n;
    }

  /**
   *  @brief A generalization of pointer arithmetic.
   *  @param  __i  An input iterator.
   *  @param  __n  The @a delta by which to change @p __i.
   *  @return  Nothing.
   *
   *  This increments @p i by @p n.  For bidirectional and random access
   *  iterators, @p __n may be negative, in which case @p __i is decremented.
   *
   *  For random access iterators, this uses their @c + and @c - operations
   *  and are constant time.  For other %iterator classes they are linear time.
  */
  template<typename _InputIterator, typename _Distance>
    inline _GLIBCXX17_CONSTEXPR void
    advance(_InputIterator& __i, _Distance __n)
    {
      // concept requirements -- taken care of in __advance
      typename iterator_traits<_InputIterator>::difference_type __d = __n;
      std::__advance(__i, __d, std::__iterator_category(__i));
    }

}

#endif // SHARED_UTILS_HPP
