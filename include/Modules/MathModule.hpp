#ifndef REKT_MATH_MODULE_HPP
#define REKT_MATH_MODULE_HPP

#include <Module.hpp>
#include <memory>

namespace REKT
{
    class MathModule : public Module
    {
    public:
        MathModule();
        void Register() override;
        void Dispose() override;
    private:
        static int Cos(Stack<Object> *stack);
        static int Sin(Stack<Object> *stack);
        static int Tan(Stack<Object> *stack);
        static int Asin(Stack<Object> *stack);
        static int Atan(Stack<Object> *stack);
        static int Atan2(Stack<Object> *stack);
        static int Cosh(Stack<Object> *stack);
        static int Sinh(Stack<Object> *stack);
        static int Tanh(Stack<Object> *stack);
        static int Asinh(Stack<Object> *stack);
        static int Atanh(Stack<Object> *stack);
        static int Exp(Stack<Object> *stack);
        static int Log(Stack<Object> *stack);
        static int Log10(Stack<Object> *stack);
        static int Pow(Stack<Object> *stack);
        static int Sqrt(Stack<Object> *stack);
        static int Ceil(Stack<Object> *stack);
        static int Floor(Stack<Object> *stack);
        static int Trunc(Stack<Object> *stack);
        static int Round(Stack<Object> *stack);
        static int Remainder(Stack<Object> *stack);
        static int Max(Stack<Object> *stack);
        static int Min(Stack<Object> *stack);
        static int Abs(Stack<Object> *stack);    
    };
}

#endif