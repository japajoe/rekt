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
        std::map<std::string, uint64_t> labels;

        void SetData(const std::vector<unsigned char>& data)
        {
            this->data = data;
        }

        void SetInstructions(const std::vector<Instruction>& instructions)
        {
            this->instructions = instructions;
        }

        void SetSymbols(const std::map<std::string, uint64_t>& symbols)
        {
            this->symbols = symbols;
        }

        void SetOffsets(const std::map<std::string, OffsetInfo>& offsets)
        {
            this->offsets = offsets;
        }

        void SetTypes(const std::map<std::string, Type>& types)
        {
            this->types = types;
        }

        void SetLabels(const std::map<std::string, uint64_t>& labels)
        {
            this->labels = labels;
        }

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