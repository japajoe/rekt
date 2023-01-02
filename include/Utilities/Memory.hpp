#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include <string>

namespace VoltLang
{
    constexpr int SIZE_OF_WORD = static_cast<int>(sizeof(void *));

    class Memory
    {
    public:
        static std::vector<unsigned char> GetBytes(const std::string& value);
        static std::vector<unsigned char> GetBytes(double value);
        static std::vector<unsigned char> GetBytes(int64_t value);
        static std::vector<unsigned char> GetBytes(uint64_t value);
        static uint64_t GetSizeInWords(uint64_t sizeInBytes);
    };
}
#endif