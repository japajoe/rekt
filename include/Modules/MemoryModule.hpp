#ifndef VOLT_MEMORYMODULE_HPP
#define VOLT_MEMORYMODULE_HPP

#include <Module.hpp>

namespace VoltLang
{
    class MemoryModule : public Module
    {
    public:
        MemoryModule();
        void Register() override;
        void Dispose() override;    
    private:
        static int Alloc(Stack *stack);
        static int Set(Stack *stack);
        static int Copy(Stack *stack);
        static int Free(Stack *stack);
    };
}

#endif