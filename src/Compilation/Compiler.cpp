#include <Compiler.hpp>
#include <Modules/Module.hpp>

namespace VoltLang
{
    Compiler::Compiler()
    {
        registers["eax"] = 0;
        registers["ebx"] = 1;
        registers["ecx"] = 2;
        registers["edx"] = 3;
        registers["ebp"] = 4;
        registers["esp"] = 5;
        registers["edi"] = 6;
        registers["eip"] = 7;
        registers["esi"] = 8;
        registers["rax"] = 9;
        registers["rbx"] = 10;
        registers["rcx"] = 11;
        registers["rdx"] = 12;     
    }

    bool Compiler::Compile(const std::string& source, Assembly* assembly)
    {
        assembly->Clear();

        compilationStage = CompilationStage::None;

        // Tokenizes the input string and returns a std::vector<std::vector<Token<TokenType>>>
        // This way we can process the source line by line. This also means none of our instructions or declarations
        // are allowed to be defined over the span of multiple lines.
        auto tokens = GetTokens(source);

        uint64_t numInstructions = 0;

        //Registers any data and labels
        for (size_t i = 0; i < tokens.size(); i++)
        {
            GetData(tokens[i], *assembly);
            GetLabels(tokens[i], *assembly);
        }        

        //Once all labels are found, count instructions and determine to which instruction a label points towards
        for (size_t i = 0; i < tokens.size(); i++)
        {
            GetLabelPointer(tokens[i], numInstructions, *assembly);
        }

        // Finally create all instructions
        for (size_t i = 0; i < tokens.size(); i++)
        {
            if (!GetInstructions(tokens[i], *assembly, assembly->instructions))
            {
                return false;
            }
        }

        assembly->instructions.push_back(Instruction(OpCode::HLT, {}));
        compilationStage = CompilationStage::None;

        return true;
    }

    TokenList Compiler::GetTokens(const std::string& source)
    {
        TokenList tokenList;

        auto lines = StringUtility::Split(source, '\n');

        for (size_t i = 0; i < lines.size(); i++)
        {
            //Strip comment
            if (StringUtility::Contains(lines[i], ";;"))
            {
                for (int j = lines[i].size() -1; j > 0; j--)
                {
                    if (lines[i][j] == ';' && j >= 1)
                    {
                        if (lines[i][j - 1] == ';')
                        {
                            size_t index = j -1;
                            lines[i].resize(index);
                        }
                    }
                }
            }

            auto tokens = tokenizer.Parse(lines[i]);
            
            if (tokens.size() == 0)
                continue;

            uint64_t lineNumber = static_cast<uint64_t>(i + 1);

            for (size_t j = 0; j < tokens.size(); j++)
            {
                tokens[j].lineNumber = lineNumber;                
            }           

            for (std::vector<Token<TokenType>>::iterator it = tokens.end() - 1; it != tokens.begin() - 1; it--)
            {
                if(it->text.size() == 0) 
                {
                    it = tokens.erase(it);
                }
            }

            if(tokens.size() > 0)
                tokenList.push_back(tokens);
        }

        return tokenList;
    }

    bool Compiler::GetData(const std::vector<Token<TokenType>> &tokens, Assembly& assembly)
    {
        size_t numParameters = tokens.size() - 1;

        switch (tokens[0].type)
        {
            case TokenType::Identifier:
                if (!AssertParameterCount(tokens, 3))
                {
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::DB, TokenType::Colon, TokenType::StringLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::DB, TokenType::Colon, TokenType::IntegerLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::DQ, TokenType::Colon, TokenType::IntegerLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::DQ, TokenType::Colon, TokenType::FloatingPointLiteral ))
                {
                    if (tokens[1].type == TokenType::DB)
                    {
                        if (tokens[3].type == TokenType::StringLiteral)
                        {
                            if (!assembly.AddData(tokens[0].text, tokens[3].text))
                            {
                                LogError(CompilationError::DuplicateDeclaration, "", tokens[0].lineNumber);
                                return false;
                            }
                        }
                        else
                        {
                            //Instead of allocating space for a string, allocate x number of bytes
                            uint64_t numBytesToAllocate;
                            if(!StringUtility::ParseNumberLexical<uint64_t>(tokens[3].text, numBytesToAllocate))
                            {
                                LogError(CompilationError::ParseNumber, "", tokens[0].lineNumber);
                                return false;
                            }

                            if (!assembly.AddDataWithRange(tokens[0].text, numBytesToAllocate))
                            {
                                LogError(CompilationError::DuplicateDeclaration, "", tokens[0].lineNumber);
                                return false;
                            }
                        }
                    }
                    else
                    {
                        if (tokens[3].type == TokenType::FloatingPointLiteral)
                        {
                            double result;
                            if (!StringUtility::ParseNumberLexical<double>(tokens[3].text, result))
                            {
                                LogError(CompilationError::ParseNumber, "", tokens[0].lineNumber);
                                return false;
                            }

                            if (!assembly.AddData(tokens[0].text, result))
                            {
                                LogError(CompilationError::DuplicateDeclaration, "", tokens[0].lineNumber);
                                return false;
                            }
                        }
                        else
                        {
                            int64_t result;
                            if (!StringUtility::ParseNumberLexical<int64_t>(tokens[3].text, result))
                            {
                                LogError(CompilationError::ParseNumber, "", tokens[0].lineNumber);
                                return false;
                            }

                            if (!assembly.AddData(tokens[0].text, result))
                            {
                                LogError(CompilationError::DuplicateDeclaration, "", tokens[0].lineNumber);
                                return false;
                            }
                        }
                    }
                }
                break;
            default:
                break;
            }

