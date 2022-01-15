#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	struct bool_type {};
	struct true_type { static const bool value = true; };
	struct false_type { static const bool value = false; };

	template <typename L, typename R>
	struct is_same : public false_type {};
	template <typename T>
	struct is_same<T, T> : public true_type {};

	template <bool, typename T = void>
	struct enable_if {};
	template <typename T>
	struct enable_if<true, T> { typedef T type;};	

	template <typename Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	template <typename T>
	class iterator_traits<T*>
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
	};
	template <typename T>
	class iterator_traits<const T*>
	{
	public:
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
	};
};

#endif
