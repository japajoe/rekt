#ifndef REKT_SPECIFICATION_HPP
#define REKT_SPECIFICATION_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <Formatting/FMT.hpp>

namespace REKT
{
    typedef unsigned char byte;
    
    enum class OpCode : uint8_t
    {
        HLT = 0,
        PUSH,
        POP,
        MOV,
        INC,
        DEC,
        ADD,
        SUB,
        MUL,
        DIV,
        CMP,
        JMP,
        JG,
        JGE,
        JL,
        JLE,
        JE,
        JNE,
        JZ,
        JNZ,
        CALL,
        RET,
        NOP,
        NUM_OPCODES
    };

    //IMPORTANT: DO NOT MODIFY OR REORDER THIS ENUM OR BAD THINGS WILL HAPPEN
    //The values in this enum are used as indices into function tables (see MathOperation.cpp)
    enum Type
    {
        Int8Pointer,
        UInt8Pointer,
        Int16Pointer,
        UInt16Pointer,
        Int32Pointer,
        UInt32Pointer,
        Int64Pointer,
        UInt64Pointer,
        DoublePointer,               
        Int8,
        UInt8,
        Int16,
        UInt16,
        Int32,
        UInt32,
        Int64,
        UInt64,
        Double,
        CharPointer,
        VoidPointer,        
        Undefined
    };

    static std::string TypeToString(Type type)
    {
        switch(type)
        {
            case Type::Int8:
                return "Int8";
            case Type::UInt8:
                return "UInt8";
            case Type::Int16:
                return "Int16";
            case Type::UInt16:
                return "UInt16";
            case Type::Int32:
                return "Int32";
            case Type::UInt32:
                return "UInt32";
            case Type::Int64:
                return "Int64";
            case Type::UInt64:
                return "UInt64";
            case Type::Double:
                return "Double";
            case Type::Int8Pointer:
                return "Int8Pointer";
            case Type::UInt8Pointer:
                return "UInt8Pointer";
            case Type::Int16Pointer:
                return "Int16Pointer";
            case Type::UInt16Pointer:
                return "UInt16Pointer";
            case Type::Int32Pointer:
                return "Int32Pointer";
            case Type::UInt32Pointer:
                return "UInt32Pointer";
            case Type::Int64Pointer:
                return "Int64Pointer";
            case Type::UInt64Pointer:
                return "UInt64Pointer";
            case Type::DoublePointer:
                return "DoublePointer";
            case Type::CharPointer:
                return "CharPointer";
            case Type::VoidPointer:
                return "VoidPointer";
            case Type::Undefined:
            default:
                return "Undefined";
        }
    }

    enum class OperandType : uint8_t
    {
        Register,
        LabelToInstruction,
        LabelToFunction,
        Data,
        FloatingPointLiteral,
        IntegerLiteral
    };

    struct OffsetInfo
    {
        uint64_t offset; //The offset of the data in the data vector
        uint64_t size; //The size of the data in number of bytes
        bool isHeap; //Signifies whether memory is heap allocated or not (typically char* are)
    };

    class Object
    {
    public:
        Type type;
        union
        {
            uint8_t as_uint8;
            uint16_t as_uint16;
            uint32_t as_uint32;
            uint64_t as_uint64;
            int8_t as_int8;
            int16_t as_int16;
            int32_t as_int32;
            int64_t as_int64;
            double as_double;
            uint8_t *as_uint8_pointer;
            uint16_t *as_uint16_pointer;
            uint32_t *as_uint32_pointer;
            uint64_t *as_uint64_pointer;
            int8_t *as_int8_pointer;
            int16_t *as_int16_pointer;
            int32_t *as_int32_pointer;
            int64_t *as_int64_pointer;
            double *as_double_pointer;
            char *as_char_pointer;
            void *as_void_pointer;
        };

        Object() 
        {
            type = Type::Undefined;
        }

        Object(uint8_t value)
        {
            as_uint8 = value;
            type = Type::UInt8;
        }

        Object(uint16_t value)
        {
            as_uint16 = value;
            type = Type::UInt16;
        }

        Object(uint32_t value)
        {
            as_uint32 = value;
            type = Type::UInt32;
        }

        Object(uint64_t value)
        {
            as_uint64 = value;
            type = Type::UInt64;
        }

        Object(int8_t value)
        {
            as_int8 = value;
            type = Type::Int8;
        }

        Object(int16_t value)
        {
            as_int16 = value;
            type = Type::Int16;
        }

        Object(int32_t value)
        {
            as_int32 = value;
            type = Type::Int32;
        }

        Object(int64_t value)
        {
            as_int64 = value;
            type = Type::Int64;
        }

        Object(double value)
        {
            as_double = value;
            type = Type::Double;
        }

        Object(uint8_t *value)
        {
            as_uint8_pointer = value;
            type = Type::UInt8Pointer;
        }

