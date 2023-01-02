#ifndef STANDARDLIBRARY_HPP
#define STANDARDLIBRARY_HPP

#include <map>
#include <string>
#include <Stack.hpp>

namespace VoltLang
{
    typedef int (*VoltVMFunction)(Stack* stack);

    class StandardLibrary
    {
    private:
        static std::map<std::string, uint64_t> functionMap;
        static int Print(Stack *stack);
        static int PrintLine(Stack *stack);
        static int PrintNumber(Stack *stack);
        static int NewLine(Stack *stack);
        static int TimeStamp(Stack *stack);
    public:
        static void Initialize();
        static bool RegisterFunction(const std::string &name, VoltVMFunction fn_ptr);
        static bool FindFunction(const std::string &name, uint64_t* fn_ptr);
        static bool HasFunction(const std::string &name);
    };
}
#endif