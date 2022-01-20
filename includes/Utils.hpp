#ifndef UTILS_HPP
# define UTILS_HPP

#include <sstream>  // std::ostringstream

// nullptr
// NULL은 문제가 있어서 C++11에서 도입되었습니다
// 함수 오버로딩시 NULL을 인자로 주는 경우 NULL을 int 0으로 인식합니다.

const class
{
    public:
        template <class T>
        operator T *() const
        {
            return 0;
        }

        template <class T, class C>
        operator T C::*() const
        {
            return 0;
        }
    private:
        void operator&() const;
} u_nullptr = {};

namespace ft
{
    // to_string
    // 어떤 Data type이 와도 string으로 바꿔줍니다
    // http://www.cplusplus.com/articles/D9j2Nwbp/
    template <typename T>
    std::string to_string(T n)
    {
        std::ostringstream os;
        os << n;
        return (os.str());
    };
    
    // #include <functional>
    // binary_function
    // http://www.cplusplus.com/reference/functional/binary_function/
    // less를 구한하기 위한 base struct
    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1   first_argument_type;
        typedef Arg2   second_argument_type;
        typedef Result result_type;
    };

    // #include <functional>
    // less 구조체
    // https://docs.microsoft.com/ko-kr/cpp/standard-library/less-struct?view=msvc-170
    // 함수 객체 개념을 알아봅시다.
    template <class T = void>
    struct less : public binary_function <T, T, bool>
    {
        bool operator()(const T& lhs, const T& rhs) const
        {
            return lhs < rhs;
        }
    };

    // #include <algorithm>
    // lexcicographical_compare
    // https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
    // https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
    // 위 reference에 코드가 다 나와있다.
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template<class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2,
                                Compare comp)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (comp(*first1, *first2)) return true;
            if (comp(*first2, *first1)) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    // <type_traits>
    // enable_if
    template<bool B, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    // <type_traits>
    // is_integral
    template <bool is_integral, typename T>
    struct is_integral_res
    {
        typedef T   type;
        static const bool value = is_integral;
    };

    // template specialization
    template <typename T>
    struct is_integral_type : public is_integral_res<false, bool> {};
    template <>
    struct is_integral_type<bool> : public is_integral_res<true, bool> {};
    template <>
    struct is_integral_type<char> : public is_integral_res<true, char> {};
    template <>
    struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
    template <>
    struct is_integral_type<short int> : public is_integral_res<true, short int> {};
    template <>
    struct is_integral_type<int> : public is_integral_res<true, int> {};
    template <>
    struct is_integral_type<long int> : public is_integral_res<true, long int> {};
    template <>
    struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
    template <>
    struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
    template <>
    struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
    template <>
    struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
    template <>
    struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
    template <>
    struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};
    
    // is_integral
    template <typename T>
    struct is_integral : public is_integral_type<T> {};
}

#endif
