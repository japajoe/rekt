#ifndef STACK_HPP
#define STACK_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include <type_traits>
#include <Instruction.hpp>
#include <Object.hpp>
#include <Utilities/MathUtility.hpp>

namespace VoltLang
{
    constexpr uint64_t VOLT_MIN_STACK_CAPACITY = 1024;

    class Stack
    {
    private:
        std::vector<unsigned char> buffer;
        std::vector<Type> types;
        uint64_t stackSize;
        uint64_t capacity;
        uint64_t stackIndex;
    public:
        Stack()
        {
            
        }

        Stack(uint64_t capacity)
        {
            capacity = MathUtility::NearestPowerOfTwo(capacity);

            if(capacity < VOLT_MIN_STACK_CAPACITY)
                capacity = VOLT_MIN_STACK_CAPACITY;

            this->capacity = capacity;
            stackSize = 0;
            stackIndex = 0;
            buffer.resize(capacity);
            types.resize(capacity / 8);
            memset(&buffer[0], 0, capacity);

            for (int i = 0; i < types.size(); i++)
            {
                types[i] = Type::Unknown;
            }
        }

        void Clear()
        {
            stackSize = 0;
            stackIndex = 0;
            memset(&buffer[0], 0, capacity);

            for (int i = 0; i < types.size(); i++)
            {
                types[i] = Type::Unknown;
            }
        }

        bool Push(unsigned char* data, Type type, uint64_t& stackOffset)
        {
            if(stackSize >= capacity)
            {
                return false;
            }

            if(type == Type::Pointer)
                memcpy(&buffer[stackSize], &data, sizeof(void *)); //Pointers have different size on x64 than x86
            else
                memcpy(&buffer[stackSize], data, sizeof(uint64_t)); //size of uint64_t is typically 8 bytes

            types[stackIndex] = type;
            stackSize += 8;
            stackIndex++;
            stackOffset = stackSize;

            return true;
        }

        template <typename T>
        bool Push(T* data, Type type, uint64_t& stackOffset)
        {
            //static_assert(/*Check for a type with an enum representation*/, "Type not allowed to be pushed in this manner (try using Push_pointer)");
            if (stackSize >= capacity)
            {
                return false;
            }

            if(type == Type::Pointer)
                memcpy(&buffer[stackSize], &data, sizeof(void *)); //Pointers have different size on x64 than x86
            else
                memcpy(&buffer[stackSize], data, sizeof(uint64_t)); //size of uint64_t is typically 8 bytes
            
            // if constexpr (std::is_pointer_v<T>)
            //     types[stackIndex] = Type::Pointer;
            // //List all valid types with their respective enums as separate "else if constexpr"s
            // else if constexpr (std::is_same_v<T, /*typename here*/>);

            types[stackIndex] = type;
            stackSize += 8;
            stackIndex++;
            stackOffset = stackSize;

            return true;
        }    

        bool PushDouble(double value, uint64_t& stackOffset)
        {
            //unsigned char *data = reinterpret_cast<unsigned char *>(&value);
            return Push<double>(&value, Type::Double, stackOffset);
        }

        bool PushInt64(int64_t value, uint64_t& stackOffset)
        {
            //unsigned char *data = reinterpret_cast<unsigned char *>(&value);
            return Push<int64_t>(&value, Type::Int64, stackOffset);
        }

        bool PushUInt64(uint64_t value, uint64_t& stackOffset)
        {
            //unsigned char *data = reinterpret_cast<unsigned char *>(&value);
            return Push<uint64_t>(&value, Type::UInt64, stackOffset);
        }

        bool PushString(char* value, uint64_t& stackOffset)
        {
            uintptr_t address = (uintptr_t)value;
            return Push<char>(value, Type::Pointer, stackOffset);
        }

        bool Pop(uint64_t& stackOffset)
        {
            if(stackSize < 8)
            {
                return false;
            }

            types[stackIndex-1] = Type::Unknown;

            stackSize -= 8;
            stackIndex--;
            stackOffset = stackSize;
            return true;
        }

        bool Pop(unsigned char* target, uint64_t& stackOffset)
        {
            if(stackSize < 8)
            {
                return false;
            }

            if(target != nullptr)
            {
                if(types[stackIndex -1] == Type::Pointer)
                    memcpy(target, &buffer[stackSize-8], sizeof(void *));
                else
                    memcpy(target, &buffer[stackSize-8], sizeof(uint64_t));
            }

            types[stackIndex-1] = Type::Unknown;

            stackSize -= 8;
            stackIndex--;
            stackOffset = stackSize;
            return true;
        }

        bool PopDouble(unsigned char* target, double& value, uint64_t& stackOffset)
        {
            if(Pop(target, stackOffset))
            {
                memcpy(&value, target, sizeof(double));
                return true;
            }

            return false;
        }

