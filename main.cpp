#include <iostream>

#include "gstackallocator/gstackallocator.hpp"

// Using main() to run GAlg::GStackAllocator examples
int main()
{
    GAlg::GStackAllocator<int, 20> stackAlloc;  // can fit 5 ints
    
    try
    {
        for (int i = 0; i < 5; ++i)
        {
            int* val = stackAlloc.allocate(sizeof(int));
            *val = i;
            std::cout << "Value " << *val << " at address " << val << std::endl;
        }
    }
    catch (const std::bad_alloc& ex)
    {
        std::cout << "Bad alloc" << std::endl;
    }

    return 0;
}
