#include <Module.hpp>

namespace REKT
{
    std::map<std::string, REKTFunction> Module::functionMap;

    void Module::Register()
    {

    }

    void Module::Dispose()
    {

    }    
    
    bool Module::RegisterFunction(const std::string &name, REKTFunction fn_ptr)
    {
        if(functionMap.count(name) == 0)
        {
            functionMap[name] = fn_ptr;
            return true;
        }
        else
        {
            std::cout << "A function with the name '" << name << "' already exists" << std::endl;
            return false;
        }
    }

    bool Module::FindFunction(const std::string &name, REKTFunction& fn_ptr)
    {
        if(functionMap.count(name))
        {
            fn_ptr = functionMap[name];
            return true;
        }

        return false;
    }

    bool Module::GetFunctionName(REKTFunction fn_ptr, std::string& name)
    {
        for(auto& f : functionMap)
        {
            if(f.second == fn_ptr)
            {
                name = f.first;
                return true;
            }
        }

        return false;
    }

    bool Module::HasFunction(const std::string& name)
    {
        if(functionMap.count(name))
        {
            return true;
        }

        return false;
    }

}