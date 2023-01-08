#include <MathModule.hpp>
#include <cmath>

namespace VoltLang
{
    MathModule::MathModule()
    {
        this->name = "Math";
        this->description = "Contains functions to do math operatioons.";        
    }

    void MathModule::Register()
    {
        RegisterFunction("cos", MathModule::Cos);
        RegisterFunction("sin", MathModule::Sin);
        RegisterFunction("tan", MathModule::Tan);
        RegisterFunction("asin", MathModule::Asin);
        RegisterFunction("atan", MathModule::Atan);
        RegisterFunction("atan2", MathModule::Atan2);
        RegisterFunction("cosh", MathModule::Cosh);
        RegisterFunction("sinh", MathModule::Sinh);
        RegisterFunction("tanh", MathModule::Tanh);
        RegisterFunction("asinh", MathModule::Asinh);
        RegisterFunction("atanh", MathModule::Atanh);
        RegisterFunction("exp", MathModule::Exp);
        RegisterFunction("log", MathModule::Log);
        RegisterFunction("log10", MathModule::Log10);
        RegisterFunction("pow", MathModule::Pow);
        RegisterFunction("sqrt", MathModule::Sqrt);
        RegisterFunction("ceil", MathModule::Ceil);
        RegisterFunction("floor", MathModule::Floor);
        RegisterFunction("trunc", MathModule::Trunc);
        RegisterFunction("round", MathModule::Round);
        RegisterFunction("remainder", MathModule::Remainder);
        RegisterFunction("max", MathModule::Max);
        RegisterFunction("min", MathModule::Min);
        RegisterFunction("abs", MathModule::Abs);
    }

    void MathModule::Dispose()
    {
        
    }        

    int MathModule::Cos(Stack* stack)
    {
        double value;
        uint64_t offset;
        if (!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = cos(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Sin(Stack* stack)
    {
        double value;
        uint64_t offset;

        if(!stack->TryPopAsDouble(value, offset))
            return -1;

        double result = sin(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Tan(Stack* stack)
    {
        double value;
        uint64_t offset;
        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = tan(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Asin(Stack* stack)
    {
        double value;    
        uint64_t offset;        

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = asin(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Atan(Stack* stack)
    {
        double value;     
        uint64_t offset;               

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = atan(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Atan2(Stack* stack)
    {          
        double x;     
        double y;     
        uint64_t offset;  

        if(!stack->TryPopAsDouble(y, offset))
        {
            return -1;
        }

        if(!stack->TryPopAsDouble(x, offset))
        {
            return -1;
        }         

        double result = atan2(x, y);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Cosh(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = cosh(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Sinh(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = sinh(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Tanh(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = tanh(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Asinh(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = asinh(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Atanh(Stack* stack)
    {
        double value;     
        uint64_t offset;  

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = atanh(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Exp(Stack* stack)
    {
        double value;     
        uint64_t offset;  

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = exp(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Log(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = log(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Log10(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = log10(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Pow(Stack* stack)
    {
        double x;     
        double y;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(y, offset))
        {
            return -1;
        }

        if(!stack->TryPopAsDouble(x, offset))
        {
            return -1;
        }          

        double result = pow(x, y);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Sqrt(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = sqrt(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Ceil(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = ceil(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Floor(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = floor(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Trunc(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = trunc(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Round(Stack* stack)
    {
        double value;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = round(value);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Remainder(Stack* stack)
    {
        double x;     
        double y;     
        uint64_t offset;               

        if(!stack->TryPopAsDouble(y, offset))
        {
            return -1;
        }

        if(!stack->TryPopAsDouble(x, offset))
        {
            return -1;
        }

        double result = remainder(x, y);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Max(Stack* stack)
    {
        double x;     
        double y;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(y, offset))
        {
            return -1;
        }

        if(!stack->TryPopAsDouble(x, offset))
        {
            return -1;
        }           

        double result = fmax(x, y);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Min(Stack* stack)
    {
        double x;     
        double y;     
        uint64_t offset;              

        if(!stack->TryPopAsDouble(y, offset))
        {
            return -1;
        }

        if(!stack->TryPopAsDouble(x, offset))
        {
            return -1;
        }        

        double result = fmin(x, y);

        stack->PushDouble(result, offset);

        return 0;
    }

    int MathModule::Abs(Stack* stack)
    {
        double value;     
        uint64_t offset;        

        if(!stack->TryPopAsDouble(value, offset))
        {
            return -1;
        }

        double result = abs(value);

        stack->PushDouble(result, offset);

        return 0;
    }
}