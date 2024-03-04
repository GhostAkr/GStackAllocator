#ifndef GALG_GSTACKALLOCATOR_HPP
#define GALG_GSTACKALLOCATOR_HPP

#include <map>
#include <array>

namespace GAlg
{
    template <typename T, std::size_t Size>
    class GStackAllocator
    {
    public:
        GStackAllocator()
            : memory{}
            , freeBlocks{{0, Size}}
        {}

        T* allocate(size_t size)
        {
            // Find the first suitable free block
            for (auto block : freeBlocks)
            {
                std::size_t blockStart = block.first;
                std::size_t blockSize = block.second;

                if (blockSize < size)
                    continue;

                // Suitable block found - update free blocks and return the pointer
                freeBlocks.erase(blockStart);
                if (size != blockSize)
                    freeBlocks[blockStart + size] = blockSize - size;

                return reinterpret_cast<T*>(memory.data() + blockStart);
            }

            // No free memory - throw an exception
            throw std::bad_alloc();
        }

    private:
        std::array<char, Size> memory;

        // Pool index -> Block size
        std::map<std::size_t, std::size_t> freeBlocks;
    };
}

#endif  // GALG_GSTACKALLOCATOR_HPP
