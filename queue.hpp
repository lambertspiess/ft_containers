#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <iostream>
# include <string>
# include "list.hpp"

namespace ft
{
	template <typename T, typename Sequence = ft::list<T> >
	class queue
	{
		private:
			typedef Sequence						Seq;
			Sequence										base;

		public:
			explicit queue(const Sequence & seq = Sequence())
			: base(seq)
			{}

			queue(queue const & other)
			: base(other.base)
			{}

			queue & operator=(const queue & other)
			{
				if (*this == other) { return (*this); }
				this->base = other.base; return (*this);
			}

			~queue() {}

			// friend keywords are needed to access the operators belonging to base
			friend bool operator==(const queue<T, Seq> & lhs, const queue<T, Seq> & rhs)
				{ return (lhs.base == rhs.base); }

			friend bool operator!=(const queue<T, Seq> & lhs, const queue<T, Seq> & rhs)
				{ return (lhs.base != rhs.base); }

			friend bool operator<(const queue<T, Seq> & lhs, const queue<T, Seq> & rhs)
				{	return (lhs.base < rhs.base);	}

			friend bool operator>(const queue<T, Seq> & lhs, const queue<T, Seq> & rhs)
				{ return (lhs.base > rhs.base); }

			friend bool operator<=(const queue<T, Seq> & lhs, const queue<T, Seq> & rhs)
				{ return (lhs.base <= rhs.base); }

			friend bool operator>=(const queue<T, Seq> & lhs, const queue<T, Seq> & rhs)
				{ return (lhs.base >= rhs.base); }

			bool empty() const { return (base.empty()); }

			typename Sequence::size_type size() const { return (base.size()); }

			T & front() { return (base.front()); }
			const T & front() const { return (base.front()); }

			T & back() { return (base.back()); }
			const T & back() const { return (base.back()); }

			void push(const T & val) { base.push_back(val); }
			void pop() { base.pop_front(); }

	}; // class queue
}; // namespace ft

#endif // QUEUE_HPP
