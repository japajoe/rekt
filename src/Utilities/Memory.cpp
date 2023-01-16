#include <Memory.hpp>
#include <cstring>

namespace VoltLang
{
    uint64_t Memory::GetSizeInWords(uint64_t sizeInBytes)
    {
        return (sizeInBytes + SIZE_OF_WORD - 1) / SIZE_OF_WORD;
    }

    std::vector<byte> Memory::GetBytes(const std::string& value)
    {
        std::vector<byte> bytes(value.begin(), value.end());
        return bytes;
    }

    std::vector<byte> Memory::GetBytes(double value)
    {
        std::vector<byte> bytes;
        bytes.resize(sizeof(double));
        memcpy(&bytes[0], &value, sizeof(double));
        return bytes;
    }

    std::vector<byte> Memory::GetBytes(int64_t value)
    {
        std::vector<byte> bytes;
        bytes.resize(sizeof(int64_t));
        memcpy(&bytes[0], &value, sizeof(int64_t));
        return bytes;
    }

    std::vector<byte> Memory::GetBytes(uint64_t value)
    {
        std::vector<byte> bytes;
        bytes.resize(sizeof(uint64_t));
        memcpy(&bytes[0], &value, sizeof(uint64_t));
        return bytes;
    }        
}