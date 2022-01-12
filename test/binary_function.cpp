#include <iostream>
#include <functional>

struct Compare: public std::binary_function<int, int, bool> {
    bool operator() (int a, int b) {return (a == b);}
};

int main() {
    Compare Compare_object;
    Compare::first_argument_type input1;
    Compare::second_argument_type input2;
    Compare::result_type result;

    std::cout << "Please enter first number: ";
    std::cin >> input1;
    std::cout << "Please enter secont number: ";
    std::cin >> input2;

    result = Compare_object(input1, input2);

    std::cout << "Numbers " << input1 << " and " << input2;
    if (result)
        std::cout << " are equal.\n";
    else
        std::cout << " are not equal.\n";
    return 0;
}