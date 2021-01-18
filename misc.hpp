#ifndef MISC_HPP
# define MISC_HPP

namespace ft
{
	// nullptr is the pointer literal, its prvalue is ft::nullptr_t.
	// see : https://stackoverflow.com/questions/61283569/how-does-c-nullptr-implementation-work

	static class nullptr_t
	{
		public:
			template <class T>
			operator T* () const { return 0; }

			template <class T, class U>
			operator T U::* () const { return 0; }

		private:
			void operator&() const; // nullptr has no address.
	}				nullptr_98 = {};
}; // namespace ft

#endif // MISC_HPP
