#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include <Compilation/Instruction.hpp>
#include <MathOperation.hpp>
#include <StandardLibrary.hpp>
#include <Assembly.hpp>
#include <Stack.hpp>
#include <vector>
#include <cstring>

constexpr uint64_t STACK_CAPACITY = 1024 * 8;
constexpr uint64_t NUM_REGISTERS = 13;
constexpr uint64_t REGISTER_CAPACITY = NUM_REGISTERS * 8;

namespace VoltLang
{
    enum class ExecutionStatus : int
    {
        Ok = 0,
        Done,
        IllegalOperation,
        IllegalJump,
        StackOverflow,
        StackUnderflow,
        DivisionByZero,
        NotImplemented,
        Error
    };

    typedef void MathOperationPtr(byte* lhs, byte* rhs, Type lhsDataType, Type rhsDataType);

    class VirtualMachine
    {
    private:
        uint64_t ip;
        uint64_t returnAddress;
        Assembly *assembly;
        bool execute;
        unsigned char registers[REGISTER_CAPACITY];
        Type registerType[NUM_REGISTERS];
        Stack stack;

        MathOperationPtr mathOperationAdd;
        MathOperationPtr mathOperationSub;
        MathOperationPtr mathOperationMul;
        MathOperationPtr mathOperationDiv;

    public:
        VirtualMachine(uint64_t stackCapacity = 0)
        {
            memset(&registers[0], 0, REGISTER_CAPACITY);
            
            if(stackCapacity == 0)
                stack = Stack(STACK_CAPACITY);
            else
                stack = Stack(stackCapacity);

            for (size_t i = 0; i < NUM_REGISTERS; i++)
            {
                registerType[i] = Type::Unknown;
            }
        }

        unsigned char* GetRegisters()
        {
            return &registers[0];
        }

        uint64_t GetRegisterCapacity() const
        {
            return REGISTER_CAPACITY;
        }

        void Reset()
        {
            assembly = nullptr;
            ip = 0;
            returnAddress = 0;
            execute = false;
            memset(&registers[0], 0, REGISTER_CAPACITY);
            for (size_t i = 0; i < NUM_REGISTERS; i++)
            {
                registerType[i] = Type::Unknown;
            }
        }

        bool LoadAssembly(Assembly* assembly)
        {
            Reset();
            this->assembly = assembly;
            execute = this->assembly != nullptr;
            return execute;
        }

