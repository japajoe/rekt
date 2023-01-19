#include <SystemModule.hpp>
#include <Formatting/FMT.hpp>
#include <chrono>
#include <iostream>

namespace REKT
{
    SystemModule::SystemModule()
    {
        this->name = "System";
        this->description = "Contains standard functionality for writing to the console etc.";
    } 

    void SystemModule::Register()
    {
        RegisterFunction("printf", SystemModule::PrintF);
        RegisterFunction("fgets", SystemModule::FGets);
        RegisterFunction("timestamp", SystemModule::TimeStamp);
        RegisterFunction("malloc", SystemModule::Malloc);
        RegisterFunction("memset", SystemModule::MemSet);
        RegisterFunction("memcpy", SystemModule::MemCpy);
        RegisterFunction("free", SystemModule::Free);
        RegisterFunction("meminc", SystemModule::MemInc);
        RegisterFunction("memdec", SystemModule::MemDec);
        RegisterFunction("memadd", SystemModule::MemAdd);
        RegisterFunction("memsub", SystemModule::MemSub);        
    }

    void SystemModule::Dispose()
    {

    }

    int SystemModule::PrintF(Stack<Object> *stack)
    {
        size_t stackCount = stack->GetSize();
        
        if (stackCount == 0)
        {
            std::cout << std::endl;
            return 0;
        }
        else if(stackCount == 1)
        {
            Object obj;
            if (!stack->Pop(obj))
            {
                return -1;
            }

            std::cout << obj.ToString();
            return 0;
        }
        else
        {
            Object message;

            if(!stack->Pop(message))
                return -1;

            fmt::dynamic_format_arg_store<fmt::format_context> store;

            for (uint64_t i = 0; i < stackCount-1; i++)
            {
                Object value;
                if (!stack->Pop(value))
                    return -1;

                switch(value.type)
                {
                    case Type::Double:
                        store.push_back(value.as_double);
                        break;
                    case Type::DoublePointer:
                        store.push_back(*value.as_double_pointer);
                        break;                        
                    case Type::Int64:
                        store.push_back(value.as_int64);
                        break;
                    case Type::Int64Pointer:
                        store.push_back(*value.as_int64_pointer);
                        break;
                    case Type::UInt64:
                        store.push_back(value.as_uint64);
                        break;
                    case Type::UInt64Pointer:
                        store.push_back(*value.as_uint64_pointer);
                        break;                        
                    case Type::CharPointer:
                        store.push_back(value.as_char_pointer);
                        break;
                    case Type::VoidPointer:
                        store.push_back(value.as_void_pointer);
                        break;                        
                    default:
                        break;
                }
            }

            auto messageText = message.ToString();

            fmt::v9::string_view sv(messageText);

            try
            {
                auto msg = fmt::vformat(sv, store);
                fmt::print(msg);
            }
            catch(const std::exception& e)
            {
                std::cerr << "printf error: " << e.what() << "-> " << messageText << '\n';
                return -1;
            }
        }

        return 0;
    }

    int SystemModule::FGets(Stack<Object> *stack)
    {
        Object argSize, argCharPtr;

        if (!stack->Pop(argCharPtr))
        {
            return -1;
        }        

        if (!stack->Pop(argSize))
        {
            return -1;
        }

        uint64_t size = 0;
        char *str = nullptr;

        if(!argCharPtr.IsPointerType())
        {
            return -1;
        }

        switch(argSize.type)
        {
            case Type::UInt64:
            case Type::Int64:
                size = argSize.as_uint64;
                break;
            case Type::UInt64Pointer:
            case Type::Int64Pointer:
                size = *argSize.as_uint64_pointer;
                break;
            default:
            {
                std::cout << "memset: Argument 'size' is not a uint64/int64/uint64*/int64*" << std::endl;
                return -1;
            }
        }        

        str = argCharPtr.as_char_pointer;

        if (fgets(str, size, stdin) == NULL)
            return -1;

        Object obj(str);
        stack->Push(obj);

        return 0;
    }

    int SystemModule::TimeStamp(Stack<Object> *stack)
    {
        return 0;
    }

    int SystemModule::Malloc(Stack<Object> *stack)
    {
        Object arg;
        if(!stack->Pop(arg))
        {
            return -1;
        }

        uint64_t size = 0;

        switch(arg.type)
        {
            case Type::UInt64:
            case Type::Int64:
                size = arg.as_uint64;
                break;
            case Type::UInt64Pointer:
            case Type::Int64Pointer:
                size = *arg.as_uint64_pointer;
                break;
            default:
            {
                std::cout << "malloc: Argument 'size' is not a uint64/int64/uint64*/int64*" << std::endl;
                return -1;
            }
        }

        void *address = malloc(size);
        Object memory(address, Type::VoidPointer);
        stack->Push(memory);

        return 0;
    }

