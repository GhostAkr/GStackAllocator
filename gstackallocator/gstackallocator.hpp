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

    private:
        std::array<char, Size> memory;

        // Pool index -> Block size
        std::map<std::size_t, std::size_t> freeBlocks;
    };
}

#endif  // GALG_GSTACKALLOCATOR_HPP
