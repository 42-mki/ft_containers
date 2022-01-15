#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <algorithm>
# include "random_iterator.hpp"
# include "random_reverse_iterator.hpp"

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename Alloc::reference reference;
		typedef typename Alloc::const_reference const_reference;
		typedef typename Alloc::pointer pointer;
		typedef typename Alloc::const_pointer const_pointer;
		typedef random_iterator<pointer, vector> iterator;
		typedef random_iterator<const_pointer, vector> const_iterator;
		typedef random_reverse_iterator<pointer, vector> reverse_iterator;
		typedef random_reverse_iterator<const_pointer, vector> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

		vector(const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			_start = _finish = _end_storage = _alloc.allocate(0);
		}
		vector(int n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			_start = _finish = _alloc.allocate(n);
			_end_storage = _start + n;
			while (n--)
				_alloc.construct(_finish++, value_type(val));
		}
		template <typename Iter>
		vector(typename ft::enable_if<!ft::is_same<typename Iter::iterator_category, void>::value, Iter>::type first,
				Iter last, const allocator_type& alloc = allocator_type())
		{
			size_type n = count_num(first, last);
			_alloc = alloc;
			_start = _finish = _alloc.allocate(n);
			_end_storage = _start + n;
			while (n--)
				_alloc.construct(_finish++, value_type(*first++));
		}
		vector(const vector& x)
		{
			_alloc = x._alloc;
			_start = _finish = _alloc.allocate(x.capacity());
			_end_storage = _start + x.capacity();
			for (size_t i = 0; i < x.size(); ++i)
				_alloc.construct(_finish++, x[i]);
		}
		~vector()
		{
			for (pointer itr = _start; itr != _finish; ++itr)
				_alloc.destroy(itr);
			_alloc.deallocate(_start, capacity());
		}
		vector& operator=(const vector& x)
		{
			for (pointer itr = _start; itr != _finish; ++itr)
				_alloc.destroy(itr);
			_alloc.deallocate(_start, capacity());
			_alloc = x._alloc;
			_start = _finish = _alloc.allocate(x.capacity());
			_end_storage = _start + x.capacity();
			for (size_t i = 0; i < x.size(); ++i)
				_alloc.construct(_finish++, x[i]);
			return *this;
		}

		//iterators
		iterator				begin() { return iterator(_start); }
		iterator				end() { return iterator(_finish); }
		const_iterator			begin() const { return const_iterator(_start); }
		const_iterator			end() const { return const_iterator(_finish); }
		reverse_iterator		rbegin() { return reverse_iterator(_finish - 1); }
		reverse_iterator		rend() { return reverse_iterator(_start - 1); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(_finish - 1); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(_start - 1); }
		
		//capacity
		size_type size() const
		{
			return _finish - _start;
		}
		size_type max_size() const
		{
			ptrdiff_t m = 1;
			m <<= sizeof(ptrdiff_t) * 8 - 1;
			m = ~m;
			size_type diffmax = m;
			size_type allocmax = _alloc.max_size();
			return std::min(diffmax, allocmax);
		}
		void resize(size_type n, value_type val = value_type())
		{
			if (n < size())
			{
				while (size() != n)
					_alloc.destroy(--_finish);
			}
			else if (n > size())
			{
				if (n > capacity())
					reserve(n);
				while (n > size())
					_alloc.construct(_finish++, val);
			}
		}
		size_type capacity() const
		{
			return _end_storage - _start;
		}
		bool empty() const
		{
			return _start == _finish;
		}
		void reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("vector::reserve");
			if (capacity() < n && n < 2 * capacity())
				n = 2 * capacity();
			if (n > capacity())
			{
				pointer new_start, new_end;
				new_start = new_end = _alloc.allocate(n);
				for (pointer i = _start; i != _finish; ++i)
				{
					_alloc.construct(new_end++, value_type(*i));
					_alloc.destroy(i);
				}
				_alloc.deallocate(_start, capacity());
				_start = new_start;
				_finish = new_end;
				_end_storage = _start + n;
			}
		}

		//element access
		reference operator[](size_type n)
		{
			return _start[n];
		}
		const_reference operator[](size_type n) const
		{
			return _start[n];
		}
		reference at(size_type n)
		{
			if (n >= size())
				throw std::out_of_range("vector::at");
			return _start[n];
		}
		const_reference at(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("vector::at");
			return _start[n];
		}
		reference front()
		{
			return *_start;
		}
		const_reference front() const
		{
			return *_start;
		}
		reference back()
		{
			return *(_finish - 1);
		}
		const_reference back() const
		{
			return *(_finish - 1);
		}

		//modifier
		template <typename Iter>
		void assign(typename ft::enable_if<!ft::is_same<typename Iter::iterator_category, void>::value, Iter>::type first, Iter last)
		{
			size_type n = count_num(first, last);
			reserve(n);
			_finish = _start;
			while (n--)
				_alloc.construct(_finish++, value_type(*first++));
		}
		void assign(size_type n, const value_type& val)
		{
			reserve(n);
			_finish = _start;
			while (n--)
				_alloc.construct(_finish++, value_type(val));
		}
		void push_back(const value_type& val)
		{
			if (_finish == _end_storage)
				reserve(capacity() + 1);
			_alloc.construct(_finish++, value_type(val));
		}
		void pop_back()
		{
			_alloc.destroy(--_finish);
		}
		iterator insert(iterator position, const value_type& val)
		{
			size_type tmp = position - begin();
			reserve(size() + 1);
			reserve(size() + 1);
			pointer cur;
			for (cur = _finish; cur != _start + tmp; --cur)
				*cur = *(cur - 1);
			_alloc.construct(cur, value_type(val));
			++_finish;
			return cur;
		}
		void insert(iterator position, size_type n, const value_type& val)
		{
			size_type tmp = position - begin();
			reserve(size() + n);
			pointer cur;
			for (cur = _finish + n - 1; cur != _start + tmp + n - 1; --cur)
				*cur = *(cur - n);
			for (; cur >= _start + tmp; --cur)
				_alloc.construct(cur, value_type(val));
			_finish += n;
		}
		template <typename Iter>
		void insert(iterator position, Iter first,
				typename ft::enable_if<!ft::is_same<typename Iter::iterator_category, void>::value, Iter>::type last)
		{
			size_type n = count_num(first, last);
			size_type tmp = position - begin();
			reserve(size() + n);
			pointer cur;
			for (cur = _finish + n - 1; cur != _start + tmp + n - 1; --cur)
				*cur = *(cur - n);
			for (; cur >= _start + tmp; --cur)
				_alloc.construct(cur, value_type(*--last));
			_finish += n;
		}
		iterator erase(iterator position)
		{
			iterator tmp(position);
			_alloc.destroy(_start + (position - begin()));
			--_finish;
			for (; tmp != end(); ++tmp)
				*tmp = *(tmp + 1);
			return position;
		}
		iterator erase(iterator first, iterator last)
		{
			iterator tmp(first);
			size_type n = 0;
			for (; tmp != last; ++tmp, ++n)
				_alloc.destroy(_start + (tmp - begin()));
			tmp = first;
			for (; tmp + n != end(); ++tmp)
				*tmp = *(tmp + n);
			_finish -= n;
			return first;
		}
		void swap(vector& x)
		{
			std::swap(_alloc, x._alloc);
			std::swap(_start, x._start);
			std::swap(_finish, x._finish);
			std::swap(_end_storage, x._end_storage);
		}
		void clear()
		{
			for (pointer i = _start; i != _finish; ++i)
				_alloc.destroy(i);
			_finish = _start;
		}
		
		//allocator
		allocator_type get_allocator() const
		{
			return _alloc;
		}

		//bool
		void flip(void)
		{
			if (!ft::is_same<value_type, bool>::value)
				throw std::domain_error("there is no member named 'flip'");
			for (pointer i = _start; i != _finish; ++i)
				*i = !*i;
		}
		static void swap(reference ref1, reference ref2)
		{
			if (!ft::is_same<value_type, bool>::value)
				throw std::domain_error("there is no member named 'swap'");
			bool tmp = ref1;
			ref1 = ref2;
			ref2 = tmp;
		}

	private:
		template <typename Iter>
		size_type count_num(typename ft::enable_if<ft::is_same<typename Iter::iterator_category, random_access_iterator_tag>::value, Iter>::type first, Iter last)
		{
			return last - first;
		}
		template <typename Iter>
		size_type count_num(typename ft::enable_if<!ft::is_same<typename Iter::iterator_category, random_access_iterator_tag>::value, Iter>::type first, Iter last)
		{
			size_type n = 0;
			for (; first != last; ++first)
				++n;
			return n;
		}
		allocator_type _alloc;
		pointer _start;
		pointer _finish;
		pointer _end_storage;
	};

	template <typename T, typename Alloc>
	bool operator==(const vector<T, Alloc>& l, const vector<T, Alloc>& r)
	{
		if (l.size() != r.size())
			return false;
		for (typename vector<T, Alloc>::size_type i = 0; i < l.size(); ++i)
			if (l[i] != r[i])
				return false;
		return true;
	}
	template <typename T, typename Alloc>
	bool operator!=(const vector<T, Alloc>& l, const vector<T, Alloc>& r)
	{
		return !(l == r);
	}
	template <typename T, typename Alloc>
	bool operator<(const vector<T, Alloc>& l, const vector<T, Alloc>& r)
	{
		for (typename vector<T, Alloc>::size_type i = 0; i < l.size() && i < r.size(); ++i)
			if (l[i] != r[i])
				return l[i] < r[i];
		return l.size() < r.size();
	}
	template <typename T, typename Alloc>
	bool operator<=(const vector<T, Alloc>& l, const vector<T, Alloc>& r)
	{
		return !(r < l);
	}
	template <typename T, typename Alloc>
	bool operator>(const vector<T, Alloc>& l, const vector<T, Alloc>& r)
	{
		return r < l;
	}
	template <typename T, typename Alloc>
	bool operator>=(const vector<T, Alloc>& l, const vector<T, Alloc>& r)
	{
		return !(l < r);
	}
	template <typename T, typename Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
};

#endif