        Object(uint16_t *value)
        {
            as_uint16_pointer = value;
            type = Type::UInt16Pointer;
        }

        Object(uint32_t *value)
        {
            as_uint32_pointer = value;
            type = Type::UInt32Pointer;
        }

        Object(uint64_t *value)
        {
            as_uint64_pointer = value;
            type = Type::UInt64Pointer;
        }

        Object(int8_t *value)
        {
            as_int8_pointer = value;
            type = Type::Int8Pointer;
        }

        Object(int16_t *value)
        {
            as_int16_pointer = value;
            type = Type::Int16Pointer;
        }

        Object(int32_t *value)
        {
            as_int32_pointer = value;
            type = Type::Int32Pointer;
        }

        Object(int64_t *value)
        {
            as_int64_pointer = value;
            type = Type::Int64Pointer;
        }

        Object(double *value)
        {
            as_double_pointer = value;
            type = Type::DoublePointer;
        }

        Object(char *value)
        {
            as_char_pointer = value;
            type = Type::CharPointer;
        }

        Object(void *value)
        {
            as_void_pointer = value;
            type = Type::VoidPointer;
        }

        Object(void *value, Type type)
        {
            as_void_pointer = value;
            this->type = type;
        }

        std::string ToString() const
        {
            switch(type)
            {
                case Type::Int8:
                    return std::to_string(as_int8);
                case Type::UInt8:
                    return std::to_string(as_uint8);
                case Type::Int16:
                    return std::to_string(as_int16);
                case Type::UInt16:
                    return std::to_string(as_uint16);
                case Type::Int32:
                    return std::to_string(as_int32);
                case Type::UInt32:
                    return std::to_string(as_uint32);
                case Type::Int64:
                    return std::to_string(as_int64);
                case Type::UInt64:
                    return std::to_string(as_uint64);
                case Type::Double:
                    return std::to_string(as_double);
                case Type::Int8Pointer:
                    return std::to_string(*as_int8_pointer);
                case Type::UInt8Pointer:
                    return std::to_string(*as_uint8_pointer);
                case Type::Int16Pointer:
                    return std::to_string(*as_int16_pointer);
                case Type::UInt16Pointer:
                    return std::to_string(*as_uint16_pointer);
                case Type::Int32Pointer:
                    return std::to_string(*as_int32_pointer);
                case Type::UInt32Pointer:
                    return std::to_string(*as_uint32_pointer);
                case Type::Int64Pointer:
                    return std::to_string(*as_int64_pointer);
                case Type::UInt64Pointer:
                    return std::to_string(*as_uint64_pointer);
                case Type::DoublePointer:
                    return std::to_string(*as_double_pointer);
                case Type::CharPointer:
                    return std::string(as_char_pointer);
                case Type::VoidPointer:
                    return fmt::format("{:p}", as_void_pointer);
                case Type::Undefined:
                default:
                    return std::string("Type::Undefined");
            }
        }

        bool IsPointerType() const
        {
            switch(type)
            {
                case Int8Pointer:
                case UInt8Pointer:
                case Int16Pointer:
                case UInt16Pointer:
                case Int32Pointer:
                case UInt32Pointer:
                case Int64Pointer:
                case UInt64Pointer:
                case DoublePointer:               
                case CharPointer:
                case VoidPointer:
                    return true;
                default:
                    return false;
            }
        }

        bool IsNumericType() const
        {
            switch(type)
            {
                case Int8:
                case UInt8:
                case Int16:
                case UInt16:
                case Int32:
                case UInt32:
                case Int64:
                case UInt64:
                case Double:               
                    return true;
                default:
                    return false;
            }
        }        

        template<typename T>
        T GetValueAs()
        {
            return reinterpret_cast<T>(as_void_pointer);
        }

        double GetValueAsDouble()
        {
            double value = 0;
            switch (type)
            {
                case Type::Int64:
                    value = static_cast<double>(as_int64);
                    break;
                case Type::UInt64:
                    value = static_cast<double>(as_uint64);
                    break;
                case Type::Int64Pointer:
                    value = static_cast<double>(*as_int64_pointer);
                    break;
                case Type::UInt64Pointer:
                    value = static_cast<double>(*as_uint64_pointer);
                    break;
                case Type::Double:
                    value = as_double;
                    break;
                case Type::DoublePointer:
                    value = *as_double_pointer;
                    break;                                
                default:
                    return 0;
            }

            return value;
        }
    };

    class Operand
    {
    public:
        Object object;
        OperandType type;
        Operand() {}
        Operand(const Object& object, OperandType type)
        {
            this->object = object;
            this->type = type;
        }
    };

    class Instruction
    {
    public:
        OpCode opcode;
        std::vector<Operand> operands;

        Instruction(OpCode opcode)
        {
            this->opcode = opcode;
        }

        Instruction(OpCode opcode, const std::vector<Operand>& operands)
        {
            this->opcode = opcode;
            this->operands = operands;
        }
    };
}
#endif