#ifndef VOLT_CONVERSIONUTILITY_HPP
#define VOLT_CONVERSIONUTILITY_HPP

#include <Core/Specification.hpp>

namespace VoltLang
{
    class ConversionUtility
    {
    public:
        static void CastSourceToDestinationType(Object* src, Object* dst, Type srcType, Type dstType);
    };
}

#endif