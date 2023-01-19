#include <MathUtility.hpp>

namespace REKT
{
    uint64_t MathUtility::NearestPowerOfTwo(uint64_t n)
    {
        uint64_t v = n; 

        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v |= v >> 32;
        v++; // next power of 2

        uint64_t x = v >> 1; // previous power of 2

        return (v - n) > (n - x) ? x : v;
    }
}