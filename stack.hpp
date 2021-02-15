#ifndef STACK_HPP
# define STACK_HPP

# include "list.hpp"

namespace ft
{
	template <typename T, typename Sequence = ft::list<T> >
	class stack
	{
		public:
			typedef Sequence								Seq;
		private:
			Sequence										base;
		public:
			stack(const Sequence & seq = Sequence())
			: base(seq)
			{}

			stack(const stack & other)
			: base(other.seq)
			{}

			stack & operator=(const stack & other)
			{
				if (*this == other) { return (*this); }
				this->base = other.base; return (*this);
			}

			// friend keywords are needed to access the operators belonging to base
			friend bool operator==(const stack<T, Seq> & lhs, const stack<T, Seq> & rhs)
				{ return (lhs.base == rhs.base); }

			friend bool operator!=(const stack<T, Seq> & lhs, const stack<T, Seq> & rhs)
				{ return (lhs.base != rhs.base); }

			friend bool operator<(const stack<T, Seq> & lhs, const stack<T, Seq> & rhs)
				{	return (lhs.base < rhs.base);	}

			friend bool operator>(const stack<T, Seq> & lhs, const stack<T, Seq> & rhs)
				{ return (lhs.base > rhs.base); }

			friend bool operator<=(const stack<T, Seq> & lhs, const stack<T, Seq> & rhs)
				{ return (lhs.base <= rhs.base); }

			friend bool operator>=(const stack<T, Seq> & lhs, const stack<T, Seq> & rhs)
				{ return (lhs.base >= rhs.base); }

			~stack()
			{}

			bool empty() const { return (base.empty()); }

			typename Sequence::size_type size() const { return (base.size()); }

			T & top() { return (base.back()); }
			const T & top() const { return (base.back()); }

			void push(const T & val) { base.push_back(val); }

			void pop() { base.pop_back(); }
	}; // class stack
}

#endif // STACK_HPP
