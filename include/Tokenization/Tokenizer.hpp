#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <Token.hpp>
#include <TokenizerA.hpp>
#include <TokenizerB.hpp>
#include <map>

namespace VoltLang
{
    typedef std::vector<std::vector<Token<TokenType>>> TokenList;

    class Tokenizer
    {
    private:
        std::map<TokenType, std::string> tokenToString;

    public:
        Tokenizer()
        {
            tokenToString[TokenType::WhiteSpace] = "WhiteSpace";
            tokenToString[TokenType::Identifier] = "Identifier";
            tokenToString[TokenType::IntegerLiteral] = "IntegerLiteral";
            tokenToString[TokenType::FloatingPointLiteral] = "FloatingPointLiteral";
            tokenToString[TokenType::StringLiteral] = "StringLiteral";
            tokenToString[TokenType::Operator] = "Operator";
            tokenToString[TokenType::StringEscapeSequence] = "StringEscapeSequence";
            tokenToString[TokenType::Comment] = "Comment";
            tokenToString[TokenType::PotentialFloatingPoint] = "PotentialFloatingPoint";
            tokenToString[TokenType::PotentialComment] = "PotentialComment";
            tokenToString[TokenType::Colon] = "Colon";
            tokenToString[TokenType::Section] = "Section";
            tokenToString[TokenType::Data] = "Data";
            tokenToString[TokenType::DB] = "DB";
            tokenToString[TokenType::DQ] = "DQ";
            tokenToString[TokenType::Text] = "Text";
            tokenToString[TokenType::Halt] = "Halt";
            tokenToString[TokenType::Push] = "Push";
            tokenToString[TokenType::Pop] = "Pop";
            tokenToString[TokenType::Move] = "Move";
            tokenToString[TokenType::Increment] = "Increment";
            tokenToString[TokenType::Decrement] = "Decrement";
            tokenToString[TokenType::Add] = "Add";
            tokenToString[TokenType::Subtract] = "Subtract";
            tokenToString[TokenType::Multiply] = "Multiply";
            tokenToString[TokenType::Divide] = "Divide";
            tokenToString[TokenType::Compare] = "Compare";
            tokenToString[TokenType::Jump] = "Jump";
            tokenToString[TokenType::JumpIfGreaterThan] = "JumpIfGreaterThan";
            tokenToString[TokenType::JumpIfGreaterThanOrEqual] = "JumpIfGreaterThanOrEqual";
            tokenToString[TokenType::JumpIfLessThan] = "JumpIfLessThan";
            tokenToString[TokenType::JumpIfLessThanOrEqual] = "JumpIfLessThanOrEqual";
            tokenToString[TokenType::JumpIfEqual] = "JumpIfEqual";
            tokenToString[TokenType::JumpIfZero] = "JumpIfZero";
            tokenToString[TokenType::JumpIfNotZero] = "JumpIfNotZero";
            tokenToString[TokenType::Call] = "Call";
            tokenToString[TokenType::Return] = "Return";
            tokenToString[TokenType::NOP] = "NOP";
        }

        std::vector<Token<TokenType>> Parse(const std::string& source)
        {
            TokenizerA tokenizerA;
            TokenizerB tokenizerB;

            auto tokensA = tokenizerA.Parse(source);

            if(tokensA.size() > 0)
            {
                auto tokensB = tokenizerB.Parse(tokensA);
                return tokensB;
            }

            std::vector<Token<TokenType>> v;
            return v;
        }

        void DumpRaw(const TokenList& tokens)
        {
            std::cout << "Lines " << tokens.size() << '\n';

            for (size_t i = 0; i < tokens.size(); i++)
            {
                std::cout << "Line " << tokens[i][0].lineNumber << "\t\t";

                for (size_t j = 0; j < tokens[i].size(); j++)
                {
                    std::cout << tokens[i][j].text << " ";
                }

                std::cout << '\n';
            }
        }

        void Dump(const TokenList& tokens)
        {
            std::cout << "Lines " << tokens.size() << '\n';

            for (size_t i = 0; i < tokens.size(); i++)
            {
                std::cout << "Line " << tokens[i][0].lineNumber << "\t\t";

                for (size_t j = 0; j < tokens[i].size(); j++)
                {
                    std::cout << tokenToString[tokens[i][j].type] << " ";
                }

                std::cout << '\n';
            }
        }    
    };
}
#endif