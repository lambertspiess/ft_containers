#ifndef ITERATORS_HPP
# define ITERATORS_HPP

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
	typename ft::iterator_traits<RandomAccessIterator>::difference_type
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

 // ============= BITS STL ITERATOR =============

	/*
	 * Bidirectional and random access iterators have corresponding reverse
	 * iterator adaptors that iterate through the data structure in the
	 * opposite direction.
	 * They have the same signatures as the corresponding iterators.
	 * The fundamental relation between a reverse iterator and its
	 * corresponding iterator is established by the identity:
	 *            &*(reverse_iterator(i)) == &*(i - 1)
	 *                                                                          
	 * This mapping is dictated by the fact that while there is always a
	 * pointer past the end of an array, there might not be a valid pointer
	 * before the beginning of an array.
	 */

	template<typename Iterator>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
		template<typename Iter>
		friend class reverse_iterator;
		protected:
			Iterator										current;
			typedef iterator_traits<Iterator>				traits_type;
		public:
			typedef Iterator								iterator_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;

			// ctor : Iterators of pointer type shall be zeroed
			reverse_iterator() : current() {};
			// no implicit conversions
			explicit reverse_iterator(iterator_type x) : current(x) {};

			reverse_iterator(const reverse_iterator & x) : current(x.current) {};

			virtual ~reverse_iterator() {}; // dtor

			// ctor for when  the underlying iterator of another type
			// is convertible to the type of @c current :
			template<typename Iter>
			reverse_iterator(const reverse_iterator<Iter> & x)
			: current(x.current) {}

			// @return the underlying iterator @c current
			iterator_type base() const { return current; };

			// returns a reference to the value stored at @ --current
			reference operator*() const
				{ Iterator tmp = current; return (*--tmp); }

			// return a pointer to the elem stored at @ current - 1
			pointer operator->() const
				{ Iterator tmp = current; --tmp; return S_to_pointer(tmp); }

			// prefix : decrement the underlying iterator and return @c *this
			reverse_iterator operator++() { --current; return (*this); }

			// postfix : decrement the underlying iterator but return the
			// original value of @c *this
			reverse_iterator operator++(int)
				{ reverse_iterator tmp = *this; --current; return tmp; }

			// prefix : increment the underlying iterator and return @c *this
			reverse_iterator & operator--() { ++current; return (*this); }

			// postfix : increment the underlying iterator but return the
			// original value of @c *this
			reverse_iterator operator--(int)
				{ reverse_iterator tmp = (*this); ++current; return tmp; }

			// if @current is a random access iterator,
			// return a reference to @c current - @a n
			reverse_iterator operator+(difference_type n) const
				{ return reverse_iterator(current - n); }

			// if @current is a random access iterator,
			// move it backwards @a n steps
			reverse_iterator & operator+=(difference_type n)
				{ current -= n; return *this; }

			// if @current is a random access iterator,
			// return a reference to @c current - @a n
			reverse_iterator operator-(difference_type n) const
				{ return reverse_iterator(current + n); }

			// if @current is a random access iterator,
			// move it forward @a n steps
			reverse_iterator & operator-=(difference_type n)
				{ current += n; return *this; }

			// if @current is a random access iterator,
			// return the value held at : @c current - @a n - 1
			reference operator[](difference_type n) const
				{ return *(*this + n); }

		private:
			// S_to_pointer : syntactic sugar to get a pointer to an elem
			// pointed-to by an iterator
			template<typename Tp>
			static Tp * S_to_pointer(Tp *p) { return p; }
			template<typename Tp>
			static pointer S_to_pointer(Tp t) { return t.operator->(); }
    }; // class reverse_iterator

	// COMPARISON operators
	// between the underlying iterators of two reverse_iterator
	template<typename Iterator>
	inline bool operator==(const reverse_iterator<Iterator> & x,
							const reverse_iterator<Iterator> & y)
	{ return x.base() == y.base(); }

	template<typename Iterator>
	inline bool operator<(const reverse_iterator<Iterator> & x,
							const reverse_iterator<Iterator> & y)
	{ return y.base() < x.base(); }

	template<typename Iterator>
	inline bool operator!=(const reverse_iterator<Iterator> & x,
							const reverse_iterator<Iterator> & y)
	{ return !(x == y); }

	template<typename Iterator>
	inline bool operator>(const reverse_iterator<Iterator> & x,
							const reverse_iterator<Iterator> & y)
	{ return y < x; }

	template<typename Iterator>
	inline bool operator<=(const reverse_iterator<Iterator> & x,
							const reverse_iterator<Iterator> & y)
	{ return !(y < x); }

	template<typename Iterator>
	inline bool operator>=(const reverse_iterator<Iterator> & x,
							const reverse_iterator<Iterator> & y)
	{ return !(x < y); }

	// same but comparing reverse_iterator to const reverse_iterator
	template<typename IteratorL, typename IteratorR>
	inline bool operator==(const reverse_iterator<IteratorL> & x,
							const reverse_iterator<IteratorR> & y)
	{ return x.base() == y.base(); }

	template<typename IteratorL, typename IteratorR>
	inline bool operator<(const reverse_iterator<IteratorL> & x,
							const reverse_iterator<IteratorR> & y)
	{ return x.base() > y.base(); }

	template<typename IteratorL, typename IteratorR>
	inline bool operator!=(const reverse_iterator<IteratorL> & x,
							const reverse_iterator<IteratorR> & y)
	{ return x.base() != y.base(); }

	template<typename IteratorL, typename IteratorR>
	inline bool operator>(const reverse_iterator<IteratorL> & x,
							const reverse_iterator<IteratorR> & y)
	{ return x.base() < y.base(); }

	template<typename IteratorL, typename IteratorR>
	inline bool operator<=(const reverse_iterator<IteratorL> & x,
							const reverse_iterator<IteratorR> & y)
	{ return x.base() >= y.base(); }

	template<typename IteratorL, typename IteratorR>
	inline bool operator>=(const reverse_iterator<IteratorL> & x,
							const reverse_iterator<IteratorR> & y)
	{ return x.base() <= y.base(); }

	// distance between two reverse_iterator
	template<typename Iterator>
	inline typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& x,
				const reverse_iterator<Iterator>& y)
	{ return y.base() - x.base(); }

	// same but between a reverse_iterator and a const reverse_iterator
	template<typename IteratorL, typename IteratorR>
	inline typename reverse_iterator<IteratorL>::difference_type
	operator-(const reverse_iterator<IteratorL>& x,
				const reverse_iterator<IteratorR>& y)
	{ return y.base() - x.base(); }

	// return a reverse_iterator pointing to @c x + n (decremented n steps)
	template<typename Iterator>
	inline reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& x)
	{ return reverse_iterator<Iterator>(x.base() - n); }

} // namespace ft

#endif // ITERATORS_HPP
