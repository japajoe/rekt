#ifndef VOLT_OBJECT_HPP
#define VOLT_OBJECT_HPP

namespace VoltLang
{
    enum class ObjectType
    {
        Double,
        Int64,
        UInt64,
        String
    };
    
    class ObjectBase
    {
    public:
        ObjectType type;
        union
        {
            double as_double;
            int64_t as_int64;
            uint64_t as_uint64;
            char* as_string;
        } value;
    };

    class UInt64Object : public ObjectBase
    {
    public:
        UInt64Object(uint64_t value)
        {
            this->type = ObjectType::UInt64;
            this->value.as_uint64 = value;
        }
    };

    struct Int64Object : public ObjectBase
    {
    public:
        Int64Object(int64_t value)
        {
            this->type = ObjectType::Int64;
            this->value.as_int64 = value;
        }        
    };

    struct DoubleObject : public ObjectBase
    {
    public:
        DoubleObject(double value)
        {
            this->type = ObjectType::Double;
            this->value.as_double = value;
        }          
    };

    class StringObject : public ObjectBase
    {
    public:
        StringObject(char* value)
        {
            this->type = ObjectType::String;
            this->value.as_string = value;
        }         
    };
}
#endif