        ExecutionStatus Run()
        {
            if(assembly == nullptr)
                return ExecutionStatus::Error;

            if(execute == false)
                return ExecutionStatus::Error;            

            Instruction *instruction = &assembly->instructions[ip];

            switch(instruction->opcode)
            {
                case OpCode::Push:
                {
                    unsigned char* lhs = GetOperandPointer(&instruction->operands[0]);

                    if(lhs == nullptr)
                    {
                        execute = false;
                        std::cout << "Push: Illegal operation\n";
                        return ExecutionStatus::IllegalOperation;
                    }

                    if (instruction->operands[0].type == OperandType::Register)
                    {
                        uint64_t registerIndex = GetRegisterIndex(&instruction->operands[0]);
                        Type type = registerType[registerIndex];
                        uint64_t stackOffset = 0;
                        if(!stack.Push(lhs, type, stackOffset))
                        {
                            execute = false;
                            return ExecutionStatus::StackOverflow;
                        }                    
                    }
                    else
                    {
                        uint64_t stackOffset = 0;

                        if(!stack.Push(lhs, instruction->operands[0].valueType, stackOffset))
                        {
                            execute = false;
                            return ExecutionStatus::StackOverflow;
                        }
                    }

                    ip++;

                    break;
                }
                case OpCode::Pop:
                {
                    if(instruction->operands.size() > 0)
                    {
                        unsigned char* lhs = GetOperandPointer(&instruction->operands[0]);

                        uint64_t stackOffset = 0;

                        Type type = stack.GetTopType();

                        if (!stack.Pop(lhs, stackOffset))
                        {
                            execute = false;
                            std::cout << "Pop: Illegal operation\n";
                            return ExecutionStatus::StackUnderflow;
                        }

                        if (lhs != nullptr)
                        {
                            if (instruction->operands[0].type == OperandType::Register)
                            {
                                uint64_t registerIndex = GetRegisterIndex(&instruction->operands[0]);
                                //registerType[registerIndex] = instruction->operands[0].valueType;
                                registerType[registerIndex] = type;

                                //std::cout << "Register index: " << registerIndex << " Type: " << (int)type << std::endl;
                            }
                        }                        
                    }
                    else
                    {
                        uint64_t stackOffset;
                        if (!stack.Pop(nullptr, stackOffset))
                        {
                            execute = false;
                            return ExecutionStatus::StackUnderflow;
                        }
                    }                
                    
                    ip++;

                    break;
                }
                case OpCode::Move:
                {
                    unsigned char* lhs = GetOperandPointer(&instruction->operands[0]);
                    unsigned char* rhs = GetOperandPointer(&instruction->operands[1]);

                    if(lhs == nullptr || rhs == nullptr)
                    {
                        execute = false;
                        std::cout << "MOV: Illegal operation\n";
                        return ExecutionStatus::IllegalOperation;
                    }

                    if(instruction->operands[1].valueType == Type::Pointer)
                        memcpy(lhs, &rhs, sizeof(void *));
                    else
                        memcpy(lhs, rhs, sizeof(uint64_t));

                    if(instruction->operands[0].type == OperandType::Register)
                    {
                        uint64_t registerIndexLHS = GetRegisterIndex(&instruction->operands[0]);

                        if(instruction->operands[1].type == OperandType::Register)
                        {
                            uint64_t registerIndexRHS = GetRegisterIndex(&instruction->operands[1]);
                            registerType[registerIndexLHS] = registerType[registerIndexRHS];
                        }
                        else
                        {
                            registerType[registerIndexLHS] = instruction->operands[1].valueType;
                        }
                    }

                    ip++;
                    break;
                }
                case OpCode::Increment:
                {
                    unsigned char* lhs = GetOperandPointer(&instruction->operands[0]);
                    uint64_t value = 1;
                    unsigned char* valuePtr = reinterpret_cast<unsigned char *>(&value);

                    Type type = GetOperandValueType(&instruction->operands[0]);
                    MathOperation::Add(lhs, valuePtr, type, Type::UInt64);
                    ip++;
                    break;
                }
                case OpCode::Decrement:
                {
                    unsigned char* lhs = GetOperandPointer(&instruction->operands[0]);
                    uint64_t value = 1;
                    unsigned char* valuePtr = reinterpret_cast<unsigned char *>(&value);

                    Type type = GetOperandValueType(&instruction->operands[0]);
                    MathOperation::Subtract(lhs, valuePtr, type, Type::UInt64);
                    ip++;                    
                    break;
                }
                case OpCode::Add:
                {
                    DoMathOperation(&instruction->operands[0], &instruction->operands[1], MathOperation::Add);                
                    ip++;
                    break;
                }
                case OpCode::Subtract:
                {
                    DoMathOperation(&instruction->operands[0], &instruction->operands[1], MathOperation::Subtract);
                    ip++;
                    break;
                }
                case OpCode::Multiply:
                {
                    DoMathOperation(&instruction->operands[0], &instruction->operands[1], MathOperation::Multiply);
                    ip++;
                    break;
                }
                case OpCode::Divide:
                {
                    unsigned char* lhs = GetOperandPointer(&instruction->operands[0]);
                    unsigned char* rhs = GetOperandPointer(&instruction->operands[1]);

                    uint64_t vl = *reinterpret_cast<uint64_t *>(lhs);
                    uint64_t vr = *reinterpret_cast<uint64_t *>(rhs);

                    if(vl == 0 || vr == 0)
                    {
                        execute = false;
                        return ExecutionStatus::DivisionByZero;
                    }

                    DoMathOperation(&instruction->operands[0], &instruction->operands[1], MathOperation::Divide);
                    ip++;
                    break;
                }              
                case OpCode::Compare:
                {
                    DoMathOperation(&instruction->operands[0], &instruction->operands[1], MathOperation::Compare);
                    ip++;
                    break;
                }
                case OpCode::Call:
                {                    
                    unsigned char *lhs = GetOperandPointer(&instruction->operands[0]);
                    uintptr_t address = *reinterpret_cast<uintptr_t*>(lhs);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        returnAddress = ip + 1;
                        ip = address;
                    }
                    else
                    {
                        VoltVMFunction func = reinterpret_cast<VoltVMFunction>(address);
                        
                        int result = func(&stack);

                        if(result < 0)
                        {
                            execute = false;
                            std::cout << "Call: Illegal operation\n";
                            return ExecutionStatus::IllegalOperation;                            
                        }

                        ip++;
                    }

                    break;
                }
                case OpCode::Jump:
                {
                    unsigned char *lhs = GetOperandPointer(&instruction->operands[0]);
                    uintptr_t address = *reinterpret_cast<uintptr_t*>(lhs);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        ip = address;
                    }
                    else
                    {
                        execute = false;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JumpIfGreaterThan:
                {
                    unsigned char *lhs = GetOperandPointer(&instruction->operands[0]);
                    uintptr_t address = *reinterpret_cast<uintptr_t*>(lhs);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(MathOperation::GetCompareFlag() > 0)
                        {
                            ip = address;
                        }
                        else
                        {
                            ip++;
                        }
                    }
                    else
                    {
                        execute = false;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JumpIfGreaterThanOrEqual:
                {
                    unsigned char *lhs = GetOperandPointer(&instruction->operands[0]);
                    uintptr_t address = *reinterpret_cast<uintptr_t*>(lhs);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(MathOperation::GetCompareFlag() >= 0)
                        {
                            ip = address;
                        }
                        else
                        {
                            ip++;
                        }
                    }
                    else
                    {
                        execute = false;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JumpIfLessThan:
                {
                    unsigned char *lhs = GetOperandPointer(&instruction->operands[0]);
                    uintptr_t address = *reinterpret_cast<uintptr_t*>(lhs);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(MathOperation::GetCompareFlag() < 0)
                        {
                            ip = address;
                        }
                        else
                        {
                            ip++;
                        }
                    }
                    else
                    {
                        execute = false;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JumpIfLessThanOrEqual:
                {
                    unsigned char *lhs = GetOperandPointer(&instruction->operands[0]);
                    uintptr_t address = *reinterpret_cast<uintptr_t*>(lhs);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(MathOperation::GetCompareFlag() <= 0)
                        {
                            ip = address;
                        }
                        else
                        {
                            ip++;
                        }
                    }
                    else
                    {
                        execute = false;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JumpIfEqual:
                {
                    unsigned char *lhs = GetOperandPointer(&instruction->operands[0]);
                    uintptr_t address = *reinterpret_cast<uintptr_t*>(lhs);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(MathOperation::GetCompareFlag() == 0)
                        {
                            ip = address;
                        }
                        else
                        {
                            ip++;
                        }
                    }
                    else
                    {
                        execute = false;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JumpIfZero:
                {
                    unsigned char *lhs = GetOperandPointer(&instruction->operands[0]);
                    uintptr_t address = *reinterpret_cast<uintptr_t*>(lhs);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(MathOperation::GetZeroFlag() == 0)
                        {
                            ip = address;
                        }
                        else
                        {
                            ip++;
                        }
                    }
                    else
                    {
                        execute = false;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JumpIfNotZero:       
                {
                    unsigned char *lhs = GetOperandPointer(&instruction->operands[0]);
                    uintptr_t address = *reinterpret_cast<uintptr_t*>(lhs);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(MathOperation::GetZeroFlag() != 0)
                        {
                            ip = address;
                        }
                        else
                        {
                            ip++;
                        }
                    }
                    else
                    {
                        execute = false;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::Return:
                {
                    ip = returnAddress;
                    break;
                }
                case OpCode::Halt:
                {
                    execute = false;
                    return ExecutionStatus::Done;
                }
                default:
                {
                    execute = false;
                    return ExecutionStatus::NotImplemented;
                }
            }

            return ExecutionStatus::Ok;
        }

        void DoMathOperation(Operand *olhs, Operand *orhs, MathOperationPtr operation)
        {
            unsigned char* lhs = GetOperandPointer(olhs);
            unsigned char* rhs = GetOperandPointer(orhs);
            if(olhs->type == OperandType::Register)
            {
                Type typeLeft = GetOperandValueType(olhs);

                if(orhs->type == OperandType::Register)
                {
                    Type typeRight = GetOperandValueType(orhs);
                    operation(lhs, rhs, typeLeft, typeRight);
                }
                else
                {
                    operation(lhs, rhs, typeLeft, orhs->valueType);
                }
            }
            else
            {
                if(orhs->type == OperandType::Register)
                {
                    Type typeRight = GetOperandValueType(orhs);
                    operation(lhs, rhs, olhs->valueType, typeRight);
                }
                else
                {
                    operation(lhs, rhs, olhs->valueType, orhs->valueType);
                }
            }
        }    

        uint64_t GetRegisterIndex(Operand* operand)
        {
            return operand->GetValue<uint64_t>();
        }

        unsigned char* GetOperandPointer(Operand* operand)
        {
            switch (operand->type)
            {
                case OperandType::Register:
                    return &registers[0] + (operand->GetValue<uint64_t>() * sizeof(unsigned char) * 8);
                case OperandType::Data:
                    return assembly->GetDataAtOffset(operand->GetValue<uint64_t>());
                    //return assembly->GetDataAtOffset<unsigned char>(operand->GetValue<uint64_t>());
                case OperandType::LabelToInstruction:
                case OperandType::LabelToFunction:
                    return &operand->data[0];
                case OperandType::IntegerLiteral:
                    return &operand->data[0];
                case OperandType::FloatingPointLiteral:
                    return &operand->data[0];
                default:
                    return nullptr;
            }
        }

        Type GetOperandValueType(Operand* operand)
        {
            if(operand->type == OperandType::Register)
            {
                uint64_t registerIndex = GetRegisterIndex(operand);
                return registerType[registerIndex];
            }
            else
            {
                return operand->valueType;
            }
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
