#include <MathModule.hpp>
#include <Formatting/FMT.hpp>
#include <chrono>
#include <iostream>
#include <cmath>

namespace REKT
{
    MathModule::MathModule()
    {
        this->name = "Math";
        this->description = "Contains functionality for doing math operations.";
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

    int MathModule::Cos(Stack<Object> *stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = sin(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Sin(Stack<Object> *stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = sin(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Tan(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = tan(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Asin(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = asin(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Atan(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = atan(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Atan2(Stack<Object> * stack)
    {          
        Object objX, objY;

        if(!stack->Pop(objY))
            return -1;

        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double y = objY.GetValueAsDouble();
        double result = atan2(x, y);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Cosh(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = cosh(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Sinh(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = sinh(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Tanh(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = tanh(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Asinh(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = asinh(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Atanh(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = atanh(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Exp(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = exp(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Log(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = log(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Log10(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = log10(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Pow(Stack<Object> * stack)
    {
        Object objX, objY;

        if(!stack->Pop(objY))
            return -1;

        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double y = objY.GetValueAsDouble();
        double result = pow(x, y);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Sqrt(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = sqrt(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Ceil(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = ceil(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Floor(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = floor(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Trunc(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = trunc(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Round(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = round(x);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Remainder(Stack<Object> * stack)
    {
        Object objX, objY;

        if(!stack->Pop(objY))
            return -1;

        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double y = objY.GetValueAsDouble();
        double result = remainder(x, y);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Max(Stack<Object> * stack)
    {
        Object objX, objY;

        if(!stack->Pop(objY))
            return -1;

        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double y = objY.GetValueAsDouble();
        double result = fmax(x, y);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Min(Stack<Object> * stack)
    {
        Object objX, objY;

        if(!stack->Pop(objY))
            return -1;

        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double y = objY.GetValueAsDouble();
        double result = fmin(x, y);
        stack->Push(Object(result));
        return 0;
    }

    int MathModule::Abs(Stack<Object> * stack)
    {
        Object objX;
        
        if(!stack->Pop(objX))
            return -1;

        double x = objX.GetValueAsDouble();
        double result = abs(x);
        stack->Push(Object(result));
        return 0;
    }          
}