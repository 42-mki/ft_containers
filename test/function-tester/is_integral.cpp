#include <iostream>
#include <type_traits>
#include "../utils/Utils.hpp"

int main(void)
{
    std::cout << std::is_integral<int>::value << "\n";
    std::cout << std::is_integral<float>::value << "\n";
    std::cout << ft::is_integral<int>::value << "\n";
    std::cout << ft::is_integral<float>::value << "\n";
    std::enable_if< std::is_integral<int>::value>::type;
    return 0;
}