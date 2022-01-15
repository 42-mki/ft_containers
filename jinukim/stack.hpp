#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template<typename T, typename Cont = vector<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Cont container_type;
		typedef typename container_type::size_type size_type;

		template <typename TT, typename CC>
		friend bool operator==(const stack<TT, CC>& l, const stack<TT, CC>& r);
		template <typename TT, typename CC>
		friend bool operator<(const stack<TT, CC>& l, const stack<TT, CC>& r);

		stack(const container_type& ctnr = container_type()) : c(ctnr) {}
		bool empty() const
		{
			return c.empty();
		}
		size_type size() const
		{
			return c.size();
		}
		value_type& top()
		{
			return c.back();
		}
		const value_type& top() const
		{
			return c.back();
		}
		void push(const value_type& val)
		{
			c.push_back(val);
		}
		void pop()
		{
			c.pop_back();
		}
	protected:
		container_type c;
	};

	template <typename T, typename Cont>
	bool operator==(const stack<T, Cont>& l, const stack<T, Cont>& r)
	{
		return l.c == r.c;
	}
	template <typename T, typename Cont>
	bool operator!=(const stack<T, Cont>& l, const stack<T, Cont>& r)
	{
		return !(l == r);
	}
	template <typename T, typename Cont>
	bool operator<(const stack<T, Cont>& l, const stack<T, Cont>& r)
	{
		return l.c < r.c;
	}
	template <typename T, typename Cont>
	bool operator>(const stack<T, Cont>& l, const stack<T, Cont>& r)
	{
		return r < l;
	}
	template <typename T, typename Cont>
	bool operator<=(const stack<T, Cont>& l, const stack<T, Cont>& r)
	{
		return !(r < l);
	}
	template <typename T, typename Cont>
	bool operator>=(const stack<T, Cont>& l, const stack<T, Cont>& r)
	{
		return !(l < r);
	}
	template <typename T, typename Cont>
	void swap(stack<T, Cont>& x, stack<T, Cont>& y)
	{
		x.swap(y);
	}
};

#endif