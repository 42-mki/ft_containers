#include <iostream>
#include <memory>

int main()
{
    std::allocator<int> myAllocator;

    int* arr = myAllocator.allocate(5);
    // myAllocator.address(arr);
    // myAllocator.allocate();
    // myAllocator.construct();
    // myAllocator.deallocate();
    // myAllocator.destroy();
    // myAllocator.max_size();
}
