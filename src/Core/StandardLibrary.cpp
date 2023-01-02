#include <StandardLibrary.hpp>
#include <iostream>
#include <cstring>
#include <chrono>

namespace VoltLang
{
    std::map<std::string, uint64_t> StandardLibrary::functionMap;

    void StandardLibrary::Initialize()
    {
        RegisterFunction("print", StandardLibrary::Print);
        RegisterFunction("println", StandardLibrary::PrintLine);
        RegisterFunction("printnum", StandardLibrary::PrintNumber);
        RegisterFunction("newln", StandardLibrary::NewLine);
        RegisterFunction("timestamp", StandardLibrary::TimeStamp);
    }

    bool StandardLibrary::RegisterFunction(const std::string &name, VoltVMFunction fn_ptr)
    {
        if(functionMap.count(name) == 0)
        {
            functionMap[name] = reinterpret_cast<uint64_t>(fn_ptr);
            return true;
        }

        return false;
    }

    bool StandardLibrary::FindFunction(const std::string &name, uint64_t* fn_ptr)
    {
        if(functionMap.count(name))
        {
            *fn_ptr = functionMap[name];
            return true;
        }

        return false;
    }

    bool StandardLibrary::HasFunction(const std::string &name)
    {
        if(functionMap.count(name))
        {
            return true;
        }

        return false;    
    }

    int StandardLibrary::Print(Stack *stack)
    {
        unsigned char buffer[8];
        memset(buffer, 0, 8);
        
        std::string value;
        uint64_t offset;

        if (!stack->TryPopAsString(buffer, value, offset))
        {
            return -1;
        }

        std::cout << value;

        return 0;
    }

    int StandardLibrary::PrintLine(Stack *stack)
    {
        unsigned char buffer[8];
        memset(buffer, 0, 8);

        std::string value;
        uint64_t offset;

        if (!stack->TryPopAsString(buffer, value, offset))
        {
            return -1;
        }

        std::cout << value << '\n';

        return 0;
    }

    int StandardLibrary::PrintNumber(Stack *stack)
    {
        unsigned char buffer[8];
        memset(buffer, 0, 8);

        std::string value;
        uint64_t offset;

        if (!stack->TryPopAsString(buffer, value, offset))
        {
            return -1;
        }

        std::cout << value;

        return 0;
    }

    int StandardLibrary::NewLine(Stack *stack)
    {
        std::cout << '\n';
        return 0;
    }

    int StandardLibrary::TimeStamp(Stack *stack)
    {
        int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        timestamp *= 0.01;
        uint64_t stackOffset = 0;
        stack->PushInt64(timestamp, stackOffset);
        return 0;
    }
}