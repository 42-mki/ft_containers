#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP
# include "Iterator.hpp"
# include "__tree"

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
            T*      _last_node;     // 이전 node
            Compare _comp;          // comp function

        public:
            // default constructor
            BST_iterator(const Compare& comp = Compare())
            :
                _node(),
                _last_node(),
                _comp(comp)
            {}
            // default constructor
            BST_iterator(T* node, T* last_node, const Compare& comp = Compare())
            :
                _node(node),
                _last_node(last_node),
                _comp(comp)
            {}
            // copy constructor
            BST_iterator(const BST_iterator& bst_it)
            :
                _node
            {}
            // operator= overloading
            BST_iterator &operator= (const BST_iterator& bst_it)
            {
                if (bst_it == *this)
                    return (*this);
                this->_node = bst_it._node;
                this->_last_node = bst_it._last_node;
                this->_comp = bst_it._comp;
                return (*this);
            }
            // destructor
            virtual ~BST_iterator() {}
            // operator overloading
            bool operator== (const BST_iterator& bst_it)
            {
                return (this->_node == bst_it._node);
            }
            bool operator!= (const BST_iterator& bst_it)
            {
                return (this->_node != bst_it._node);
            }
            reference operator* (void) const
            {
                return (this->_node->value);
            }
            pointer operator-> (void) const
            {
                return (&this->_node->value);
            }

            BST_iterator& operator++ (void)
            {
                T* cursor = _node;

                if (_node->right == _last_node)
                {
                    cursor = _node->parent;
                    while (cursor != _last_node && _comp(cursor->value.first, _node->value.first))
                        cursor = cursor->parent;
                    _node = cursor;
                }
                else if (cursor == _last_node)
                {

                }
                else
                {

                }
                return *this;
            }

            BST_iterator operator++(int)
            {

            }

            BST_iterator& operator--(void)
            {

            }

            BST_iterator operator--(int)
            {

            }
    };
    // BST_const_iterator
    template <typename T, typename Compare>
    class BST_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        public:
            typedef typename T::value_type  value_type;
    };
    // BinarySearchTree
    template <  class T,
                class Compare = ft::less<T>,
                class Node = ft::BST_Node<T>,
                class Type_Alloc = std::allocator<T>,
                class Node_Alloc = std::allocator<Node> >
    class BinarySearchTree
    {
        public:
            typedef BinarySearchTree    self;
            typedef self&               self_reference;
            typedef T                   value_type;
            typedef Type_Alloc          type_alloc;
            typedef Node                node_type;
            typedef Node*               node_pointer;
            typedef Node_Alloc          node_alloc;
            typedef ft::BST_iterator<Node, Compare>         iterator;
            typedef ft::BST_const_iterator<Node, Compare>   const_iterator;
            typedef size_t              size_type;

        public:
            node_pointer                _last_node;
            node_alloc                  _node_alloc;
        
        public:
            BinarySearchTree (const node_alloc& _node_alloc_init = node_alloc())
            :
                _node_alloc(_node_alloc_init)
            {

            }
            ~BinarySearchTree ()
            {

            }
            ft::pair<iterator, bool> insertPair(value_type to_insert)
            {

            }
            void removeByKey(value_type to_remove)
            {

            }
            node_pointer serachByKey(value_type to_remove)
            {

            }
            void swap(self& x)
            {

            }
            size_type max_size() const
            {

            }
        private:
            node_pointer _BST_get_lower_node(node_pointer root)
            {

            }
            node_pointer _BST_get_higher_node(node_poinetr root)
            {

            }
            void _replaceNodeInParent(node_pointer node, node_pointer new_node)
            {

            }
            void _replaceDoubleChildren(node_pointer& to_remove, node_pointer new_node)
            {

            }
            void _removeByKey(node_pointer node, value_type to_remove)
            {

            }
    };
}

#endif