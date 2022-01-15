#ifndef PAIR_HPP
# define PAIR_HPP

# include <memory>
# include <functional>

namespace ft
{
	template <typename T1, typename T2>
	class pair
	{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;
		pair(): first(), second() {}
		template <typename U1, typename U2>
		pair(const pair<U1, U2>& pr): first(pr.first), second(pr.second) {}
		pair(const first_type& x, const second_type& y): first(x), second(y) {}
		pair& operator=(const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}
		~pair() { }
	};
	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

	template <typename T1, typename T2>
	bool operator==(const pair<T1, T2>& l, const pair<T1, T2>& r) { return l.first == r.first && l.second == r.second ;}
	template <typename T1, typename T2>
	bool operator<(const pair<T1, T2>& l, const pair<T1, T2>& r) { return l.first < r.first || (!(r.first < l.first) && l.second < r.second);}
	template <typename T1, typename T2>
	bool operator!=(const pair<T1, T2>& l, const pair<T1, T2>& r) { return !(l == r);}
	template <typename T1, typename T2>
	bool operator>(const pair<T1, T2>& l, const pair<T1, T2>& r) { return r < l;}
	template <typename T1, typename T2>
	bool operator<=(const pair<T1, T2>& l, const pair<T1, T2>& r) { return !(r < l);}
	template <typename T1, typename T2>
	bool operator>=(const pair<T1, T2>& l, const pair<T1, T2>& r) { return !(l < r);}

	template <typename Pair>
	struct Select1st: public std::unary_function<Pair, typename Pair::first_type>
	{
	public:
		typename Pair::first_type operator()(Pair& x) const { return x.first; }
		const typename Pair::first_type operator()(const Pair& x) const { return x.first; }
	};
	template <typename T>
	struct Itself: public std::unary_function<T, T>
	{
	public:
		T operator()(T& x) const { return x; }
		const T operator()(const T& x) const { return x; }
	};
};

#endif