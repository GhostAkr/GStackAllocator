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

        // WARNING: there are no safe guards when working with free blocks. Any unexpected
        // call to deallocate will cause UB
        void deallocate(T* ptr, size_t size)
        {
            size_t targetBlockStart = reinterpret_cast<char*>(ptr) - memory.data();
            size_t targetBlockSize = size;

            // Search if we have another free block BEFORE the current one
            for (auto block : freeBlocks)
            {
                std::size_t blockStart = block.first;
                std::size_t blockSize = block.second;

                if (blockStart > targetBlockStart)
                    break;

                if (blockStart + blockSize == targetBlockStart - 1)
                {
                    // Merge free blocks and delete the old one
                    targetBlockStart = blockStart;
                    targetBlockSize += blockSize;
                    freeBlocks.erase(blockStart);
                    break;
                }
            }

            // Search if we have another free block AFTER the current one
            for (auto block : freeBlocks)
            {
                std::size_t blockStart = block.first;
                std::size_t blockSize = block.second;

                if (blockStart == targetBlockStart + targetBlockSize)
                {
                    // Merge free blocks and delete the old one
                    targetBlockSize += blockSize;
                    freeBlocks.erase(blockStart);
                }
                else if (blockStart > targetBlockStart + targetBlockSize)
                    break;
            }

            // Add new free block
            freeBlocks[targetBlockStart] = targetBlockSize;
        }

    private:
        std::array<char, Size> memory;

        // Pool index -> Block size
        std::map<std::size_t, std::size_t> freeBlocks;
    };
}

#endif  // GALG_GSTACKALLOCATOR_HPP