        return true;
    }

    bool Compiler::GetLabels(const std::vector<Token<TokenType>> &tokens, Assembly& assembly)
    {
        switch (tokens[0].type)
        {
            case TokenType::Identifier:
                if (!AssertParameterCount(tokens, 1))
                {
                    return false;
                }            

                if (AssertParameterTypes(tokens, TokenType::Colon))
                {
                    if (!assembly.AddLabel(tokens[0].text, 0))
                    {
                        LogError(CompilationError::DuplicateDeclaration, "", tokens[0].lineNumber);
                        return false;
                    }
                }
                break;
            default:
                break;
        }

        return true;
    }   

    bool Compiler::GetLabelPointer(const std::vector<Token<TokenType>> &tokens, uint64_t& numInstructions, Assembly& assembly)
    {
        if(tokens[0].type == TokenType::Identifier && tokens.size() == 2)
        {
            if(!IsOpCode(tokens[0].type) && tokens[1].type == TokenType::Colon)
            {
                if(assembly.labels.count(tokens[0].text))
                {
                    assembly.labels[tokens[0].text] = numInstructions;
                }
            }
        }
        if(IsOpCode(tokens[0].type))
        {
            numInstructions++;
        }

        return true;
    }

    bool Compiler::GetInstructions(const std::vector<Token<TokenType>> &tokens, Assembly& assembly, std::vector<Instruction> &instructions)
    {
        if(!IsOpCode(tokens[0].type))
        {
            if(tokens[0].type == TokenType::Section)
            {
                if(tokens[1].type == TokenType::Text)
                {
                    compilationStage = CompilationStage::Text;
                }
                else
                {
                    compilationStage = CompilationStage::None;
                }
            }
            else
            {
                if(compilationStage == CompilationStage::Text && tokens[0].type == TokenType::Identifier)
                {
                    if(tokens.size() == 1)
                    {
                        LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                        return false;
                    }
                    else if(tokens.size() >= 2)
                    {
                        if(tokens[1].type != TokenType::Colon)
                        {
                            LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                            return false;
                        }
                    }
                }
            } 


            return true;
        }  

        int numParameters = tokens.size() - 1;

        switch(tokens[0].type)
        {
            case TokenType::Halt:
            {            
                if (!AssertParameterCount(tokens, 0))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                Instruction instruction(OpCode::HLT, {});
                instructions.push_back(instruction);        
                break;
            }
            case TokenType::Push:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::IntegerLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::FloatingPointLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::PUSH, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }
                break;
            }
            case TokenType::Pop:
            {
                if (!AssertParameterCount(tokens, 0) && !AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (numParameters == 0)
                {
                    Instruction instruction(OpCode::POP, {});
                    instructions.push_back(instruction);
                }
                else
                {
                    if(AssertParameterTypes(tokens, TokenType::Identifier))
                    {
                        Operand operand;

                        if (CreateOperand(tokens[1], assembly, &operand))
                        {
                            Instruction instruction(OpCode::POP, { operand });
                            instructions.push_back(instruction);                    
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
                break;
            }
            case TokenType::Move:
            {
                if (!AssertParameterCount(tokens, 2))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], assembly, &operandLeft) && 
                        CreateOperand(tokens[2], assembly, &operandRight))
                    {
                        Instruction instruction(OpCode::MOV, { operandLeft, operandRight });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;
            }
            case TokenType::Increment:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::INC, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;
            }
            case TokenType::Decrement:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::DEC, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::Add:
            {
                if (!AssertParameterCount(tokens, 2))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], assembly, &operandLeft) && 
                        CreateOperand(tokens[2], assembly, &operandRight))
                    {
                        Instruction instruction(OpCode::ADD, { operandLeft, operandRight });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }                        
                break;
            }
            case TokenType::Subtract:
            {
                if (!AssertParameterCount(tokens, 2))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], assembly, &operandLeft) && 
                        CreateOperand(tokens[2], assembly, &operandRight))
                    {
                        Instruction instruction(OpCode::SUB, { operandLeft, operandRight });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }                        
                break;
            }
            case TokenType::Multiply:
            {
                if (!AssertParameterCount(tokens, 2))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], assembly, &operandLeft) && 
                        CreateOperand(tokens[2], assembly, &operandRight))
                    {
                        Instruction instruction(OpCode::MUL, { operandLeft, operandRight });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }                        
                break;
            }
            case TokenType::Divide:
            {
                if (!AssertParameterCount(tokens, 2))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier ) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral ))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], assembly, &operandLeft) && 
                        CreateOperand(tokens[2], assembly, &operandRight))
                    {
                        Instruction instruction(OpCode::DIV, { operandLeft, operandRight });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }                        
                break;
            }
            case TokenType::Compare:
            {
                if (!AssertParameterCount(tokens, 2))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier ) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::IntegerLiteral, TokenType::Identifier ) ||
                    AssertParameterTypes(tokens, TokenType::IntegerLiteral, TokenType::IntegerLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::IntegerLiteral, TokenType::FloatingPointLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::FloatingPointLiteral, TokenType::Identifier ) ||
                    AssertParameterTypes(tokens, TokenType::FloatingPointLiteral, TokenType::IntegerLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::FloatingPointLiteral, TokenType::FloatingPointLiteral ))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], assembly, &operandLeft) && 
                        CreateOperand(tokens[2], assembly, &operandRight))
                    {
                        Instruction instruction(OpCode::CMP, { operandLeft, operandRight });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }                        
                break;
            }
            case TokenType::Jump:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::JMP, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::JumpIfGreaterThan:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::JG, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::JumpIfGreaterThanOrEqual:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::JGE, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::JumpIfLessThan:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::JL, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::JumpIfLessThanOrEqual:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::JLE, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::JumpIfEqual:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::JE, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::JumpIfNotEqual:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::JNE, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }            
            case TokenType::JumpIfZero:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::JZ, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::JumpIfNotZero:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::JNZ, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::Call:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], assembly, &operand))
                    {
                        Instruction instruction(OpCode::CALL, { operand });
                        instructions.push_back(instruction);                    
                    }
                    else
                    {
                        return false;
                    }
                }            
                break;            
            }
            case TokenType::Return:
            {
                if (!AssertParameterCount(tokens, 0))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                Instruction instruction(OpCode::RET, {});
                instructions.push_back(instruction);   
                break;            
            }
            case TokenType::NOP:
            {
                if (!AssertParameterCount(tokens, 0))
                {
                    LogError(CompilationError::UnexpectedToken, "", tokens[0].lineNumber);
                    return false;
                }

                Instruction instruction(OpCode::NOP, {});
                instructions.push_back(instruction);                 
                break;            
            }
            default:
                return false;
        }

        return true;
    }

    bool Compiler::GetOperandTargetType(const std::string &text, Assembly& assembly, OperandType& operandType)
    {
        if (registers.count(text))
        {
            operandType = OperandType::Register;
            return true;
        }

        if(assembly.labels.count(text))
        {
            operandType = OperandType::LabelToInstruction;
            return true;
        }

        if(Module::HasFunction(text))
        {
            operandType = OperandType::LabelToFunction;
            return true;
        }

        if(assembly.symbols.count(text))
        {
            operandType = OperandType::Data;
            return true;
        }

        if(StringUtility::Contains(text, "."))
        {
            double value;
            if (StringUtility::ParseNumberLexical(text, value))
            {
                operandType = OperandType::FloatingPointLiteral;
                return true;
            }
        }
        else
        {
            int64_t value;
            if (StringUtility::ParseNumberLexical(text, value))
            {
                operandType = OperandType::IntegerLiteral;
                return true;
            }
        }

        operandType = OperandType::LabelToInstruction;
        return true;
    }

    bool Compiler::CreateOperand(const Token<TokenType>& token, Assembly& assembly, Operand* operand)
    {
        const std::string &text = token.text;

        OperandType type;
        GetOperandTargetType(text, assembly, type);
        operand->type = type;

        switch(type)
        {
            case OperandType::Register:
            {
                if(registers.count(text))
                {
                    uint64_t value = registers[text];
                    operand->object = Object(value);
                    return true;
                }
                else
                {
                    LogError(CompilationError::UnknownAddressRegister, text, token.lineNumber);
                }            
                break;
            }
            case OperandType::Data:
            {            
                if(assembly.symbols.count(text))
                {
                    uint64_t value = assembly.symbols[text];
                    Type valueType = assembly.types[text];

                    void *ptr = &assembly.data[value];
                    operand->object = Object(ptr, valueType);
                    return true;
                }
                else
                {
                    LogError(CompilationError::UnknownAddressData, text, token.lineNumber);
                }            
                break;
            }
            case OperandType::LabelToInstruction:
            {            
                if(assembly.labels.count(text))
                {
                    uint64_t value = assembly.labels[text];                    
                    operand->object = Object(value);
                    return true;
                }
                else
                {
                    LogError(CompilationError::UnknownAddressLabel, text, token.lineNumber);
                }
                break;
            }
            case OperandType::LabelToFunction:
            {
                VoltVMFunction value;

                if(Module::FindFunction(text, value))
                {
                    operand->object = Object((void*)value, Type::VoidPointer);
                    return true;
                }
                else
                {
                    LogError(CompilationError::UnknownAddressLabel, text, token.lineNumber);
                }                        
                break;
            }
            case OperandType::IntegerLiteral:
            {
                int64_t value;
                if (StringUtility::ParseNumberLexical<int64_t>(text, value))
                {
                    operand->object = Object(value);
                    return true;
                }
                break;
            }
            case OperandType::FloatingPointLiteral:
            {
                double value;
                if (StringUtility::ParseNumberLexical<double>(text, value))
                {
                    operand->object = Object(value);
                    return true;
                }
                break;
            }
            default:
                return false;
        }

        return false;
    }

    bool Compiler::AssertParameterCount(const std::vector<Token<TokenType>> &tokens, int expectedTokensCount)
    {
        if((tokens.size() - 1) != expectedTokensCount)
        {
            return false;
        }

        return true;
    }

    bool Compiler::IsOpCode(TokenType type)
    {
        switch(type)
        {
            case TokenType::Halt:
            case TokenType::Push:
            case TokenType::Pop:
            case TokenType::Move:
            case TokenType::Increment:
            case TokenType::Decrement:
            case TokenType::Add:
            case TokenType::Subtract:
            case TokenType::Multiply:
            case TokenType::Divide:
            case TokenType::Compare:
            case TokenType::Jump:
            case TokenType::JumpIfGreaterThan:
            case TokenType::JumpIfGreaterThanOrEqual:
            case TokenType::JumpIfLessThan:
            case TokenType::JumpIfLessThanOrEqual:
            case TokenType::JumpIfEqual:
            case TokenType::JumpIfNotEqual:
            case TokenType::JumpIfZero:
            case TokenType::JumpIfNotZero:
            case TokenType::Call:
            case TokenType::Return:
            case TokenType::NOP:
                return true;
            default:
                return false;        
        }
    }

    void Compiler::LogError(CompilationError errorCode, const std::string& content, uint64_t lineNumber)
    {
        switch(errorCode)
        {
            case CompilationError::UnexpectedToken:
                std::cout << "Error on line " << lineNumber << ": Unexpected token " << content << "\n";
                break;
            case CompilationError::InvalidParameterCount:
                std::cout << "Error on line " << lineNumber << ": Invalid number of parameters. " << content << '\n';
                break;            
            case CompilationError::UnknownAddressRegister:
                std::cout << "Error on line " << lineNumber << ": Can't find address for register " << content << '\n';
                break;
            case CompilationError::UnknownAddressData:
                std::cout << "Error on line " << lineNumber << ": Can't find address for data " << content << '\n';
                break;
            case CompilationError::UnknownAddressLabel:
                std::cout << "Error on line " << lineNumber << ": Can't find address for label " << content << '\n';
                break;
            case CompilationError::DuplicateDeclaration:
                std::cout << "Error on line " << lineNumber << ": Can not create data because it is already declared\n";
                break;
            case CompilationError::ParseNumber:
                std::cout << "Error on line " << lineNumber << ": Failed to parse number\n";
                break;
            default:
                break;
            }
    }
}