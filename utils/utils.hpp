#ifndef UTILS_HPP
# define UTILS_HPP

#include <sstream>

const class {
public:
    template <class T>
    operator T*() const {
        return 0;
    }
    template <class T, class C>
    operator T C::*() const {
        return 0;
    }
private:
    void operator&() const;
} u_nullptr = {};

namespace ft
{
    template <typename T>
    std::string to_string(T n)
    {
        std::ostringstream os;
        ss << n;
        return (ss.str());
    }
}

#endif
