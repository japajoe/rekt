#ifndef ASSEMBLY_HPP
#define ASSEMBLY_HPP

#include <vector>
#include <cstdint>
#include <Compilation/Instruction.hpp>
#include <iostream>

namespace VoltLang
{
    class Assembly
    {
    public:
        std::vector<unsigned char> data;
        std::vector<Instruction> instructions;
        std::map<std::string, uint64_t> symbols;
        std::map<std::string, OffsetInfo> offsets;
        std::map<std::string, Type> types;

        // unsigned char* GetDataAtOffset(uint64_t offset)
        // {
        //     return offset >= data.size() ? nullptr : &data[offset];
        // }

        template<typename T>
        T* GetDataAtOffset(uint64_t offset)
        {
            return offset >= data.size() ? nullptr : reinterpret_cast<T*>(&data[offset]);
        }

        unsigned char* GetDataAtOffset(uint64_t offset)
        {
            return offset >= data.size() ? nullptr : &data[offset];
        }     
    };
}
#endif