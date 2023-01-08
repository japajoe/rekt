#include <SystemModule.hpp>
#include <chrono>
#define FMT_HEADER_ONLY
#include <Formatting/fmt/format.h>
#include <Formatting/fmt/args.h>

namespace VoltLang
{
    SystemModule::SystemModule()
    {
        this->name = "System";
        this->description = "Contains standard functionality for writing to the console etc.";
    }

    void SystemModule::Register()
    {
        RegisterFunction("printf", SystemModule::PrintF);
        RegisterFunction("timestamp", SystemModule::TimeStamp);
    }

    void SystemModule::Dispose()
    {

    }

    int SystemModule::PrintF(Stack *stack)
    {
        uint64_t offset = 0;
        uint64_t stackCount = stack->GetCount();

        if(stackCount == 0)
        {
            std::cout << '\n';
        }
        else if(stackCount == 1)
        {
            std::string message;

            if(!stack->TryPopAsString(message, offset))
                return -1;

            std::cout << message;
        }
        else
        {
            std::string message;

            if(!stack->TryPopAsString(message, offset))
                return -1;

            fmt::dynamic_format_arg_store<fmt::format_context> store;

            for (uint64_t i = 0; i < stackCount-1; i++)
            {
                Object value;
                if (!stack->TryPopAsObject(value, offset))
                    return -1;

                switch(value.type)
                {
                    case ObjectType::Double:
                        store.push_back(value.value.as_double);
                        break;
                    case ObjectType::Int64:
                        store.push_back(value.value.as_int64);
                        break;
                    case ObjectType::UInt64:
                        store.push_back(value.value.as_uint64);
                        break;
                    case ObjectType::String:
                        store.push_back(value.value.as_string);
                        break;
                    default:
                        break;
                }
            }

            fmt::v9::string_view sv(message);

            try
            {
                auto msg = fmt::vformat(sv, store);
                fmt::print(msg);
            }
            catch(const std::exception& e)
            {
                std::cerr << "printf error: " << e.what() << "-> " << message << '\n';
                return -1;
            }
        }

        return 0;        
    }

    int SystemModule::TimeStamp(Stack *stack)
    {
        int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        timestamp *= 0.01;
        uint64_t stackOffset = 0;
        stack->PushInt64(timestamp, stackOffset);
        return 0;
    }    

}