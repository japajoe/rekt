#ifndef REKT_MODULELOADER_HPP
#define REKT_MODULELOADER_HPP

#include <Module.hpp>
#include <memory>
#include <vector>
#include <iostream>

namespace REKT
{
    class ModuleLoader
    {
    private:
        static std::vector<std::shared_ptr<Module>> modules;
    public:
        template<typename T>
        static bool Load()
        {
            auto module = std::make_shared<T>();

            Module* ptr = dynamic_cast<T*>(module.get());

            if(ptr == nullptr)
            {
                std::cout << "This does not appear to be a valid module" << std::endl;
                return false;
            }

            if(ptr->GetName().size() == 0)
            {
                std::cout << "The module must have a name" << std::endl;
                return false;
            }

            for (size_t i = 0; i < modules.size(); i++)
            {
                if(modules[i]->GetName() == ptr->GetName())
                {
                    std::cout << "The module with the same name already exists" << std::endl;
                    return false;
                }
            }
            
            modules.push_back(module);
            ptr->Register();
            
            return true;
        }

        static void Dispose()
        {
            for (size_t i = 0; i < modules.size(); i++)
                modules[i]->Dispose();
        }
    };
}
#endif