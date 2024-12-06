#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
    // #include <utility>
    // std::pair struct
    // https://www.cplusplus.com/reference/utility/pair/
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair() : first(), second() {}
        template <typename U1, typename U2>
        pair(const pair<U1, U2>& pr): first(pr.first), second(pr.second) {}
        pair(const first_type& x, const second_type& y): first(x), second(y) {}
        pair& operator=(const pair& p)
        {
            first = p.first;
            second = p.second;
            return *this;
        }
    };
    template <class T1, class T2>
    inline
    bool
    operator==(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
    {
        return x.first == y.first && x.second == y.second;
    }
    template <class T1, class T2>
    inline
    bool
    operator!=(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
    {
        return !(x == y);
    }
    template <class T1, class T2>
    inline
    bool
    operator<(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
    {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    }
    template <class T1, class T2>
    inline
    bool
    operator>(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
    {
        return y < x;
    }
    template <class T1, class T2>
    inline
    bool
    operator>=(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
    {
        return !(x < y);
    }
    template <class T1, class T2>
    inline
    bool
    operator<=(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
    {
        return !(y > x);
    }

    template <class T1, class T2>
    inline
    ft::pair<T1,T2>
    make_pair(T1 x, T2 y)
    {
        return ft::pair<T1, T2>(x, y);
    }
} // namespace ft

#endif