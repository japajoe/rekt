#ifndef VOLT_SYSTEM_MODULE_HPP
#define VOLT_SYSTEM_MODULE_HPP

#include <Module.hpp>

namespace VoltLang
{
    class SystemModule : public Module
    {
    public:
        SystemModule();
        void Register() override;
        void Dispose() override;
    private:
        static int PrintF(Stack *stack);
        static int TimeStamp(Stack *stack);    
    };
}
#endif