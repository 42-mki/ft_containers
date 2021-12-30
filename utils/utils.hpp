#ifndef UTILS_HPP
# define UTILS_HPP

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

#endif