    int SystemModule::MemSet(Stack<Object> *stack)
    {
        Object argAddress, argSize, argValue;

        if(!stack->Pop(argAddress))
        {
            return -1;
        }        

        if(!stack->Pop(argValue))
        {
            return -1;
        }

        if(!stack->Pop(argSize))
        {
            return -1;
        }

        if(argAddress.type != Type::VoidPointer)
        {
            std::cout << "memset: Argument 'address' is not a void*" << std::endl;
            return -1;
        }

        void *address = argAddress.as_void_pointer;
        uint64_t value = 0;
        uint64_t size = 0;

        switch(argValue.type)
        {
            case Type::UInt64:
            case Type::Int64:
                value = argValue.as_uint64;
                break;
            case Type::UInt64Pointer:
            case Type::Int64Pointer:
                value = *argValue.as_uint64_pointer;
                break;
            default:
            {
                std::cout << "memset: Argument 'value' is not a uint64/int64/uint64*/int64*" << std::endl;
                return -1;
            }
        }

        switch(argSize.type)
        {
            case Type::UInt64:
            case Type::Int64:
                size = argSize.as_uint64;
                break;
            case Type::UInt64Pointer:
            case Type::Int64Pointer:
                size = *argSize.as_uint64_pointer;
                break;
            default:
            {
                std::cout << "memset: Argument 'size' is not a uint64/int64/uint64*/int64*" << std::endl;
                return -1;
            }
        }

        memset(address, static_cast<int>(value), size);

        return 0;
    }

    int SystemModule::MemCpy(Stack<Object> *stack)
    {
        Object argDst, argSrc, argSize;

        if(!stack->Pop(argDst))
        {
            return -1;
        }        

        if(!stack->Pop(argSrc))
        {
            return -1;
        }

        if(!stack->Pop(argSize))
        {
            return -1;
        }

        if(argDst.type != Type::VoidPointer)
        {
            std::cout << "memcpy: Argument 'dst' is not a void*" << std::endl;
            return -1;
        }        

        if(argSrc.type != Type::VoidPointer)
        {
            std::cout << "memcpy: Argument 'src' is not a void*" << std::endl;
            return -1;
        }

        void *dst = argDst.as_void_pointer;
        void *src = argSrc.as_void_pointer;
        uint64_t size = 0;

        switch (argSize.type)
        {
            case Type::UInt64:
            case Type::Int64:
                size = argSize.as_uint64;
                break;
            case Type::UInt64Pointer:
            case Type::Int64Pointer:
                size = *argSize.as_uint64_pointer;
                break;
            default:
            {
                std::cout << "memcpy: Argument 'size' is not a uint64/int64/uint64*/int64*" << std::endl;
                return -1;
            }
        }

        memcpy(dst, src, size);

        return 0;
    }

    int SystemModule::Free(Stack<Object> *stack)
    {
        Object argPtr;
        if(!stack->Pop(argPtr))
        {
            return -1;
        }

        if(!argPtr.IsPointerType())
        {
            std::cout << "free: Argument is not a pointer type" << std::endl;
            return -1;
        }

        void *address = argPtr.as_void_pointer;
        free(address);
        return 0;
    }

    int SystemModule::MemInc(Stack<Object> *stack)
    {
        Object argPtr;
        
        if(!stack->Pop(argPtr))
        {
            return -1;
        }

        if(!argPtr.IsPointerType())
        {
            return -1;
        }

        char *p = reinterpret_cast<char *>(argPtr.as_void_pointer);
        p += 1;
        void *ptr = p;
        stack->Push(Object(ptr, argPtr.type));

        return 0;
    }

    int SystemModule::MemDec(Stack<Object> *stack)
    {
        Object argPtr;
        
        if(!stack->Pop(argPtr))
        {
            return -1;
        }

        if(!argPtr.IsPointerType())
        {
            return -1;
        }

        char *p = reinterpret_cast<char *>(argPtr.as_void_pointer);
        p -= 1;
        void *ptr = p;
        stack->Push(Object(ptr, argPtr.type));

        return 0;
    }

    int SystemModule::MemAdd(Stack<Object> *stack)
    {
        Object argCount, argPtr;
        
        if(!stack->Pop(argPtr))
        {
            return -1;
        }

        if(!stack->Pop(argCount))
        {
            return -1;
        }

        if(!argPtr.IsPointerType())
        {
            return -1;
        }

        uint64_t count = 0;

        switch(argCount.type)
        {
            case Type::Int64:
                count = argCount.as_int64;
                break;
            case Type::UInt64:
                count = argCount.as_uint64;
                break;
            case Type::Int64Pointer:
                count = *argCount.as_int64_pointer;
                break;
            case Type::UInt64Pointer:
                count = *argCount.as_uint64_pointer;
                break;
            default:
                return -1;
        }     

        char *p = reinterpret_cast<char *>(argPtr.as_void_pointer);
        p += count;
        void *ptr = p;

        stack->Push(Object(ptr, argPtr.type));

        return 0;
    }

    int SystemModule::MemSub(Stack<Object> *stack)
    {
        Object argCount, argPtr;
        
        if(!stack->Pop(argPtr))
        {
            return -1;
        }

        if(!stack->Pop(argCount))
        {
            return -1;
        }

        if(!argPtr.IsPointerType())
        {
            return -1;
        }

        uint64_t count = 0;

        switch(argCount.type)
        {
            case Type::Int64:
                count = argCount.as_int64;
                break;
            case Type::UInt64:
                count = argCount.as_uint64;
                break;
            case Type::Int64Pointer:
                count = *argCount.as_int64_pointer;
                break;
            case Type::UInt64Pointer:
                count = *argCount.as_uint64_pointer;
                break;
            default:
                return -1;
        }

        char *p = reinterpret_cast<char *>(argPtr.as_void_pointer);
        p -= count;
        void *ptr = p;

        return 0;
    }    
}