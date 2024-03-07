#include <iostream>
#include <vector>

#include "gstackallocator/gstackallocator.hpp"

// Using main() to run GAlg::GStackAllocator examples
int main()
{
    GAlg::GStackAllocator<int, 20> stackAlloc;  // can fit 5 ints
    
    try
    {
        std::vector<int*> ptrs;
        for (int i = 0; i < 5; ++i)
        {
            int* val = stackAlloc.allocate(sizeof(int));
            *val = i;
            ptrs.push_back(val);
            std::cout << "Value " << *val << " at address " << val << std::endl;
        }

        stackAlloc.deallocate(ptrs[1], sizeof(int));
        stackAlloc.deallocate(ptrs[3], sizeof(int));
        stackAlloc.deallocate(ptrs[2], sizeof(int));

        int* val = stackAlloc.allocate(sizeof(int));
        *val = 10;
        std::cout << "Value " << *val << " at address " << val << std::endl;

        val = stackAlloc.allocate(sizeof(int));
        *val = 11;
        std::cout << "Value " << *val << " at address " << val << std::endl;

        val = stackAlloc.allocate(sizeof(int));
        *val = 12;
        std::cout << "Value " << *val << " at address " << val << std::endl;
    }
    catch (const std::bad_alloc& ex)
    {
        std::cout << "Bad alloc" << std::endl;
    }

    return 0;
}
