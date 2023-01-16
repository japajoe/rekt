#ifndef VOLT_MEMORY_HPP
#define VOLT_MEMORY_HPP

#include <cstdint>
#include <Specification.hpp>
#include <vector>
#include <string>

namespace VoltLang
{
    constexpr int SIZE_OF_WORD = static_cast<int>(sizeof(void *));

    class Memory
    {
    public:
        static uint64_t GetSizeInWords(uint64_t sizeInBytes);
        static std::vector<byte> GetBytes(const std::string& value);
        static std::vector<byte> GetBytes(double value);
        static std::vector<byte> GetBytes(int64_t value);
        static std::vector<byte> GetBytes(uint64_t value);        
    };
}

#endif