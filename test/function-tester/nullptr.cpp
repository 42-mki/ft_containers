#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>
# include <iostream>

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

int main()
{
    int *intAddress = nullptr;
    int *MyintAddress = u_nullptr;

    std::cout << intAddress << std::endl;
    std::cout << MyintAddress << std::endl;
}