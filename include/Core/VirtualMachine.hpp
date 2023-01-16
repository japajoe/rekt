#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include <Utilities/ConversionUtility.hpp>
#include <Modules/Module.hpp>
#include <MathOperation.hpp>
#include <Specification.hpp>
#include <Assembly.hpp>
#include <Stack.hpp>
#include <vector>
#include <cstring>

namespace VoltLang
{
    constexpr uint64_t STACK_CAPACITY = 1024;
    constexpr uint64_t NUM_REGISTERS = 13;
    typedef int64_t MathOperationPtr(Object* lhs, Object* rhs);

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

    class VirtualMachine
    {
    private:
        Assembly *assembly;
        bool execute;
        uint64_t ip;
        int64_t compareFlag;
        int64_t zeroFlag;
        Object registers[NUM_REGISTERS];
        Stack<Object> stack;
        Stack<Object> internalStack;
    public:
        VirtualMachine(uint64_t stackCapacity = 0)
        {
            stackCapacity = MathUtility::NearestPowerOfTwo(stackCapacity);

            if(stackCapacity < VOLT_MIN_STACK_CAPACITY)
                stackCapacity = VOLT_MIN_STACK_CAPACITY;

            for (size_t i = 0; i < NUM_REGISTERS; i++)
            {
                registers[i] = Object();
                registers[i].type = Type::Int64;
                registers[i].as_int64 = 0;
            }

            if (stackCapacity == 0)
                stack = Stack<Object>(STACK_CAPACITY);
            else
                stack = Stack<Object>(stackCapacity);

            internalStack = Stack<Object>(STACK_CAPACITY);

            assembly = nullptr;
            compareFlag = 0;
            zeroFlag = 0;
        }

        Object* GetRegisters()
        {
            return &registers[0];
        }

        Stack<Object>* GetStack()
        {
            return &stack;
        }

        uint64_t GetRegisterCapacity() const
        {
            return NUM_REGISTERS;
        }

        int64_t GetCompareFlag() const
        {
            return compareFlag;
        }

        int64_t GetZeroFlag() const
        {
            return zeroFlag;
        }        

        /// @brief Resets the state of this machine. This will unload any loaded assembly.
        void Reset()
        {
            assembly = nullptr;
            ip = 0;
            execute = false;
            compareFlag = 0;
            zeroFlag = 0;

            stack.Clear();
            internalStack.Clear();

            for (size_t i = 0; i < NUM_REGISTERS; i++)
            {
                registers[i].type = Type::Int64;
                registers[i].as_int64 = 0;
            }            
        }

        /// @brief Resets the state of this VirtualMachine instance and loads the given assembly.
        /// @param assembly The assembly to load.
        /// @return True on success or false on failure.
        bool LoadAssembly(Assembly* assembly)
        {
            Reset();
            this->assembly = assembly;
            execute = this->assembly != nullptr;
            return execute;
        }

        void SetInstructionPointerOffset(uint64_t offset)
        {
            this->ip = offset;
        }       

        uint64_t GetInstructionPointer() const
        {
            return this->ip;
        }

