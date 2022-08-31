#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <iostream>
# include <memory>
# include "vector.hpp"
# include "rb_tree_iterator.hpp"
# include "rb_tree_reverse_iterator.hpp"

namespace ft
{
	static int _level = -1;
	template <typename Key, typename Val, typename KeyOfValue, typename Comp = std::less<Key>, typename Alloc = std::allocator<Val> >
	class rb_tree
	{
		typedef typename Alloc::template rebind<node<Val> >::other _node_allocator;
	public:
		typedef Key key_type;
		typedef Val value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Alloc allocator_type;
		typedef struct node<Val> node;
		typedef node* node_pointer;
		typedef rb_tree_iterator<value_type> iterator;
		typedef rb_tree_const_iterator<value_type> const_iterator;
		typedef rb_tree_reverse_iterator<iterator> reverse_iterator;
		typedef rb_tree_const_reverse_iterator<const_iterator> const_reverse_iterator;

		rb_tree(const Comp& comp = Comp(), const allocator_type& alloc = allocator_type()): _comp(comp), _alloc(alloc), _size(0), _nalloc(_node_allocator())
		{
			_nil = _nalloc.allocate(1);
			_nalloc.construct(_nil, node());
			_nil->value = _alloc.allocate(1);
			_alloc.construct(_nil->value, value_type());
			_nil->parent = _nil->left = _nil->right = _nil;
			_nil->color = black;
			_root = _nil;
		}
		rb_tree(const rb_tree& x): _comp(x._comp), _alloc(x._alloc), _size(0), _nalloc(_node_allocator())
		{
			_nil = _nalloc.allocate(1);
			_nalloc.construct(_nil, node());
			_nil->value = _alloc.allocate(1);
			_alloc.construct(_nil->value, value_type());
			_nil->parent = _nil->left = _nil->right = _nil;
			_nil->color = black;
			_root = _nil;
			for (const_iterator itr = x.begin(); itr != x.end(); ++itr)
				insert(*itr);
		}
		~rb_tree()
		{
			clear();
			_alloc.destroy(_nil->value);
			_alloc.deallocate(_nil->value, 1);
			_nalloc.destroy(_nil);
			_nalloc.deallocate(_nil, 1);
		}
		rb_tree& operator=(const rb_tree& x)
		{
			clear();
			for (const_iterator itr = x.begin(); itr != x.end(); ++itr)
				insert(*itr);
			return *this;
		}

