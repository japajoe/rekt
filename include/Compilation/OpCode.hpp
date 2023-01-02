#ifndef OPCODE_HPP
#define OPCODE_HPP

namespace VoltLang
{
    enum class OpCode : unsigned char
    {
        Halt = 0,
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
        NOP,
        NUM_OPCODES
    };
}
#endif