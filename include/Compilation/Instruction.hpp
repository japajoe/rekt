#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <OpCode.hpp>
#include <Specification.hpp>
#include <cstring>
#include <vector>
#include <cstdint>
#include <iostream>

namespace VoltLang
{
    class Operand
    {
    public:
        OperandType type;
        Type valueType;
        unsigned char data[8];

        Operand()
        {
            
        }

        Operand(OperandType type)
        {
            this->type = type;
            this->valueType = Type::UInt8;
            memset(data, 0, 8);
        }

        Operand(OperandType type, Type valueType, unsigned char value)
        {
            this->type = type;
            this->valueType = valueType;
            memset(data, 0, 8);
            memcpy(&data[0], &value, sizeof(unsigned char));
        }

        Operand(OperandType type, Type valueType, char value)
        {
            this->type = type;
            this->valueType = valueType;
            memset(data, 0, 8);
            memcpy(&data[0], &value, sizeof(char));
        }

        Operand(OperandType type, Type valueType, uint64_t value)
        {
            this->type = type;
            this->valueType = valueType;
            memset(data, 0, 8);
            memcpy(&data[0], &value, sizeof(uint64_t));
        }

        Operand(OperandType type, Type valueType, int64_t value)
        {
            this->type = type;
            this->valueType = valueType;
            memset(data, 0, 8);
            memcpy(&data[0], &value, sizeof(int64_t));
        }

        Operand(OperandType type, Type valueType, double value)
        {
            this->type = type;
            this->valueType = valueType;
            memset(data, 0, 8);
            memcpy(&data[0], &value, sizeof(double));
        }

        template<typename T>
        T GetValue() const
        {
            T value;
            memcpy(&value, &data[0], sizeof(T));        
            return value;
        } 
    };

    class Instruction
    {
    private:
        size_t numOperands;
    public:
        OpCode opcode;
        std::vector<Operand> operands;

        Instruction(OpCode opcode, const std::vector<Operand>& operands)
        {
            this->opcode = opcode;
            this->operands = operands;
        }
    };
}
#endif