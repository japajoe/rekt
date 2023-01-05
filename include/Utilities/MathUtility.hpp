#ifndef MATHUTILITY_HPP
#define MATHUTILITY_HPP

#include <cstdint>

namespace VoltLang
{
    class MathUtility
    {
    public:
        static uint64_t NearestPowerOfTwo(uint64_t n);
    };
}
#endif