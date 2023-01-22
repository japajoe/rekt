#ifndef REKT_ASSEMBLY_HPP
#define REKT_ASSEMBLY_HPP

#include <vector>
#include <cstdint>
#include <map>
#include <string>
#include <iostream>
#include <Core/Specification.hpp>
#include <Utilities/Memory.hpp>

namespace REKT
{
    // class Assembly
    // {
    // public:
    //     std::vector<byte> data;
    //     std::vector<Instruction> instructions;
    //     std::map<std::string, uint64_t> symbols;
    //     std::map<std::string, OffsetInfo> offsets;
    //     std::map<std::string, Type> types;
    //     std::map<std::string, uint64_t> labels;
        
    //     void Clear()
    //     {
    //         data.clear();
    //         instructions.clear();
    //         labels.clear();
    //         offsets.clear();
    //         symbols.clear();
    //         types.clear();
    //     }

    //     void* GetDataPointer(const std::string& symbol, Type& type)
    //     {
    //         if(offsets.count(symbol) == 0)
    //             return nullptr;

    //         auto info = offsets[symbol];
    //         type = types[symbol];

    //         return &data[info.offset];
    //     }

    //     bool AddDataWithRange(const std::string& symbol, uint64_t size)
    //     {
    //         if(symbols.count(symbol))
    //             return false;

    //         uint64_t offset = data.size();

    //         symbols[symbol] = offset;
    //         types[symbol] = Type::CharPointer;

    //         size_t numBytes = size;
    //         numBytes += 1; //+1 for null terminator

    //         uint64_t neededSpace = Memory::GetSizeInWords(numBytes) * SIZE_OF_WORD;

    //         for (int i = 0; i < numBytes; i++)
    //             data.push_back((byte)0);
            
    //         data.push_back('\0');

    //         //Add padding if necessary
    //         if(neededSpace > numBytes)
    //         {
    //             uint64_t difference = neededSpace - numBytes;
    //             for (uint64_t i = 0; i < difference; i++)
    //                 data.push_back(static_cast<byte>(0));
    //         }

    //         offsets[symbol] = {offset, neededSpace};

    //         return true;
    //     }        

    //     bool AddData(const std::string& symbol, const std::string& value)
    //     {
    //         if(symbols.count(symbol))
    //             return false;

    //         uint64_t offset = data.size();

    //         symbols[symbol] = offset;
    //         types[symbol] = Type::CharPointer;

    //         auto bytes = Memory::GetBytes(value);
    //         size_t numBytes = bytes.size();

    //         numBytes += 1; //+1 for null terminator

    //         uint64_t neededSpace = Memory::GetSizeInWords(numBytes) * SIZE_OF_WORD;

    //         for (int i = 0; i < bytes.size(); i++)
    //             data.push_back(bytes[i]);

    //         data.push_back('\0');

    //         //Add padding if necessary
    //         if(neededSpace > numBytes)
    //         {
    //             uint64_t difference = neededSpace - numBytes;
    //             for (uint64_t i = 0; i < difference; i++)
    //                 data.push_back(static_cast<byte>(0));
    //         }

    //         offsets[symbol] = {offset, neededSpace};

    //         return true;
    //     }

    //     bool AddData(const std::string& symbol, byte value)
    //     {
    //         if(symbols.count(symbol))
    //             return false;

    //         uint64_t offset = data.size();

    //         symbols[symbol] = offset;
    //         types[symbol] = Type::UInt8Pointer;

    //         size_t numBytes = 1;
    //         uint64_t neededSpace = Memory::GetSizeInWords(1) * SIZE_OF_WORD;

    //         data.push_back(value);

    //         //Add padding if necessary
    //         if(neededSpace > 1)
    //         {
    //             uint64_t difference = neededSpace - numBytes;
    //             for (uint64_t i = 0; i < difference; i++)
    //                 data.push_back(static_cast<byte>(0));
    //         }

