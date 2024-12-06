#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "Iterator.hpp"
# include "Pair.hpp"

namespace ft
{
    // BST_Node
    template <typename T>
    struct BST_Node
    {
        public:
            // member type
            typedef T   value_type;
            // member variable
            value_type  value;
            BST_Node*   parent;
            BST_Node*   left;
            BST_Node*   right;
            // 기본 생성자
            BST_Node()
            :
                value(),
                parent(u_nullptr),
                left(u_nullptr),
                right(u_nullptr)
            {}
            BST_Node (  BST_Node* _parent = u_nullptr,
                        BST_Node* _left = u_nullptr,
                        BST_Node* _right = u_nullptr)
            :
                value(),
                parent(_parent),
                left(_left),
                right(_right)
            {}
            BST_Node (  const value_type& _val,
                        BST_Node* _parent = u_nullptr,
                        BST_Node* _left = u_nullptr,
                        BST_Node* _right = u_nullptr)
            :
                value(_val),
                parent(_parent),
                left(_left),
                right(_right)
            {}
            // 복사 생성자
            BST_Node (const BST_Node& node)
            :
                value(node.value),
                parent(node.parent),
                left(node.left),
                right(node.right)
            {}
            // 대입 연산자 오버로딩
            BST_Node &operator=(const BST_Node& node)
            {
                if (node == *this)
                    return *this;
                this->value = node.value;
                this->parent = node.parent;
                this->left = node.left;
                this->right = node.right;
                return *this;
            }
            // 소멸자
            virtual ~BST_Node() {}
    };
    // BST_iterator
    // T는 BST_Node
    // Compare은 less가 default
    // BST iterator는 bidirectional_iterator가 default
    template <typename T, typename Compare>
    class BST_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        public:
            typedef typename T::value_type  value_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category    iterator_category;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type      difference_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer              pointer;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference            reference;
        
        public:
            T*      _node;          // 현재 가리키고 있는 node
            T*      _last_node;     // 꼬리 노드 혹은 빈 노드
            Compare _comp;          // comp function

        public:
            BST_iterator(const Compare& comp = Compare()) : _node(), _last_node(), _comp(comp) {}
            BST_iterator(T* node, T* last_node, const Compare& comp = Compare()) : _node(node), _last_node(last_node), _comp(comp) {}
            BST_iterator(const BST_iterator& bst_it) : _node(bst_it._node), _last_node(bst_it._last_node), _comp(bst_it._comp) {}
            BST_iterator &operator= (const BST_iterator& bst_it)
            {
                this->_node = bst_it._node;
                this->_last_node = bst_it._last_node;
                this->_comp = bst_it._comp;
                return (*this);
            }
            // destructor
            virtual ~BST_iterator() {}
            // operator overloading
            bool operator== (const BST_iterator& bst_it) { return (this->_node == bst_it._node); }
            bool operator!= (const BST_iterator& bst_it) { return (this->_node != bst_it._node); }
            reference operator* (void) const { return (this->_node->value); }
            pointer operator-> (void) const { return (&this->_node->value); }
            /*
            **
            **                  42
            **                 /  \
            **               15    58
            **              /  \
            **             2    26    
            */
            BST_iterator& operator++ (void)
            {
                T* curr = _node;

                // _node의 right가 비어있을 때
                if (curr->right == _last_node)
                {
                    curr = _node->parent;
                    // curr이 root node가 아니고 && 자식이 부모보다 크다면, 즉 _node가 right 노드라면
                    while (curr != _last_node && _comp(curr->value.first, _node->value.first))
                        curr = curr->parent;
                    _node = curr;
                }
                else if (curr == _last_node)
                {
                    _node = _last_node->right;
                }
                // _node의 right가 비어있지 않다면
                else
                {
                    curr = _node->right;
                    if (curr == _last_node->parent && curr->right == _last_node)
                        _node = curr;
                    else
                    {
                        while (curr->left != _last_node)
                            curr = curr->left;
                    }
                    _node = curr;
                }
                return *this;
            }

            BST_iterator operator++(int)
            {
                BST_iterator temp(*this);
                operator++();
                return (temp);
            }