        bool PopUInt64(unsigned char* target, uint64_t& value, uint64_t& stackOffset)
        {
            if(Pop(target, stackOffset))
            {
                memcpy(&value, target, sizeof(uint64_t));
                return true;
            }

            return false;
        }

        bool PopInt64(unsigned char* target, int64_t& value, uint64_t& stackOffset)
        {
            if(Pop(target, stackOffset))
            {
                memcpy(&value, target, sizeof(int64_t));
                return true;
            }

            return false;
        }

        bool PopString(unsigned char* target, char* value, uint64_t stackOffset)
        {
            if(Pop(target, stackOffset))
            {
                value = GetDataAs<char>(target);
                return true;
            }

            return false;            
        }

        bool TryPopAsString(unsigned char* target, std::string& value, uint64_t& stackOffset)
        {
            Type type = GetTopType();

            switch(type)
            {
                case Type::Double:
                {
                    double v;
                    if (!PopDouble(target, v, stackOffset))
                        return false;

                    value = std::to_string(v);
                    return true;
                }
                case Type::UInt64:
                {
                    uint64_t v;
                    if(!PopUInt64(target, v, stackOffset))
                        return false;

                    value = std::to_string(v);
                    return true;
                }
                case Type::Int64:
                {
                    int64_t v;
                    if (!PopInt64(target, v, stackOffset))
                        return false;

                    value = std::to_string(v);
                    return true;
                }
                case Type::Pointer:
                {
                    if (!Pop(target, stackOffset))
                        return false;

                    char *ptr = GetDataAs<char>(target);

                    value = std::string(ptr);
                    return true;
                }
                default:
                    return false;
            }        
        }

        bool TryPopAsObject(unsigned char* target, ObjectBase& value, uint64_t& stackOffset)
        {
            Type type = GetTopType();

            switch(type)
            {
                case Type::Double:
                {
                    double v;
                    if (!PopDouble(target, v, stackOffset))
                        return false;

                    value.value.as_double = v;
                    value.type = ObjectType::Double;
                    return true;
                }
                case Type::UInt64:
                {
                    uint64_t v;
                    if(!PopUInt64(target, v, stackOffset))
                        return false;

                    value.value.as_uint64 = v;
                    value.type = ObjectType::UInt64;
                    return true;
                }
                case Type::Int64:
                {
                    int64_t v;
                    if (!PopInt64(target, v, stackOffset))
                        return false;

                    value.value.as_int64 = v;
                    value.type = ObjectType::Int64;
                    return true;
                }
                case Type::Pointer:
                {
                    if (!Pop(target, stackOffset))
                        return false;

                    char *ptr = GetDataAs<char>(target);

                    value.value.as_string = ptr;
                    value.type = ObjectType::String;
                    return true;
                }
                default:
                    return false;
            }        
        }         

        bool CheckType(Type type, int64_t index)
        {
            uint64_t i = stackIndex + index;

            if(i < 0 || i > ((capacity / 8) - 1))
                return false;

            return types[i] == type;
        }

        template<typename ...Param>
        bool CheckTypesTopToBottom(const Param& ... param)
        {
            int64_t i = 0;

            for(const auto p : {param...}) 
            {
                int64_t index = 0 - (i+1);

                Type type = static_cast<Type>(p);

                if(!CheckType(type, index))
                {
                    return false;
                }

                i++;
            }        

            return true;
        }

        template<typename ...Param>
        bool CheckTypesBottomToTop(const Param& ... param)
        {
            const std::size_t nArgs = sizeof...(Param);

            int64_t i = nArgs - 1;

            for(const auto p : {param...}) 
            {
                int64_t index = 0 - (i+1);

                Type type = static_cast<Type>(p);

                if(!CheckType(type, index))
                {
                    return false;
                }

                i--;
            }        

            return true;
        }

        unsigned char* GetBuffer()
        {
            return &buffer[0];
        }

        unsigned char* GetTop()
        {
            if(stackSize < 8)
            {
                return nullptr;
            }
            return &buffer[stackSize - 8];
        }

        Type GetTopType() const
        {
            if(stackIndex == 0)
                return Type::Unknown;
            return types[stackIndex - 1];
        }

        uint64_t GetCapacity() const
        {
            return capacity;
        }    

        uint64_t GetSize() const
        {
            return stackSize;
        }

        uint64_t GetCount() const
        {
            return stackIndex;
        }

        template<typename T>
        T* GetDataAs(unsigned char* src) 
        {
            uintptr_t ptr = *reinterpret_cast<uintptr_t*>(src);
            return reinterpret_cast<T*>(ptr);
        }    
    };
}
#endif
