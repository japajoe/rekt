#ifndef STACK_HPP
#define STACK_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include <type_traits>
#include <Specification.hpp>
#include <MathUtility.hpp>

namespace VoltLang
{
    constexpr uint64_t VOLT_MIN_STACK_CAPACITY = 1024;

    template<typename T>
    class Stack
    {
    private:
        std::vector<T> buffer;
        uint64_t size;
        uint64_t stackIndex;
        uint64_t capacity;

    public:
        Stack(){}
        Stack(uint64_t capacity)
        {
            capacity = MathUtility::NearestPowerOfTwo(capacity);

            if(capacity < VOLT_MIN_STACK_CAPACITY)
                capacity = VOLT_MIN_STACK_CAPACITY;

            this->capacity = capacity;
            size = 0;
            stackIndex = 0;
            buffer.resize(capacity);
        }

        void Clear()
        {
            size = 0;
            stackIndex = 0;
        }

        uint64_t GetSize() const
        {
            return size;
        }

        uint64_t GetCapacity() const
        {
            return capacity;
        }

        Type GetTopType() const
        {
            if(size == 0)
                return Type::Undefined;
            return buffer[size - 1].type;
        }

        Object* GetTop() const
        {
            if(size < 1)
            {
                return nullptr;
            }
            return &buffer[size - 1];
        }

        bool Push(const T& item)
        {
            if(size >= capacity)
            {
                return false;
            }

            buffer[size] = item;
            size++;
            stackIndex++;
            return true;            
        }

        bool Pop(T& item)
        {
            if(size < 1)
            {
                return false;
            }            

            item = buffer[size - 1];
            size--;
            stackIndex--;
            return true;
        }

        bool Pop()
        {
            if(size < 1)
            {
                return false;
            }

            size--;
            stackIndex--;
            return true;
        }

        bool CheckType(Type type, int64_t index)
        {
            uint64_t i = stackIndex + index;

            if(i < 0 || i > (capacity  - 1))
                return false;

            return buffer[i].type == type;
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

    };
}
#endif