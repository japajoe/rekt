#ifndef REKT_CONVERSIONUTILITY_HPP
#define REKT_CONVERSIONUTILITY_HPP

#include <Core/Specification.hpp>

namespace REKT
{
    class ConversionUtility
    {
    public:
        static void CastSourceToDestinationType(Object* src, Object* dst, Type srcType, Type dstType);
    };
}

#endif