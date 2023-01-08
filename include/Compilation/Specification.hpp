#ifndef SPECIFICATION_HPP
#define SPECIFICATION_HPP

#include <cstdint>
#include <string>

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

    static std::string TypeToString(Type type)
    {
        switch(type)
        {
            case Type::UInt8:
                return "UInt8";
            case Type::Int8:
                return "Int8";
            case Type::UInt16:
                return "UInt16";
            case Type::Int16:
                return "Int16";
            case Type::UInt32:
                return "UInt32";
            case Type::Int32:
                return "Int32";
            case Type::UInt64:
                return "UInt64";
            case Type::Int64:
                return "Int64";
            case Type::Single:
                return "Single";
            case Type::Double:
                return "Double";
            case Type::Pointer:
                return "Pointer";
            default:
                return "Unknown";            
        }
    }

    struct OffsetInfo
    {
        uint64_t offset;
        uint64_t size;
    };
}
#endif
