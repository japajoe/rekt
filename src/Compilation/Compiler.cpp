#include <Compiler.hpp>
#include <Core/StandardLibrary.hpp>

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
        compilationStage = CompilationStage::None;
        // Tokenizes the input string and returns a std::vector<std::vector<Token<TokenType>>>
        // This way we can process the source line by line. This also means none of our instructions or declarations
        // are allowed to be defined over the span of multiple lines.
        auto tokens = GetTokens(source);

        AssemblyData data;
        AssemblyLabel labels;
        uint64_t numInstructions = 0;
        std::vector<Instruction> instructions;

        //Registers any data and labels
        for (size_t i = 0; i < tokens.size(); i++)
        {
            GetData(tokens[i], data);
            GetLabels(tokens[i], labels);
        }

        //Once all labels are found, count instructions and determine to which instruction a label points towards
        for (size_t i = 0; i < tokens.size(); i++)
        {
            GetLabelPointer(tokens[i], numInstructions, labels);
        }

        //Finally create all instructions
        for (size_t i = 0; i < tokens.size(); i++)
        {        
            if(!GetInstructions(tokens[i], data, labels, instructions))
            {
                return false;
            }
        }

        instructions.push_back(Instruction(OpCode::Halt, {}));

        assembly->data = data.data;
        assembly->symbols = data.symbols;
        assembly->offsets = data.offsets;
        assembly->types = data.types;
        assembly->instructions = instructions;

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

    bool Compiler::GetData(const std::vector<Token<TokenType>> &tokens, AssemblyData& data)
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
                            if (!data.Add(tokens[0].text, tokens[3].text))
                            {
                                LogError(CompilationError::DuplicateDeclaration, "", tokens[0].lineNumber);
                                return false;
                            }
                        }
                        else
                        {
                            unsigned char result;
                            if(!StringUtility::ParseNumberLexical<unsigned char>(tokens[3].text, result))
                            {
                                LogError(CompilationError::ParseNumber, "", tokens[0].lineNumber);
                                return false;
                            }

                            if (!data.Add(tokens[0].text, result))
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

                            if (!data.Add(tokens[0].text, result))
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

                            if (!data.Add(tokens[0].text, result))
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

    bool Compiler::GetLabels(const std::vector<Token<TokenType>> &tokens, AssemblyLabel& labels)
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
                    if (!labels.Add(tokens[0].text, 0))
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

    bool Compiler::GetLabelPointer(const std::vector<Token<TokenType>> &tokens, uint64_t& numInstructions, AssemblyLabel& labels)
    {
        if(tokens[0].type == TokenType::Identifier && tokens.size() == 2)
        {
            if(!IsOpCode(tokens[0].type))
            {
                if(labels.labels.count(tokens[0].text))
                {
                    labels.labels[tokens[0].text] = numInstructions;
                }
            }
        }
        if(IsOpCode(tokens[0].type))
        {
            numInstructions++;
        }

        return true;
    }

    bool Compiler::GetInstructions(const std::vector<Token<TokenType>> &tokens, AssemblyData& data, AssemblyLabel& labels, std::vector<Instruction> &instructions)
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
                    return false;
                }

                Instruction instruction(OpCode::Halt, {});
                instructions.push_back(instruction);        
                break;
            }
            case TokenType::Push:
            {
                if (!AssertParameterCount(tokens, 1))
                {
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::IntegerLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::FloatingPointLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::Push, { operand });
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
                    return false;
                }

                if (numParameters == 0)
                {
                    Instruction instruction(OpCode::Pop, {});
                    instructions.push_back(instruction);
                }
                else
                {
                    if(AssertParameterTypes(tokens, TokenType::Identifier))
                    {
                        Operand operand;

                        if (CreateOperand(tokens[1], data, labels, &operand))
                        {
                            Instruction instruction(OpCode::Pop, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], data, labels, &operandLeft) && 
                        CreateOperand(tokens[2], data, labels, &operandRight))
                    {
                        Instruction instruction(OpCode::Move, { operandLeft, operandRight });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::Increment, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::Decrement, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], data, labels, &operandLeft) && 
                        CreateOperand(tokens[2], data, labels, &operandRight))
                    {
                        Instruction instruction(OpCode::Add, { operandLeft, operandRight });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], data, labels, &operandLeft) && 
                        CreateOperand(tokens[2], data, labels, &operandRight))
                    {
                        Instruction instruction(OpCode::Subtract, { operandLeft, operandRight });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], data, labels, &operandLeft) && 
                        CreateOperand(tokens[2], data, labels, &operandRight))
                    {
                        Instruction instruction(OpCode::Multiply, { operandLeft, operandRight });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier, TokenType::Identifier ) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::IntegerLiteral ) ||
                    AssertParameterTypes(tokens, TokenType::Identifier, TokenType::FloatingPointLiteral ))
                {
                    Operand operandLeft;
                    Operand operandRight;

                    if (CreateOperand(tokens[1], data, labels, &operandLeft) && 
                        CreateOperand(tokens[2], data, labels, &operandRight))
                    {
                        Instruction instruction(OpCode::Divide, { operandLeft, operandRight });
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

                    if (CreateOperand(tokens[1], data, labels, &operandLeft) && 
                        CreateOperand(tokens[2], data, labels, &operandRight))
                    {
                        Instruction instruction(OpCode::Compare, { operandLeft, operandRight });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::Jump, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::JumpIfGreaterThan, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::JumpIfGreaterThanOrEqual, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::JumpIfLessThan, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::JumpIfLessThanOrEqual, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::JumpIfEqual, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::JumpIfZero, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::JumpIfNotZero, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Operand operand;

                    if (CreateOperand(tokens[1], data, labels, &operand))
                    {
                        Instruction instruction(OpCode::Call, { operand });
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
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Instruction instruction(OpCode::Return, {});
                    instructions.push_back(instruction);   
                }            
                break;            
            }
            case TokenType::NOP:
            {
                if (!AssertParameterCount(tokens, 0))
                {
                    return false;
                }

                if (AssertParameterTypes(tokens, TokenType::Identifier ))
                {
                    Instruction instruction(OpCode::NOP, {});
                    instructions.push_back(instruction);                 
                }            
                break;            
            }
            default:
                return false;
        }

        return true;
    }

    bool Compiler::GetOperandTargetType(const std::string &text, const AssemblyData& data, AssemblyLabel& labels, OperandType& operandType)
    {
        if (registers.count(text))
        {
            operandType = OperandType::Register;
            return true;
        }

        if(labels.labels.count(text))
        {
            operandType = OperandType::LabelToInstruction;
            return true;
        }

        if(StandardLibrary::HasFunction(text))
        {
            operandType = OperandType::LabelToFunction;
            return true;
        }

        if(data.symbols.count(text))
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

    bool Compiler::CreateOperand(const Token<TokenType>& token, AssemblyData &data, AssemblyLabel &labels, Operand* operand)
    {
        const std::string &text = token.text;

        OperandType type;
        GetOperandTargetType(text, data, labels, type);

        switch(type)
        {
            case OperandType::Register:
            {
                if(registers.count(text))
                {
                    uint64_t value = registers[text];
                    Type valueType = data.types[text];
                    *operand = Operand(type, valueType, value);
                    //std::cout << "Create operand to Register: " << text << " with value: " << value << '\n';
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
                if(data.symbols.count(text))
                {
                    uint64_t value = data.symbols[text];
                    Type valueType = data.types[text];
                    *operand = Operand(type, valueType, value);
                    //std::cout << "Create operand to Data: " << text << " with value: " << value << '\n';
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
                if(labels.labels.count(text))
                {
                    uint64_t value = labels.labels[text];
                    *operand = Operand(type, Type::UInt64, value);
                    //std::cout << "Create operand to LabelToInstruction: " << text << " with value: " << value << '\n';
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
                uint64_t value = 0;

                if(StandardLibrary::FindFunction(text, &value))
                {
                    *operand = Operand(type, Type::UInt64, value);
                    //std::cout << "Create operand to LabelToFunction: " << text << " with value: " << value << '\n';
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
                    *operand = Operand(type, Type::Int64, value);
                    //std::cout << "Create operand to IntegerLiteral: " << text << " with value: " << value << '\n';
                    return true;
                }
                break;
            }
            case OperandType::FloatingPointLiteral:
            {
                double value;
                if (StringUtility::ParseNumberLexical<double>(text, value))
                {
                    *operand = Operand(type, Type::Double, value);
                    //std::cout << "Create operand to FloatingPointLiteral: " << text << " with value: " << value << '\n';
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

    // bool Compiler::AssertParameterTypes(const std::vector<Token<TokenType>> &tokens, const std::vector<TokenType>& requiredTokens)
    // {
    //     for (size_t i = 1; i < tokens.size(); i++)
    //     {
    //         if (tokens[i].type != requiredTokens[i - 1])
    //         {
    //             return false;
    //         }
    //     }

    //     return true;
    // }

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