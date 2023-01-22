#ifndef REKT_TOKEN_HPP
#define REKT_TOKEN_HPP

#include <string>

namespace REKT
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
        DP,
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
        JumpIfNotEqual,
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