        /// @brief Executes a single instruction of a loaded assembly and increments the instruction pointer.
        /// @return An ExecutionStatus telling whether the execution was successfull or not.
        ExecutionStatus Run()
        {
            if(assembly == nullptr)
                return ExecutionStatus::Error;

            if(execute == false)
                return ExecutionStatus::Error;            

            Instruction *instruction = &assembly->instructions[ip];

            switch(instruction->opcode)
            {
                case OpCode::PUSH:
                {
                    auto lhs = GetOperandPointer(&instruction->operands[0]);

                    if (!stack.Push(*lhs))
                    {
                        execute = false;
                        return ExecutionStatus::StackOverflow;
                    }

                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::POP:
                {
                    if(instruction->operands.size() == 0)
                    {
                        if(!stack.Pop())
                        {
                            execute = false;
                            return ExecutionStatus::StackUnderflow;
                        }
                    }
                    else
                    {
                        auto dst = GetOperandPointer(&instruction->operands[0]);

                        Object src;

                        if (!stack.Pop(src))
                        {
                            execute = false;
                            return ExecutionStatus::StackUnderflow;
                        }

                        if(instruction->operands[0].type == OperandType::Register)
                        {
                            *dst = src;
                        }
                        else
                        {
                            ConversionUtility::CastSourceToDestinationType(&src, dst, src.type, dst->type);
                        }                     
                    }

                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::MOV:
                {
                    auto lhs = GetOperandPointer(&instruction->operands[0]);
                    auto rhs = GetOperandPointer(&instruction->operands[1]);

                    if(instruction->operands[0].type == OperandType::Register)
                    {
                        *lhs = *rhs;
                    }
                    else
                    {
                        ConversionUtility::CastSourceToDestinationType(rhs, lhs, rhs->type, lhs->type);
                    }

                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::INC:
                {
                    auto lhs = GetOperandPointer(&instruction->operands[0]);
                    Object rhs((uint64_t)1);
                    zeroFlag = DoMathOperation(lhs, &rhs, MathOperation::Add);
                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::DEC:
                {
                    auto lhs = GetOperandPointer(&instruction->operands[0]);
                    Object rhs((uint64_t)1);
                    zeroFlag = DoMathOperation(lhs, &rhs, MathOperation::Subtract);
                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::ADD:
                {
                    auto lhs = GetOperandPointer(&instruction->operands[0]);
                    auto rhs = GetOperandPointer(&instruction->operands[1]);
                    zeroFlag = DoMathOperation(lhs, rhs, MathOperation::Add);
                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::SUB:
                {
                    auto lhs = GetOperandPointer(&instruction->operands[0]);
                    auto rhs = GetOperandPointer(&instruction->operands[1]);
                    zeroFlag = DoMathOperation(lhs, rhs, MathOperation::Subtract);
                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::MUL:
                {
                    auto lhs = GetOperandPointer(&instruction->operands[0]);
                    auto rhs = GetOperandPointer(&instruction->operands[1]);
                    zeroFlag = DoMathOperation(lhs, rhs, MathOperation::Multiply);
                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::DIV:
                {
                    auto lhs = GetOperandPointer(&instruction->operands[0]);
                    auto rhs = GetOperandPointer(&instruction->operands[1]);

                    if(lhs->as_void_pointer == 0 || rhs->as_void_pointer == 0)
                    {
                        execute = false;
                        return ExecutionStatus::DivisionByZero;
                    }

                    zeroFlag = DoMathOperation(lhs, rhs, MathOperation::Divide);
                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::CMP:
                {
                    auto lhs = GetOperandPointer(&instruction->operands[0]);
                    auto rhs = GetOperandPointer(&instruction->operands[1]);                    
                    compareFlag = DoMathOperation(lhs, rhs, MathOperation::Compare);
                    IncrementInstructionPointer();
                    break;
                }
                case OpCode::CALL:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if (instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        uint64_t returnAddress = ip + 1;

                        Object returnAdd(returnAddress);

                        if (!internalStack.Push(returnAdd))
                        {
                            execute = false;
                            std::cout << "CALL: Unable to push return address to internal stack at offset " << ip << std::endl;
                            return ExecutionStatus::StackOverflow;
                        }

                        SetInstructionPointer(obj->as_uint64);
                    }
                    else if(instruction->operands[0].type == OperandType::LabelToFunction)
                    {                        
                        VoltVMFunction func = reinterpret_cast<VoltVMFunction>(obj->as_void_pointer);
                        
                        int result = func(&stack);

                        if(result < 0)
                        {
                            std::string labelName;

                            if(Module::GetFunctionName(func, labelName))
                            {
                                std::cout << "CALL: Illegal operation at call to '" << labelName << "' at offset " << ip << std::endl;
                            }
                            else
                            {
                                std::cout << "CALL: Illegal operation at offset " << ip << std::endl;
                            }
                            
                            execute = false;                            
                            return ExecutionStatus::IllegalOperation;
                        }

                        IncrementInstructionPointer();
                    }
                    else
                    {
                        execute = false;
                        std::cout << "CALL: Illegal operation at offset " << ip << std::endl;
                        return ExecutionStatus::IllegalOperation;                        
                    }

                    break;
                }
                case OpCode::RET:
                {
                    Object obj;
                    if (!internalStack.Pop(obj))
                    {
                        execute = false;
                        std::cout << "RET: failed to get return address at offset " << ip << std::endl;
                        return ExecutionStatus::StackUnderflow;
                    }

                    SetInstructionPointer(obj.as_uint64);

                    break;
                }
                case OpCode::JMP:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        SetInstructionPointer(obj->as_uint64);
                    }
                    else
                    {
                        execute = false;
                        std::cout << "JMP: can't jump to offset" << obj->as_uint64 << std::endl;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    
                    break;
                }
                case OpCode::JG:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(compareFlag > 0)
                            SetInstructionPointer(obj->as_uint64);
                        else
                            IncrementInstructionPointer();
                    }
                    else
                    {
                        execute = false;
                        std::cout << "JG: can't jump to offset" << obj->as_uint64 << std::endl;
                        return ExecutionStatus::IllegalJump;
                    }

                    break;
                }
                case OpCode::JGE:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(compareFlag >= 0)
                            SetInstructionPointer(obj->as_uint64);
                        else
                            IncrementInstructionPointer();
                    }
                    else
                    {
                        execute = false;
                        std::cout << "JGE: can't jump to offset" << obj->as_uint64 << std::endl;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JL:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(compareFlag < 0)
                            SetInstructionPointer(obj->as_uint64);
                        else
                            IncrementInstructionPointer();
                    }
                    else
                    {
                        execute = false;
                        std::cout << "JL: can't jump to offset" << obj->as_uint64 << std::endl;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JLE:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(compareFlag <= 0)
                            SetInstructionPointer(obj->as_uint64);
                        else
                            IncrementInstructionPointer();
                    }
                    else
                    {
                        execute = false;
                        std::cout << "JLE: can't jump to offset" << obj->as_uint64 << std::endl;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JE:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(compareFlag == 0)
                            SetInstructionPointer(obj->as_uint64);
                        else
                            IncrementInstructionPointer();
                    }
                    else
                    {
                        execute = false;
                        std::cout << "JE: can't jump to offset" << obj->as_uint64 << std::endl;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JNE:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(compareFlag != 0)
                            SetInstructionPointer(obj->as_uint64);
                        else
                            IncrementInstructionPointer();
                    }
                    else
                    {
                        execute = false;
                        std::cout << "JNE: can't jump to offset" << obj->as_uint64 << std::endl;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JZ:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(zeroFlag != 0)
                            SetInstructionPointer(obj->as_uint64);
                        else
                            IncrementInstructionPointer();
                    }
                    else
                    {
                        execute = false;
                        std::cout << "JZ: can't jump to offset" << obj->as_uint64 << std::endl;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::JNZ:
                {
                    auto obj = GetOperandPointer(&instruction->operands[0]);

                    if(instruction->operands[0].type == OperandType::LabelToInstruction)
                    {
                        if(zeroFlag == 0)
                            SetInstructionPointer(obj->as_uint64);
                        else
                            IncrementInstructionPointer();
                    }
                    else
                    {
                        execute = false;
                        std::cout << "JNZ: can't jump to offset" << obj->as_uint64 << std::endl;
                        return ExecutionStatus::IllegalJump;
                    }                    
                    break;
                }
                case OpCode::HLT:
                {                    
                    execute = false;
                    return ExecutionStatus::Done;
                }
                case OpCode::NOP:
                {
                    IncrementInstructionPointer();
                    break;
                }
                default:
                {
                    execute = false;
                    return ExecutionStatus::NotImplemented;
                }
            }

            return ExecutionStatus::Ok;
        }

        /// @brief Sets the instruction pointer to the given offset and executes until a RET instruction is found.
        /// @param labelOffset The offset to jump to and start executing.
        /// @return An ExecutionStatus telling whether execution was successful or not.
        ExecutionStatus Call(uint64_t labelOffset)
        {
            if(assembly == nullptr)
                return ExecutionStatus::Error;

            if(labelOffset >= assembly->instructions.size())
                return ExecutionStatus::IllegalJump;

            //Return to last instruction (HLT) which compiler always adds automatically
            uint64_t returnAddress = assembly->instructions.size() - 1;

            Object obj(returnAddress);

            if(!internalStack.Push(obj))
            {
                return ExecutionStatus::StackOverflow;
            }

            SetInstructionPointer(labelOffset);

            ExecutionStatus status = ExecutionStatus::Ok;

            execute = true;
            
            while(status == ExecutionStatus::Ok)
            {
                status = Run();
            }

            return status;
        }
    private:
        inline Object* GetOperandPointer(Operand* operand)
        {
            switch (operand->type)
            {
                case OperandType::Register:
                    return &registers[operand->object.as_uint64];
                case OperandType::Data:
                case OperandType::LabelToInstruction:
                case OperandType::LabelToFunction:
                case OperandType::IntegerLiteral:
                case OperandType::FloatingPointLiteral:
                    return &operand->object;
                default:
                    return nullptr;
            }           
        }

        inline int64_t DoMathOperation(Object *lhs, Object *rhs, MathOperationPtr operation)
        {
            return operation(lhs, rhs);
        }

        inline void SetInstructionPointer(uint64_t offset)
        {
            ip = offset;
        }

        inline void IncrementInstructionPointer()
        {
            ip++;
        }
    };
}
#endif