            BST_iterator& operator--(void)
            {
                T* curr = _node;

                if (curr->left == _last_node)
                {
                    curr = _node->parent;
                    while (curr != _last_node && !_comp(curr->value.first, _node->value.first))
                        curr = curr->parent;
                    _node = curr;
                }
                else if (curr == _last_node)
                {
                    _node = _last_node->right;
                }
                else
                {
                    curr = _node->left;
                    if (curr == _last_node->parent && curr->left == _last_node)
                        _node = curr;
                    else
                    {
                        while (curr->right != _last_node)
                            curr = curr->right;
                    }
                    _node = curr;
                }
                return *this;
            }

            BST_iterator operator--(int)
            {
                BST_iterator temp(*this);
                operator--();
                return (temp);
            }
    };
    // BST_const_iterator
    template <typename T, typename Compare>
    class BST_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        public:
            typedef typename T::value_type  value_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category    iterator_category;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type      difference_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer              pointer;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference            reference;
        
        public:
            T*      _node;          // 현재 가리키고 있는 node
            T*      _last_node;     // 꼬리 노드 혹은 빈 노드
            Compare _comp;          // comp function

        public:
            BST_const_iterator(const Compare& comp = Compare()) : _node(), _last_node(), _comp(comp) {}
            BST_const_iterator(T* node, T* last_node, const Compare& comp = Compare()) : _node(node), _last_node(last_node), _comp(comp) {}
            BST_const_iterator(const BST_const_iterator& bst_it) : _node(bst_it._node), _last_node(bst_it._last_node), _comp(bst_it._comp) {}
            BST_const_iterator(const BST_iterator<T, Compare>& bst_it) : _node(bst_it._node), _last_node(bst_it._last_node), _comp(bst_it._comp) {}
            BST_const_iterator &operator= (const BST_const_iterator& bst_it)
            {
                if (bst_it == *this)
                    return (*this);
                this->_node = bst_it._node;
                this->_last_node = bst_it._last_node;
                this->_comp = bst_it._comp;
                return (*this);
            }
            // destructor
            virtual ~BST_const_iterator() {}
            // operator overloading
            bool operator== (const BST_const_iterator& bst_it) { return (this->_node == bst_it._node); }
            bool operator!= (const BST_const_iterator& bst_it) { return (this->_node != bst_it._node); }
            reference operator* (void) const { return (this->_node->value); }
            pointer operator-> (void) const { return (&this->_node->value); }
            /*
            **
            **                  42
            **                 /  \
            **               15    58
            **              /  \
            **             2    26    
            */
            BST_const_iterator& operator++ (void)
            {
                T* curr = _node;

                // _node의 right가 비어있을 때
                if (curr->right == _last_node)
                {
                    curr = _node->parent;
                    // curr이 root node가 아니고 && 자식이 부모보다 크다면, 즉 _node가 right 노드라면
                    while (curr != _last_node && _comp(curr->value.first, _node->value.first))
                        curr = curr->parent;
                    _node = curr;
                }
                else if (curr == _last_node)
                {
                    _node = _last_node->right;
                }
                // _node의 right가 비어있지 않다면
                else
                {
                    curr = _node->right;
                    if (curr == _last_node->parent && curr->right == _last_node)
                        _node = curr;
                    else
                    {
                        while (curr->left != _last_node)
                            curr = curr->left;
                    }
                    _node = curr;
                }
                return *this;
            }

            BST_const_iterator operator++(int)
            {
                BST_const_iterator temp(*this);
                operator++();
                return (temp);
            }

            BST_const_iterator& operator--(void)
            {
                T* curr = _node;

                if (curr->left == _last_node)
                {
                    curr = _node->parent;
                    while (curr != _last_node && _comp(curr->value.first, _node->value.first))
                        curr = curr->parent;
                    _node = curr;
                }
                else if (curr == _last_node)
                    _node = _last_node->right;
                else
                {
                    curr = _node->left;
                    if (curr == _last_node->parent && curr->left == _last_node)
                        _node = curr;
                    else
                    {
                        while (curr->right != _last_node)
                            curr = curr->right;
                    }
                    _node = curr;
                }
                return *this;
            }

            BST_const_iterator operator--(int)
            {
                BST_const_iterator temp(*this);
                operator--();
                return (temp);
            }
    };
    // BST
    template <  class T,
                class Compare = ft::less<T>,
                class Node = ft::BST_Node<T>,
                class Type_Alloc = std::allocator<T>,
                class Node_Alloc = std::allocator<Node> >
    class BST
    {
        public:
            typedef BST                 self;
            typedef self&               self_reference;
            typedef T                   value_type;             // std::pair<T1, T2> 가 들어올것임
            typedef Type_Alloc          type_alloc;
            typedef Node                node_type;
            typedef Node*               node_pointer;
            typedef Node_Alloc          node_alloc;
            typedef ft::BST_iterator<Node, Compare>         iterator;
            typedef ft::BST_const_iterator<Node, Compare>   const_iterator;
            typedef size_t              size_type;

        public:
            // _last_node->parent = root node
            // _last_node->right = last node
            // _last_node->left = first node
            node_pointer                _last_node;
            node_alloc                  _node_alloc;
            int                         _size;
            node_pointer                _min;
            node_pointer                _max;
        
        public:
            BST (const node_alloc& _node_alloc_init = node_alloc())
            :
                _node_alloc(_node_alloc_init),
                _size(0),
                _min(0),
                _max(0)
            {
                _last_node = _node_alloc.allocate(1);
                _node_alloc.construct(_last_node, Node(_last_node, _last_node, _last_node));
            }
            ~BST ()
            {
                _node_alloc.destroy(_last_node);
                _node_alloc.deallocate(_last_node, 1);
            }
            int getSize() const
            {
                return _size;
            }
            ft::pair<iterator, bool> insertPair(value_type to_insert)
            {
                Node* prev_node = _last_node;
                Node* curr_node = _last_node->parent;

                // true라면 leaf node의 right에 insert
                bool side = true;

                // root부터 leaf까지 한칸 한칸 탐색
                while (curr_node != _last_node)
                {
                    int curr_key = curr_node->value.first;
                    if (curr_key == to_insert.first)
                        return ft::make_pair(iterator(curr_node, _last_node), false);

                    prev_node = curr_node;
                    if (to_insert.first > curr_key)
                    {
                        side = true;
                        curr_node = curr_node->right;
                    }
                    else
                    {
                        side = false;
                        curr_node = curr_node->left;
                    }
                }

                Node* new_node = _node_alloc.allocate(1);
                // 새로운 노드의 parent는 prev_node이고, left, right는 _last_node
                _node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));

                // BST가 비어있을 때
                if (prev_node == _last_node)
                {
                    _last_node->parent = new_node;
                    _last_node->left = new_node;
                    _last_node->right = new_node;
                }
                // 제일 아래 노드까지 왔을 때 그 노드의 key보다 insert할 key가 크다면
                else if (side == true)
                    prev_node->right = new_node;
                else
                    prev_node->left = new_node;

                if (_last_node->left->value.first > new_node->value.first)
                    _last_node->left = new_node;
                if (_last_node->right->value.first < new_node->value.first)
                    _last_node->right = new_node;
                _size += 1;
                return (ft::make_pair(iterator(new_node, _last_node), true));
            }
            void removeByKey(value_type to_remove)
            {
                _removeByKey(_last_node->parent, to_remove);
            }
            // 찾으면 curr 반환 없으면 _last_node반환
            node_pointer serachByKey(value_type pair)
            {
                node_pointer curr = _last_node->parent;

                while (curr != _last_node)
                {
                    if (curr->value.first == pair.first)
                        return curr;
                    if (curr->value.first > pair.first)
                        curr = curr->left;
                    else
                        curr = curr->right;
                }
                return curr;
            }
            void swap(self& x)
            {
                if (&x == this)
                    return ;
                node_pointer temp = this->_last_node;
                this->_last_node = x._last_node;
                x._last_node = temp;
            }
            size_type max_size() const { return node_alloc().max_size(); }
        private:
            // 현재 node의 자식 중에서 가장 작은 key를 가진 node를 반환
            node_pointer _BST_get_lower_node(node_pointer root)
            {
                while (root != _last_node && root->left != _last_node)
                    root = root->left;
                return (root);
            }
            // 현재 node의 자식 중에서 가장 큰 key를 가진 node를 반환
            node_pointer _BST_get_higher_node(node_pointer root)
            {
                while (root != _last_node && root->right != _last_node)
                    root = root->right;
                return (root);
            }
            // 지우려는 노드가 left, right 둘다 있는 경우
            void _replaceDoubleChildren(node_pointer& remove_node, node_pointer new_node)
            {
                // 지우려는 노드가 root가 아니면서, 새로 넣을 노드의 parent가 remove가 아닌 경우
                // parent의 left를 new_node의 right로 교체해줘야함.
                if (remove_node->parent != _last_node && new_node->parent != remove_node)
                    new_node->parent->left = new_node->right;
                
                // new_node의 값들을 remove_node 값으로 교체하기
                new_node->parent = remove_node->parent;
                if (remove_node->left != new_node)
                    new_node->left = remove_node->left;
                if (remove_node->right != new_node)
                    new_node->right = remove_node->right;
                
                // 지우려는 노드가 root노드라면
                if (remove_node->parent == _last_node)
                    _last_node->parent = new_node;
                // remove_node에 연결되어 있던 parent node 값을 new_node로 교체해주기
                else
                {
                    if (remove_node->parent->left == remove_node)
                        remove_node->parent->left = new_node;
                    else if (remove_node->parent->right == remove_node)
                        remove_node->parent->right = new_node;
                }
                // remove_node에 연결되어 있던 자식 node 값을 new_node로 교체해주기
                if (remove_node->left != _last_node && remove_node->left != new_node)
                    remove_node->left->parent = new_node;
                if (remove_node->right != _last_node && remove_node->right != new_node)
                    remove_node->right->parent = new_node;
                
                _last_node->left = _BST_get_lower_node(_last_node->parent);
                _last_node->right = _BST_get_higher_node(_last_node->parent);
                _size -= 1;


                _node_alloc.destroy(remove_node);
                _node_alloc.deallocate(remove_node, 1);
            }
            void _replaceNodeInParent(node_pointer remove_node, node_pointer new_node)
            {
                // 지우려는 노드가 root라면
                if (remove_node->parent == _last_node)
                    _last_node->parent = new_node;
                else
                {   
                    // parent의 left 혹은 right를 new_node로 대체
                    if (remove_node == remove_node->parent->left)
                        remove_node->parent->left = new_node;
                    else
                        remove_node->parent->right = new_node;
                }

                _last_node->left = _BST_get_lower_node(_last_node->parent);
                _last_node->right = _BST_get_higher_node(_last_node->parent);
                _size -= 1;

                // new_node의 parent를 지울 node의 parent로 교체
                new_node->parent = remove_node->parent;

                _node_alloc.destroy(remove_node);
                _node_alloc.deallocate(remove_node, 1);
            }
            // 노드를 지우는 재귀함수
            void _removeByKey(node_pointer node, value_type pair)
            {
                if (node == _last_node)
                    return ;
                // 찾으려는 값이 노드 값보다 작은 경우 
                if (pair.first < node->value.first)
                {
                    _removeByKey(node->left, pair);
                    return ;
                }
                // 찾으려는 값이 노드 값보다 큰 경우 
                if (pair.first > node->value.first)
                {
                    _removeByKey(node->right, pair);
                    return ;
                }
                // 찾았는데 찾은 노드가 left, right 둘다 있다면
                if (node->left != _last_node && node->right != _last_node)
                {
                    node_pointer successor = _BST_get_lower_node(node->right);
                    _replaceDoubleChildren(node, successor);
                }
                // 찾았는데 찾은 노드가 left만 있다면
                else if (node->left != _last_node)
                    _replaceNodeInParent(node, node->left);
                // 찾았는데 찾은 노드가 right만 있다면
                else if (node->right != _last_node)
                    _replaceNodeInParent(node, node->right);
                // 찾았는데 찾은 노드가 leaf 노드라면
                else
                    _replaceNodeInParent(node, _last_node);
            }
    };
}

#endif