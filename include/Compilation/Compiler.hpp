#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <string>
#include <algorithm>
#include <map>
#include <Core/Assembly.hpp>
#include <Tokenization/Tokenizer.hpp>
#include <Utilities/StringUtility.hpp>
#include <Utilities/Memory.hpp>
#include <AssemblyData.hpp>
#include <AssemblyLabel.hpp>
#include <Instruction.hpp>
#include <OpCode.hpp>

namespace VoltLang
{
    enum class CompilationStage : int
    {
        None,
        Data,
        Labels,
        Text
    };

    enum class CompilationError
    {
        UnexpectedToken,
        InvalidParameterCount,
        UnknownAddressRegister,
        UnknownAddressData,
        UnknownAddressLabel,
        DuplicateDeclaration,    
        ParseNumber
    };

    class Compiler
    {
    public:
        Compiler();
        bool Compile(const std::string &source, Assembly* assembly);
    private:
        std::map<std::string, uint64_t> registers;
        Tokenizer tokenizer;
        CompilationStage compilationStage;
        TokenList GetTokens(const std::string &source);
        bool GetData(const std::vector<Token<TokenType>> &tokens, AssemblyData& data);
        bool GetLabels(const std::vector<Token<TokenType>> &tokens, AssemblyLabel& labels);
        bool GetLabelPointer(const std::vector<Token<TokenType>> &tokens, uint64_t& numInstructions, AssemblyLabel &labels);
        bool GetInstructions(const std::vector<Token<TokenType>> &tokens, AssemblyData& data, AssemblyLabel& labels, std::vector<Instruction> &instructions);
        bool GetOperandTargetType(const std::string &text, const AssemblyData& data, AssemblyLabel& labels, OperandType& operandType);
        bool CreateOperand(const Token<TokenType>& token, AssemblyData &data, AssemblyLabel &labels, Operand* operand);
        bool AssertParameterCount(const std::vector<Token<TokenType>> &tokens, int expectedTokensCount);
        bool IsOpCode(TokenType type);
        void LogError(CompilationError errorCode, const std::string& content, uint64_t lineNumber);

        template<typename ...Param>
        bool AssertParameterTypes(const std::vector<Token<TokenType>> &tokens, const Param& ... param)
        {     
            const std::size_t nArgs = sizeof...(Param);

            //Too many tokens to loop through, causing out of range problems
            if(nArgs > (tokens.size() -1))
                return false;
            
            int index = 1;

            for(const auto p : {param...}) 
            {
                TokenType srcType = static_cast<TokenType>(p);
                TokenType type = tokens[index].type;
                index++;

                if(type != srcType)
                {
                    return false;
                }
            }

            return true;
        }
    };
}
#endif