#ifndef VOLT_MODULE_HPP
#define VOLT_MODULE_HPP

#include <map>
#include <cstdint>
#include <string>
#include <Core/Specification.hpp>
#include <Core/Stack.hpp>

namespace VoltLang
{
    typedef int (*VoltVMFunction)(Stack<Object>* stack);

    class Module
    {
    private:
        static std::map<std::string, VoltVMFunction> functionMap;
    public:
        virtual void Register();
        virtual void Dispose();
        static bool RegisterFunction(const std::string &name, VoltVMFunction fn_ptr);
        static bool FindFunction(const std::string &name, VoltVMFunction& fn_ptr);
        static bool GetFunctionName(VoltVMFunction fn_ptr, std::string& name);
        static bool HasFunction(const std::string& name);
        
        std::string GetName() const
        {
            return name;
        }

        std::string GetDescription() const
        {
            return description;
        }

    protected:
        std::string name;
        std::string description;
    };
}
#endif