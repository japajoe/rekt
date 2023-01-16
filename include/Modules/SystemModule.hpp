#ifndef VOLT_SYSTEM_MODULE_HPP
#define VOLT_SYSTEM_MODULE_HPP

#include <Module.hpp>
#include <memory>

namespace VoltLang
{
    class SystemModule : public Module
    {
    public:
        SystemModule();
        void Register() override;
        void Dispose() override;
    private:
        static int PrintF(Stack<Object> *stack);
        static int FGets(Stack<Object> *stack);
        static int TimeStamp(Stack<Object> *stack);
        static int Malloc(Stack<Object> *stack);
        static int MemSet(Stack<Object> *stack);
        static int MemCpy(Stack<Object> *stack);
        static int Free(Stack<Object> *stack);
    };
}
#endif