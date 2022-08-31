#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "pair.hpp"
# include "rb_tree.hpp"
# include "iterator.hpp"

namespace ft
{
	template <typename T, class Compare = std::less<T>, typename Alloc = std::allocator<T> >
	class set
	{
	public:
		typedef T key_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef rb_tree<key_type, value_type, Itself<value_type>, key_compare, allocator_type> tree;
		typedef typename tree::const_iterator iterator;
		typedef typename tree::const_iterator const_iterator;
		typedef typename tree::const_reverse_iterator reverse_iterator;
		typedef typename tree::const_reverse_iterator const_reverse_iterator;
		typedef typename tree::difference_type difference_type;
		typedef typename tree::size_type size_type;

		set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _container(tree()), _comp(comp), _alloc(alloc) {}
		template <typename Iter>
		set(typename ft::enable_if<!ft::is_same<typename Iter::iterator_category, void>::value, Iter>::type first,
				Iter last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _container(tree()), _comp(comp), _alloc(alloc)
		{
			for (Iter cur = first; cur != last; ++cur)
				insert(*cur);
		}
		set(const set& x): _container(x._container), _comp(x._comp), _alloc(x._alloc) {}
		set& operator=(const set& x)
		{
			_container = x._container;
			_comp = x._comp;
			_alloc = x._alloc;
			return *this;
		}
		~set() {}

		//iterators
		iterator begin()
		{
			return _container.begin();
		}
		const_iterator begin() const
		{
			return _container.begin();
		}
		iterator end()
		{
			return _container.end();
		}
		const_iterator end() const
		{
			return _container.end();
		}
		reverse_iterator rbegin()
		{
			return _container.rbegin();
		}
		const_reverse_iterator rbegin() const
		{
			return _container.rbegin();
		}
		reverse_iterator rend()
		{
			return _container.rend();
		}
		const_reverse_iterator rend() const
		{
			return _container.rend();
		}

		//capacity
		bool empty() const { return _container.size() == 0; }
		size_type size() const { return _container.size(); }
		size_type max_size() const { return _container.max_size(); }

		//modifiers
		pair<iterator, bool> insert(const value_type& val)
		{
			return _container.insert(val);
		}
		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			return insert(val).first;
		}
		template <class Iter>
		void insert(typename ft::enable_if<!ft::is_same<typename Iter::iterator_category, void>::value, Iter>::type first, Iter last)
		{
			for (; first != last; ++first)
				insert(*first);
		}
		void erase(const_iterator position)
		{
			_container.erase(position);
		}
		size_type erase(const value_type& k)
		{
			return _container.erase(k);
		}
		void erase(iterator first, iterator last)
		{
			_container.erase(first, last);
		}
		void swap(set& x)
		{
			_container.swap(x._container);
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
		}
		void clear()
		{
			_container.clear();
		}

		//observers
		key_compare key_comp() const
		{
			return _comp;
		}
		value_compare value_comp() const
		{
			return value_compare(_comp);
		}

		//operations
		iterator find(const key_type& k)
		{
			return _container.find(k);
		}
		const_iterator find(const key_type& k) const
		{
			return _container.find(k);
		}
		size_type count(const key_type& k) const
		{
			return _container.count(k);
		}
		iterator lower_bound(const key_type& k)
		{
			return _container.lower_bound(k);
		}
		const_iterator lower_bound(const key_type& k) const
		{
			return _container.lower_bound(k);
		}
		iterator upper_bound(const key_type& k)
		{
			return _container.upper_bound(k);
		}
		const_iterator upper_bound(const key_type& k) const
		{
			return _container.upper_bound(k);
		}
		pair<iterator, iterator> equal_range(const key_type& k)
		{
			return _container.equal_range(k);
		}
		pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return _container.equal_range(k);
		}

		//allocator
		allocator_type get_allocator() const
		{
			return _alloc;
		}
		void print()
		{
			_container.print(_container._root);
		}
	private:
		tree _container;
		key_compare _comp;
		allocator_type _alloc;
	};
	template <typename T, typename Comp, typename Alloc>
	bool operator==(const set<T, Comp, Alloc>& l, const set<T, Comp, Alloc>& r)
	{
		if (l.size() != r.size())
			return false;
		typename set<T, Comp, Alloc>::const_iterator i = l.begin(), j = r.begin();
		for (; i != l.end() && j != r.end(); ++i, ++j)
			if (*i != *j)
				break;
		return *i == *j;
	}
	template <typename T, typename Comp, typename Alloc>
	bool operator!=(const set<T, Comp, Alloc>& l, const set<T, Comp, Alloc>& r)
	{
		return !(l == r);
	}
	template <typename T, typename Comp, typename Alloc>
	bool operator<(const set<T, Comp, Alloc>& l, const set<T, Comp, Alloc>& r)
	{
		typename set<T, Comp, Alloc>::const_iterator i = l.begin(), j = r.begin();
		for (; i != l.end() && j != r.end(); ++i, ++j)
			if (*i != *j)
				break;
		return *i < *j;
	}
	template <typename T, typename Comp, typename Alloc>
	bool operator<=(const set<T, Comp, Alloc>& l, const set<T, Comp, Alloc>& r)
	{
		return !(r < l);
	}
	template <typename T, typename Comp, typename Alloc>
	bool operator>(const set<T, Comp, Alloc>& l, const set<T, Comp, Alloc>& r)
	{
		return r < l;
	}
	template <typename T, typename Comp, typename Alloc>
	bool operator>=(const set<T, Comp, Alloc>& l, const set<T, Comp, Alloc>& r)
	{
		return !(l < r);
	}
	template <typename T, typename Comp, typename Alloc>
	void swap(set<T,Comp, Alloc>& x, set<T, Comp, Alloc>& y)
	{;
		x.swap(y);
	}
};

#endif