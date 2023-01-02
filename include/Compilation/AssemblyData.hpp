#ifndef ASSEMBLYDATA_HPP
#define ASSEMBLYDATA_HPP

#include <vector>
#include <map>
#include <string>
#include <Memory.hpp>
#include <Instruction.hpp>

namespace VoltLang
{
    class AssemblyData
    {
    public:
        std::vector<unsigned char> data;
        std::map<std::string, uint64_t> symbols;
        std::map<std::string, OffsetInfo> offsets;
        std::map<std::string, Type> types;

        bool Add(const std::string& symbol, const std::string& value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();

            symbols[symbol] = offset;
            types[symbol] = Type::Pointer;

            auto bytes = Memory::GetBytes(value);
            size_t numBytes = bytes.size();

            numBytes += 1; //+1 for null terminator

            uint64_t neededSpace = Memory::GetSizeInWords(numBytes) * SIZE_OF_WORD;

            for (int i = 0; i < bytes.size(); i++)
                data.push_back(bytes[i]);

            data.push_back('\0');

            //Add padding if necessary
            if(neededSpace > numBytes)
            {
                uint64_t difference = neededSpace - numBytes;
                for (uint64_t i = 0; i < difference; i++)
                    data.push_back(static_cast<unsigned char>(0));
            }

            offsets[symbol] = {offset, neededSpace};

            return true;
        }

        bool Add(const std::string& symbol, unsigned char value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();

            symbols[symbol] = offset;
            types[symbol] = Type::UInt8;

            size_t numBytes = 1;
            uint64_t neededSpace = Memory::GetSizeInWords(1) * SIZE_OF_WORD;

            data.push_back(value);

            //Add padding if necessary
            if(neededSpace > 1)
            {
                uint64_t difference = neededSpace - numBytes;
                for (uint64_t i = 0; i < difference; i++)
                    data.push_back(static_cast<unsigned char>(0));
            }

            offsets[symbol] = {offset, neededSpace};

            return true;
        }

        bool Add(const std::string& symbol, double value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();

            symbols[symbol] = offset;
            types[symbol] = Type::Double;

            auto bytes = Memory::GetBytes(value);
            size_t numBytes = bytes.size();
            uint64_t neededSpace = Memory::GetSizeInWords(bytes.size()) * SIZE_OF_WORD;

            for (size_t i = 0; i < bytes.size(); i++)
                data.push_back(bytes[i]);

            //Add padding if necessary
            if(neededSpace > bytes.size())
            {
                uint64_t difference = neededSpace - numBytes;
                for (uint64_t i = 0; i < difference; i++)
                    data.push_back(static_cast<unsigned char>(0));
            }

            offsets[symbol] = {offset, neededSpace};

            return true;
        }

        bool Add(const std::string& symbol, int64_t value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();

            symbols[symbol] = offset;
            types[symbol] = Type::Int64;

            auto bytes = Memory::GetBytes(value);
            size_t numBytes = bytes.size();
            
            uint64_t neededSpace = Memory::GetSizeInWords(bytes.size()) * SIZE_OF_WORD;

            for (size_t i = 0; i < bytes.size(); i++)
                data.push_back(bytes[i]);

            //Add padding if necessary
            if(neededSpace > bytes.size())
            {
                uint64_t difference = neededSpace - numBytes;
                for (uint64_t i = 0; i < difference; i++)
                    data.push_back(static_cast<unsigned char>(0));
            }

            offsets[symbol] = {offset, neededSpace};

            return true;
        }

        bool Add(const std::string& symbol, uint64_t value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();

            symbols[symbol] = offset;
            types[symbol] = Type::UInt64;

            auto bytes = Memory::GetBytes(value);
            size_t numBytes = bytes.size();
            
            uint64_t neededSpace = Memory::GetSizeInWords(bytes.size()) * SIZE_OF_WORD;

            for (size_t i = 0; i < bytes.size(); i++)
                data.push_back(bytes[i]);

            //Add padding if necessary
            if(neededSpace > bytes.size())
            {
                uint64_t difference = neededSpace - numBytes;
                for (uint64_t i = 0; i < difference; i++)
                    data.push_back(static_cast<unsigned char>(0));
            }

            offsets[symbol] = {offset, neededSpace};

            return true;
        }    
    };
}
#endif