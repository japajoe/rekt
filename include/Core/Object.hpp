#ifndef VOLT_OBJECT_HPP
#define VOLT_OBJECT_HPP

#include <Compilation/Specification.hpp>
#include <cstring>

namespace VoltLang
{
    enum class ObjectType : unsigned char
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
        String = 10,
        Pointer = 11,
        Unknown = 12
    };
    
    class Object
    {
    public:
        ObjectType type;
        union
        {
            int8_t as_int8;
            uint8_t as_uint8;
            int16_t as_int16;
            uint16_t as_uint16;            
            int32_t as_int32;
            uint32_t as_uint32;
            int64_t as_int64;
            uint64_t as_uint64;
            float as_float;
            double as_double;            
            char* as_string;
            void* as_pointer;
            unsigned char as_bytes[8];
        } value;

        Object(){}

        Object(double v)
        {
            this->value.as_double = v;
            this->type = ObjectType::Double;
        }

        Object(int64_t v)
        {
            this->value.as_int64 = v;
            this->type = ObjectType::Int64;
        }

        Object(uint64_t v)
        {
            this->value.as_uint64 = v;
            this->type = ObjectType::UInt64;
        }

        Object(char* v)
        {
            this->value.as_string = v;
            this->type = ObjectType::String;
        }

        Object(void* v)
        {
            this->value.as_pointer = v;
            this->type = ObjectType::Pointer;
        }

        Object(unsigned char* v, ObjectType type)
        {
            memcpy(value.as_bytes, v, sizeof(void *));
            this->type = type;
        }

    };
}
#endif