#ifndef MY_NULLPTR
# define MY_NULLPTR

// source : https://stackoverflow.com/questions/13675203/implementation-safe-nullptr
const class my_nullptr_t
{
	public:
		// Return 0 for any class pointer
		template <typename T>
		operator T*() const { return (0); }

		// Return 0 for any member pointer
		template <typename T, typename U>
		operator T U::*() const { return (0); }

		// Safe boolean conversion
		operator void*() const { return (0); }
} my_nullptr = {};

#endif // MY_NULLPTR
