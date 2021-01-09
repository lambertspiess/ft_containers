#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	/*
	 * reverse_iterator :
	 * bidirectional and random access iterators have corresponding reverse
	 * iterator adaptors that iterate through the data structure in the
	 * opposite direction. They have the same signatures as the corresponding
	 * iterators.
	 */
	template<typename Iterator>
	class reverse_iterator
	: public iterator<typename iterator_traits<_Iterator>::iterator_category,
						typename iterator_traits<_Iterator>::value_type,
						typename iterator_traits<_Iterator>::difference_type,
						typename iterator_traits<_Iterator>::pointer,
						typename iterator_traits<_Iterator>::reference>
	{
		protected:
			_Iterator_current;
		public:
			typedef _Iterator								iterator_type;
			typedef typename iterator_traits<_Iterator>::difference_type
															difference_type;
			typedef typename iterator_traits<_Iterator>::reference	reference;
			typedef typename iterator_traits<_Iterator>::pointer	pointer;
		public:
		
	}
}

#endif
