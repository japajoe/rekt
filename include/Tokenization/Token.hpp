#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

namespace VoltLang
{
    enum class PrimitiveTokenType : int
    {
        WhiteSpace = 0, // Basically an unused type
        Identifier,
        IntegerLiteral,
        FloatingPointLiteral,
        StringLiteral,
        Operator,
        StringEscapeSequence,
        Comment,
        PotentialFloatingPoint,
        PotentialComment
    };

    enum class TokenType : int
    {
        WhiteSpace = 0,     //Basically an unused type
        Identifier,
        IntegerLiteral,
        FloatingPointLiteral,
        StringLiteral,
        Operator,
        StringEscapeSequence,
        Comment,
        PotentialFloatingPoint,
        PotentialComment,
        Colon,
        Section,
        Data,
        DB,
        DQ,
        Text,
        Halt,
        Push,
        Pop,
        Move,
        Increment,
        Decrement,
        Add,
        Subtract,
        Multiply,
        Divide,
        Compare,
        Jump,
        JumpIfGreaterThan,
        JumpIfGreaterThanOrEqual,
        JumpIfLessThan,
        JumpIfLessThanOrEqual,
        JumpIfEqual,
        JumpIfZero,
        JumpIfNotZero,
        Call,
        Return,
        NOP
    };

    template<typename T>
    struct Token
    {
        T type;
        std::string text;
        uint64_t lineNumber;
    };
}
#endif