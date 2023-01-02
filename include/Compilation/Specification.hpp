#ifndef SPECIFICATION_HPP
#define SPECIFICATION_HPP

#include <cstdint>

namespace VoltLang
{
    typedef unsigned char byte;

    enum class OperandType : uint8_t
    {
        Register = 0,
        Data,
        LabelToInstruction,
        LabelToFunction,
        IntegerLiteral,
        FloatingPointLiteral
    };

    enum Type : uint8_t
    {
        UInt8 = 0,
        Int8 = 1,
        UInt16 = 2,
        Int16 = 3,
        UInt32 = 4,
        Int32 = 5,
        UInt64 = 6,
        Int64 = 7,
        Single = 8,
        Double = 9,
        Pointer = 10,
        Unknown = 11
    };

    struct OffsetInfo
    {
        uint64_t offset;
        uint64_t size;
    };
}
#endif
