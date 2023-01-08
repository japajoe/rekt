#ifndef VOLT_SYSTEM_MODULE_HPP
#define VOLT_SYSTEM_MODULE_HPP

#include <Module.hpp>
#include <memory>
#include <Utilities/Arena.hpp>

namespace VoltLang
{
    class SystemModule : public Module
    {
    public:
        SystemModule();
        void Register() override;
        void Dispose() override;
    private:
        static void* lastString;
        static std::unique_ptr<Arena> arena;
        static int PrintF(Stack *stack);
        static int GetLine(Stack *stack);
        static int TimeStamp(Stack *stack);
    };
}
#endif