		node_pointer minimum(node_pointer x)
		{
			while (x->left != _nil)
				x = x->left;
			return x;
		}
		void left_rotate(node_pointer x)
		{
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == _nil)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		void right_rotate(node_pointer x)
		{
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != _nil)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == _nil)
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}
		pair<iterator, bool> insert(const value_type& x)
		{
			node_pointer newnode = _nalloc.allocate(1);
			_nalloc.construct(newnode, node());
			newnode->left = newnode->right = newnode->parent = _nil;
			newnode->color = red;
			newnode->value = _alloc.allocate(1);
			_alloc.construct(newnode->value, value_type(x));
			return insert(newnode);
		}
		pair<iterator, bool> insert(node_pointer z)
		{
			node_pointer y = _nil;
			node_pointer x = _root;
			while (x != _nil)
			{
				y = x;
				if (KeyOfValue()(*z->value) == KeyOfValue()(*x->value))
				{
					_alloc.destroy(z->value);
					_alloc.deallocate(z->value, 1);
					_nalloc.destroy(z);
					_nalloc.deallocate(z, 1);
					return ft::make_pair(iterator(_nil, _root, x), false);
				}
				else if (_comp(KeyOfValue()(*z->value), KeyOfValue()(*x->value)))
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == _nil)
				_root = z;
			else if (_comp(KeyOfValue()(*z->value), KeyOfValue()(*y->value)))
				y->left = z;
			else
				y->right = z;
			++_size;
			if (z->parent == _nil)
				z->color = black;
			else if (z->parent->parent != _nil)
				insert_fixup(z);
			return ft::make_pair(iterator(_nil, _root, z), true);
		}
		void insert_fixup(node_pointer z)
		{
			node_pointer u;
			while (z->parent->color == red)
			{
				if (z->parent == z->parent->parent->right)
				{
					u = z->parent->parent->left;
					if (u->color == red)
					{
						u->color = black;
						z->parent->color = black;
						z->parent->parent->color = red;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							right_rotate(z);
						}
						z->parent->color = black;
						z->parent->parent->color = red;
						left_rotate(z->parent->parent);
					}
				}
				else
				{
					u = z->parent->parent->right;
					if (u->color == red)
					{
						u->color = black;
						z->parent->color = black;
						z->parent->parent->color = red;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->right)
						{
							z = z->parent;
							left_rotate(z);
						}
						z->parent->color = black;
						z->parent->parent->color = red;
						right_rotate(z->parent->parent);
					}
				}
				if (z == _root)
					break;
			}
			_root->color = black;
		}
		void transplant(node_pointer u, node_pointer v)
		{
			if (u->parent == _nil)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}
		void remove(node_pointer z)
		{
			if (z == _nil)
				return ;
			node_pointer y = z, x;
			rb_color org = y->color;
			if (z->left == _nil)
			{
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == _nil)
			{
				x = z->left;
				transplant(z, z->left);
			}
			else
			{
				y = minimum(z->right);
				org = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (z->value)
			{
				_alloc.destroy(z->value);
				_alloc.deallocate(z->value, 1);
			}
			_nalloc.destroy(z);
			_nalloc.deallocate(z, 1);
			--_size;
			if (org == black)
				remove_fixup(x);
			_nil->left = _nil->right = _nil->parent = _nil;
			_nil->color = black;
		}
		void remove_fixup(node_pointer x)
		{
			node_pointer w;
			while (x != _root && x->color == black)
			{
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->color == red)
					{
						w->color = black;
						x->parent->color = red;
						left_rotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == black && w->right->color == black)
					{
						w->color = red;
						x = x->parent;
					}
					else
					{
						if (w->right->color == black)
						{
							w->left->color = black;
							w->color = red;
							right_rotate(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = black;
						w->right->color = black;
						left_rotate(x->parent);
						x = _root;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->color == red)
					{
						w->color = black;
						x->parent->color = red;
						right_rotate(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == black && w->left->color == black)
					{
						w->color = red;
						x = x->parent;
					}
					else
					{
						if (w->left->color == black)
						{
							w->right->color = black;
							w->color = red;
							left_rotate(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = black;
						w->left->color = black;
						right_rotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = black;
		}

		iterator begin()
		{
			node_pointer cur = _root;
			while (cur->left != _nil)
				cur = cur->left;
			return iterator(_nil, _root, cur);
		}
		const_iterator begin() const
		{
			node_pointer cur = _root;
			while (cur->left != _nil)
				cur = cur->left;
			return const_iterator(_nil, _root, cur);
		}
		iterator end()
		{
			return iterator(_nil, _root, _nil);
		}
		const_iterator end() const
		{
			return const_iterator(_nil, _root, _nil);
		}
		reverse_iterator rbegin()
		{
			node_pointer cur = _root;
			while (cur->right != _nil)
				cur = cur->right;
			return reverse_iterator(_nil, _root, cur);
		}
		const_reverse_iterator rbegin() const
		{
			node_pointer cur = _root;
			while (cur->right != _nil)
				cur = cur->right;
			return const_reverse_iterator(_nil, _root, cur);
		}
		reverse_iterator rend()
		{
			return reverse_iterator(_nil, _root, _nil);
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_nil, _root, _nil);
		}

		bool empty() const
		{
			return _size == 0;
		}
		size_type size() const
		{
			return _size;
		}
		size_type max_size() const
		{
			return _alloc.max_size() * sizeof(value_type) / (sizeof(node));
		}

		void erase(iterator position)
		{
			remove(position.cur());
		}
		void erase(const_iterator position)
		{
			remove(position.cur());
		}
		size_type erase(const key_type& k)
		{
			iterator itr = find(k);
			if (itr.cur() != _nil)
				erase(itr);
			return itr.cur() != _nil;
		}
		void erase(iterator first, iterator last)
		{
			vector<node_pointer> l;
			for (; first != last; ++first)
				l.push_back(first.cur());
			for (typename vector<node_pointer>::iterator itr = l.begin(); itr != l.end(); ++itr)
				remove(*itr);
		}
		void erase(const_iterator first, const_iterator last)
		{
			vector<node_pointer> l;
			for (; first != last; ++first)
				l.push_back(first.cur());
			for (typename vector<node_pointer>::iterator itr = l.begin(); itr != l.end(); ++itr)
				remove(*itr);
		}
		void swap(rb_tree& x)
		{
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
			std::swap(_root, x._root);
			std::swap(_nil, x._nil);
			std::swap(_size, x._size);
		}
		void clear()
		{
			_clear(_root);
			_size = 0;
			_root = _nil;
		}

		Comp key_compare() const
		{
			return _comp;
		}

		iterator find(const key_type& k)
		{
			node_pointer x = _root;
			while (x != _nil)
			{
				if (KeyOfValue()(*x->value) == k)
					break;
				else if (!_comp(KeyOfValue()(*x->value), k))
					x = x->left;
				else
					x = x->right;;
			}
			return iterator(_nil, _root, x);
		}
		const_iterator find(const key_type& k) const
		{
			node_pointer x = _root;
			while (x != _nil)
			{

				if (KeyOfValue()(*x->value) == k)
					break;
				else if (!_comp(KeyOfValue()(*x->value), k))
					x = x->left;
				else
					x = x->right;;
			}
			return const_iterator(_nil, _root, x);
		}
		size_type count(const key_type& k) const
		{
			const_iterator itr = find(k);
			return itr.cur() != _nil;
		}
		iterator lower_bound(const key_type& k)
		{
			node_pointer x = _root, y = _nil;
			while (x != _nil)
			{
				if (!(_comp(KeyOfValue()(*x->value), k)))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return iterator(_nil, _root, y);
		}
		const_iterator lower_bound(const key_type& k) const
		{
			node_pointer x = _root, y = _nil;
			while (x != _nil)
			{
				if (!(_comp(KeyOfValue()(*x->value), k)))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return const_iterator(_nil, _root, y);
		}
		iterator upper_bound(const key_type& k)
		{
			node_pointer x = _root, y = _nil;
			while (x != _nil)
			{
				if (_comp(k, KeyOfValue()(*x->value)))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return iterator(_nil, _root, y);
		}
		const_iterator upper_bound(const key_type& k) const
		{
			node_pointer x = _root, y = _nil;
			while (x != _nil)
			{
				if (_comp(k, KeyOfValue()(*x->value)))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return const_iterator(_nil, _root, y);
		}
		pair<iterator, iterator> equal_range(const key_type& k)
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		void print(node_pointer cur) const
		{
			++_level;
			if (cur->right != _nil)
			{
				print(cur->right);
				--_level;
			}
			for (int ix = 0; ix < _level; ++ix) std::cout << "    ";
			std::cout << (cur->color == red ?"|":"") << *cur->value << (cur->color == red ?"|":"") << std::endl;
			if (cur->left != _nil)
			{
				print(cur->left);
				--_level;
			}
		}
	private:
		void _clear(node_pointer cur)
		{
			if (cur == _nil)
				return;	
			_clear(cur->left);
			_clear(cur->right);
			_alloc.destroy(cur->value);
			_alloc.deallocate(cur->value, 1);
			_nalloc.destroy(cur);
			_nalloc.deallocate(cur, 1);
		}
		Comp _comp;
		allocator_type _alloc;
		node_pointer _root;
		node_pointer _nil;
		size_type _size;
		_node_allocator _nalloc;
	};
};

#endif
