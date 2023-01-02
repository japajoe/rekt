#include <volt.hpp>

uint64_t NearestPowerOfTwo(uint64_t n)
{
    uint64_t v = n; 

    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++; // next power of 2

    uint64_t x = v >> 1; // previous power of 2

    return (v - n) > (n - x) ? x : v;
} 

void volt_library_init(void)
{
    StandardLibrary::Initialize();
}

bool volt_function_register(const char* name, VoltVMFunction fn_ptr)
{
    return StandardLibrary::RegisterFunction(name, fn_ptr);
}

Assembly* volt_assembly_create(void)
{
    Assembly* assembly = new Assembly();
    return assembly;
}

void volt_assembly_destroy(Assembly* assembly)
{
    if(assembly != nullptr)
    {
        delete assembly;
        assembly = nullptr;
    }
}

uint64_t volt_assembly_get_num_instructions(Assembly* assembly)
{
    if(assembly == nullptr)
        return 0;

    return assembly->instructions.size();
}

bool volt_assembly_get_symbol_info(Assembly* assembly, const char* name, uint64_t* startOffset, uint64_t* size, Type* type)
{
    if(assembly == nullptr)
        return false;

    if(assembly->symbols.count(name) == 0)
        return false;

    if(assembly->offsets.count(name) == 0)
        return false;

    if(assembly->types.count(name) == 0)
        return false;

    *startOffset = assembly->offsets[name].offset;
    *size = assembly->offsets[name].size;
    *type = assembly->types[name];

    return true;
}

char** volt_assembly_get_symbols(Assembly* assembly, uint64_t* count)
{
    if(assembly == nullptr)
    {
        *count = 0;
        return nullptr;
    }

    if(assembly->symbols.size() == 0)
    {
        *count = 0;
        return nullptr;
    }

    *count = assembly->symbols.size();

    char **symbols = new char *[assembly->symbols.size()];

    size_t index = 0;

    for(auto& item : assembly->symbols)
    {
        char *str = new char[item.first.size() + 1];
        str[item.first.size()] = '\0';

        for (size_t i = 0; i < item.first.size(); i++)
        {
            str[i] = item.first[i];
        }

        symbols[index] = str;
        index++;
    }

    return symbols;
}

VirtualMachine* volt_virtual_machine_create(uint64_t stackCapacity)
{
    stackCapacity = NearestPowerOfTwo(stackCapacity);

    if(stackCapacity < 1024)
        stackCapacity = 1024;

    VirtualMachine *vm = new VirtualMachine(stackCapacity);
    return vm;
}

void volt_virtual_machine_destroy(VirtualMachine* vm)
{
    if(vm != nullptr)
    {
        delete vm;
        vm = nullptr;
    }
}

bool volt_virtual_machine_load_assembly(VirtualMachine* vm, Assembly* assembly)
{
    if(vm == nullptr)
        return false;
    if(assembly == nullptr)
        return false;

    return vm->LoadAssembly(assembly);
}

bool volt_virtual_machine_reset(VirtualMachine* vm)
{
    if(vm == nullptr)
        return false;

    vm->Reset();
    return true;
}

ExecutionStatus volt_virtual_machine_run(VirtualMachine* vm)
{
    if(vm == nullptr)
        return ExecutionStatus::Error;
    return vm->Run();
}

byte* volt_virtual_machine_get_registers(VirtualMachine* vm, uint64_t* size)
{
    if(vm == nullptr)
        return nullptr;

    *size = vm->GetRegisterCapacity();
    return vm->GetRegisters();
}

Compiler* volt_compiler_create(void)
{
    Compiler* compiler = new Compiler();
    return compiler;
}

void volt_compiler_destroy(Compiler* compiler)
{
    if(compiler != nullptr)
    {
        delete compiler;
        compiler = nullptr;
    }
}

bool volt_compile_from_text(Compiler* compiler, const char* source, Assembly* assembly)
{
    if(compiler == nullptr || assembly == nullptr)
        return false;

    return compiler->Compile(source, assembly);
}

bool volt_compile_from_file(Compiler* compiler, const char* filepath, Assembly* assembly)
{
    if(compiler == nullptr || assembly == nullptr)
        return false;

    if (!File::Exists(filepath))
    {
        std::cout << "File could not be found: " << filepath << '\n';
        return false;
    }        

    std::string source = File::ReadAllText(filepath);

    return compiler->Compile(source, assembly);
}

bool volt_stack_push(Stack* stack, byte* data, Type type, uint64_t* stackOffset)
{
    if(stack == nullptr)
        return false;
    return stack->Push(data, type, *stackOffset);
}

bool volt_stack_push_double(Stack* stack, double value, uint64_t* stackOffset)
{
    if(stack == nullptr)
        return false;
    
    return stack->PushDouble(value, *stackOffset);
}

bool volt_stack_push_int64(Stack* stack, int64_t value, uint64_t* stackOffset)
{
    if(stack == nullptr)
        return false;
    return stack->PushInt64(value, *stackOffset);
}

bool volt_stack_push_uint64(Stack* stack, uint64_t value, uint64_t* stackOffset)
{
    if(stack == nullptr)
        return false;
    return stack->PushUInt64(value, *stackOffset);
}

bool volt_stack_pop(Stack* stack, byte* target, uint64_t* stackOffset)
{
    if(stack == nullptr)
        return false;
    return stack->Pop(target, *stackOffset);
}

byte* volt_stack_get_buffer(Stack* stack)
{
    if(stack == nullptr)
        return nullptr;
    return stack->GetBuffer();
}

byte* volt_stack_get_top(Stack* stack)
{
    if(stack == nullptr)
        return nullptr;
    return stack->GetTop();
}

bool volt_stack_check_type(Stack* stack, Type type, int64_t index)
{
    if(stack == nullptr)
        return false;

    return stack->CheckType(type, index);
}

Type volt_stack_get_top_type(Stack* stack)
{
    if(stack == nullptr)
        return Type::UInt8;
    return stack->GetTopType();
}

uint64_t volt_stack_get_capacity(Stack* stack)
{
    if(stack == nullptr)
        return 0;
    return stack->GetCapacity();
}

uint64_t volt_stack_get_size(Stack* stack)
{
    if(stack == nullptr)
        return 0;
    return stack->GetSize();
}

uint64_t volt_stack_get_count(Stack* stack)
{
    if(stack == nullptr)
        return 0;
    return stack->GetCount();
}