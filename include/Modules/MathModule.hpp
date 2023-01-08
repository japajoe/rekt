#ifndef VOLT_MATHMODULE_HPP
#define VOLT_MATHMODULE_HPP

#include <Module.hpp>

namespace VoltLang
{
    class MathModule : public Module
    {
    public:
        MathModule();
        void Register() override;
        void Dispose() override;
    private:
        static int Cos(Stack* stack);
        static int Sin(Stack* stack);
        static int Tan(Stack* stack);
        static int Asin(Stack* stack);
        static int Atan(Stack* stack);
        static int Atan2(Stack* stack);
        static int Cosh(Stack* stack);
        static int Sinh(Stack* stack);
        static int Tanh(Stack* stack);
        static int Asinh(Stack* stack);
        static int Atanh(Stack* stack);
        static int Exp(Stack* stack);
        static int Log(Stack* stack);
        static int Log10(Stack* stack);
        static int Pow(Stack* stack);
        static int Sqrt(Stack* stack);
        static int Ceil(Stack* stack);
        static int Floor(Stack* stack);
        static int Trunc(Stack* stack);
        static int Round(Stack* stack);
        static int Remainder(Stack* stack);
        static int Max(Stack* stack);
        static int Min(Stack* stack);
        static int Abs(Stack* stack);
    };
}

#endif