    //         offsets[symbol] = {offset, neededSpace};

    //         return true;
    //     }        

    //     bool AddData(const std::string& symbol, double value)
    //     {
    //         if(symbols.count(symbol))
    //             return false;

    //         uint64_t offset = data.size();

    //         symbols[symbol] = offset;
    //         types[symbol] = Type::DoublePointer;

    //         auto bytes = Memory::GetBytes(value);
    //         size_t numBytes = bytes.size();
    //         uint64_t neededSpace = Memory::GetSizeInWords(bytes.size()) * SIZE_OF_WORD;

    //         for (size_t i = 0; i < bytes.size(); i++)
    //             data.push_back(bytes[i]);

    //         //Add padding if necessary
    //         if(neededSpace > bytes.size())
    //         {
    //             uint64_t difference = neededSpace - numBytes;
    //             for (uint64_t i = 0; i < difference; i++)
    //                 data.push_back(static_cast<byte>(0));
    //         }

    //         offsets[symbol] = {offset, neededSpace};

    //         return true;
    //     }

    //     bool AddData(const std::string& symbol, int64_t value)
    //     {
    //         if(symbols.count(symbol))
    //             return false;

    //         uint64_t offset = data.size();

    //         symbols[symbol] = offset;
    //         types[symbol] = Type::Int64Pointer;

    //         auto bytes = Memory::GetBytes(value);
    //         size_t numBytes = bytes.size();
            
    //         uint64_t neededSpace = Memory::GetSizeInWords(bytes.size()) * SIZE_OF_WORD;

    //         for (size_t i = 0; i < bytes.size(); i++)
    //             data.push_back(bytes[i]);

    //         //Add padding if necessary
    //         if(neededSpace > bytes.size())
    //         {
    //             uint64_t difference = neededSpace - numBytes;
    //             for (uint64_t i = 0; i < difference; i++)
    //                 data.push_back(static_cast<byte>(0));
    //         }

    //         offsets[symbol] = {offset, neededSpace};

    //         return true;
    //     }

    //     bool AddData(const std::string& symbol, uint64_t value)
    //     {
    //         if(symbols.count(symbol))
    //             return false;

    //         uint64_t offset = data.size();

    //         symbols[symbol] = offset;
    //         types[symbol] = Type::UInt64Pointer;

    //         auto bytes = Memory::GetBytes(value);
    //         size_t numBytes = bytes.size();
            
    //         uint64_t neededSpace = Memory::GetSizeInWords(bytes.size()) * SIZE_OF_WORD;

    //         for (size_t i = 0; i < bytes.size(); i++)
    //             data.push_back(bytes[i]);

    //         //Add padding if necessary
    //         if(neededSpace > bytes.size())
    //         {
    //             uint64_t difference = neededSpace - numBytes;
    //             for (uint64_t i = 0; i < difference; i++)
    //                 data.push_back(static_cast<byte>(0));
    //         }

    //         offsets[symbol] = {offset, neededSpace};

    //         return true;
    //     }

    //     bool AddDataAsPointer(const std::string& symbol, uint64_t value)
    //     {
    //         if(symbols.count(symbol))
    //             return false;

    //         uint64_t offset = data.size();

    //         symbols[symbol] = offset;
    //         types[symbol] = Type::VoidPointer;

    //         auto bytes = Memory::GetBytes(value);
    //         size_t numBytes = bytes.size();
            
    //         uint64_t neededSpace = Memory::GetSizeInWords(bytes.size()) * SIZE_OF_WORD;

    //         for (size_t i = 0; i < bytes.size(); i++)
    //             data.push_back(bytes[i]);

    //         //Add padding if necessary
    //         if(neededSpace > bytes.size())
    //         {
    //             uint64_t difference = neededSpace - numBytes;
    //             for (uint64_t i = 0; i < difference; i++)
    //                 data.push_back(static_cast<byte>(0));
    //         }

    //         offsets[symbol] = {offset, neededSpace};

