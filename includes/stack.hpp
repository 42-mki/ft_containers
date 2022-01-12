#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
        protected:
            container_type      c;
        public:
            explicit stack (const container_type& _c = container_type())
            :
                c(_c);
            {}
            ~stack() {}
            bool empty() const
            {
                return (this->c.empty());
            }
            size_type size() const
            {
                return (this->c.size());
            }
            value_type& top()
            {
                return (this->c.back());
            }
            const value_type& top() const
            {
                return (this->c.back());
            }
            void push (const value_type& val)
            {
                this->c.push_back(val);
            }
            void pop ()
            {
                this->c.pop_back();
            }
            template <class T1, class C1>
            friend bool operator== (const ft::stack<T1, C1>& x, const ft:stack<T1, C1>& y);

            template <class T1, class C1>
            friend bool operator< (const ft::stack<T1, C1>& x, const ft:stack<T1, C1>& y);
    };
    template <class T, class Container>
    bool operator== (const ft::stack<T, Container>& x, const ft::stack<T, Container>& y)
    {
        return (x.c == y.c);
    }
    template <class T, class Container>
    bool operator< (const ft::stack<T, Container>& x, const ft::stack<T, Container>& y)
    {
        return (x.c < y.c);
    }
    template <class T, class Container>
    bool operator== (const ft::stack<T, Container>& x, const ft::stack<T, Container>& y)
    {
        return !(x.c == y.c);
    }
    template <class T, class Container>
    bool operator> (const ft::stack<T, Container>& x, const ft::stack<T, Container>& y)
    {
        return y < x;
    }
    template <class T, class Container>
    bool operator>= (const ft::stack<T, Container>& x, const ft::stack<T, Container>& y)
    {
        return !(x < y);
    }
    template <class T, class Container>
    bool operator<= (const ft::stack<T, Container>& x, const ft::stack<T, Container>& y)
    {
        return !(y < x);
    }
}

#endif