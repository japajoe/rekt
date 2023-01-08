#include <MemoryModule.hpp>

namespace VoltLang
{
    MemoryModule::MemoryModule()
    {
        this->name = "Memory";
        this->description = "Contains functions to allocate/set/copy/free memory.";
    }

    void MemoryModule::Register()
    {
        RegisterFunction("malloc", MemoryModule::Alloc);
        RegisterFunction("memset", MemoryModule::Set);
        RegisterFunction("memcpy", MemoryModule::Copy);
        RegisterFunction("free", MemoryModule::Free);

    }

    void MemoryModule::Dispose()
    {

    }

    int MemoryModule::Alloc(Stack *stack)
    {
        uint64_t stackCount = stack->GetCount();

        if (stackCount == 0)
        {
            return -1;
        }        

        if(stackCount != 1)
        {
            return -1;
        }

        uint64_t size;
        uint64_t offset;

        if(!stack->TryPopAsUInt64(size, offset))
            return -1;

        void* pointer = malloc(size);

        uintptr_t address = reinterpret_cast<uintptr_t>(pointer);

        stack->PushUInt64(address, offset);

        return 0;
    }

    int MemoryModule::Set(Stack *stack)
    {
        uint64_t stackCount = stack->GetCount();

        if (stackCount != 3)
        {
            return -1;
        }

        uint64_t size;
        uint64_t offset;
        uint64_t value;
        uint64_t pointer;

        if (!stack->TryPopAsUInt64(size, offset))
        {
            return -1;
        }

        if (!stack->TryPopAsUInt64(value, offset))
        {
            return -1;
        }

        if (!stack->TryPopAsUInt64(pointer, offset))
        {
            return -1;
        }

        uintptr_t address = static_cast<uintptr_t>(pointer);
        void *target = reinterpret_cast<void *>(address);

        memset(target, value, size);

        return 0;
    }

    int MemoryModule::Copy(Stack *stack)
    {
        uint64_t stackCount = stack->GetCount();

        if (stackCount != 3)
        {
            return -1;
        }

        uint64_t size;
        uint64_t dest;
        uint64_t src;
        uint64_t offset;

        if(!stack->TryPopAsUInt64(size, offset))
            return -1;

        if(!stack->TryPopAsUInt64(dest, offset))
            return -1;

        if(!stack->TryPopAsUInt64(src, offset))
            return -1;

        void *pSrc = reinterpret_cast<void *>(static_cast<uintptr_t>(src));
        void *pDst = reinterpret_cast<void *>(static_cast<uintptr_t>(dest));

        memcpy(pDst, pSrc, size);

        return 0;
    }

    int MemoryModule::Free(Stack *stack)
    {
        uint64_t stackCount = stack->GetCount();

        if (stackCount != 1)
        {
            return -1;
        }

        uint64_t src;
        uint64_t offset;

        if(!stack->TryPopAsUInt64(src, offset))
            return -1;

        void *pSrc = reinterpret_cast<void *>(static_cast<uintptr_t>(src));

        free(pSrc);

        return 0;
    }
}