    //         return true;
    //     }

    //     bool AddLabel(const std::string& label, uint64_t location)
    //     {
    //         if(labels.count(label))
    //             return false;

    //         labels[label] = location;

    //         return true;
    //     }        
    // };

    class Assembly
    {
    public:
        std::vector<Object> data;
        std::vector<Instruction> instructions;
        std::map<std::string, uint64_t> symbols;
        std::map<std::string, OffsetInfo> offsets;
        std::map<std::string, Type> types;
        std::map<std::string, uint64_t> labels;

        ~Assembly()
        {
            Clear();
        }

        void Clear()
        {
            for(auto& item : offsets)
            {
                auto &o = item.second;
                if(data[o.offset].type == Type::CharPointer)
                {
                    if(o.isHeap && data[o.offset].as_char_pointer != nullptr)
                    {
                        delete[] data[o.offset].as_char_pointer;
                        data[o.offset].as_char_pointer = nullptr;
                    }
                }
            }

            data.clear();
            instructions.clear();
            labels.clear();
            offsets.clear();
            symbols.clear();
            types.clear();            
        }

        void* GetDataPointer(const std::string& symbol, Type& type)
        {
            if(offsets.count(symbol) == 0)
                return nullptr;

            auto info = offsets[symbol];
            type = types[symbol];

            return &data[info.offset];
        }

        bool AddDataWithRange(const std::string& symbol, uint64_t size)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();

            char *ptr = new char[size];
            memset(ptr, 0, size);

            data.emplace_back(ptr, Type::CharPointer);

            bool isHeap = true;

            offsets[symbol] = {offset, size, isHeap};
            symbols[symbol] = offset;
            types[symbol] = Type::CharPointer;            

            return true;
        }        

        bool AddData(const std::string& symbol, const std::string& value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();

            auto bytes = Memory::GetBytes(value);
            size_t numBytes = bytes.size() + 1; //+1 for null terminator

            uint64_t neededSpace = Memory::GetSizeInWords(numBytes) * SIZE_OF_WORD;

            char *ptr = new char[neededSpace];
            memset(ptr, 0, neededSpace);
            memcpy(ptr, &bytes[0], bytes.size());

            ptr[bytes.size()] = '\0';

            bool isHeap = true;

            data.emplace_back(ptr, Type::CharPointer);
            offsets[symbol] = {offset, neededSpace, isHeap};
            symbols[symbol] = offset;
            types[symbol] = Type::CharPointer;            

            return true;
        }   

        bool AddData(const std::string& symbol, double value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();
            bool isHeap = false;

            data.emplace_back(value);
            symbols[symbol] = offset;
            types[symbol] = Type::Double;
            offsets[symbol] = {offset, 8, isHeap};

            return true;
        }

        bool AddData(const std::string& symbol, int64_t value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();
            bool isHeap = false;

            data.emplace_back(value);
            symbols[symbol] = offset;
            types[symbol] = Type::Double;
            offsets[symbol] = {offset, 8, isHeap};

            return true;
        }

        bool AddData(const std::string& symbol, uint64_t value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();
            bool isHeap = false;

            data.emplace_back(value);
            symbols[symbol] = offset;
            types[symbol] = Type::Double;
            offsets[symbol] = {offset, 8, isHeap};

            return true;
        }

        bool AddDataAsPointer(const std::string& symbol, uint64_t value)
        {
            if(symbols.count(symbol))
                return false;

            uint64_t offset = data.size();
            bool isHeap = false;

            void *ptr = reinterpret_cast<void *>(value);
            
            data.emplace_back(ptr);
            symbols[symbol] = offset;
            types[symbol] = Type::VoidPointer;
            offsets[symbol] = {offset, 8, isHeap};

            return true;
        }

        bool AddLabel(const std::string& label, uint64_t location)
        {
            if(labels.count(label))
                return false;

            labels[label] = location;

            return true;
        }        
    };    
}
#endif