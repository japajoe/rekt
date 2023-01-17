#include <volt.hpp>
#include <Utilities/Memory.hpp>
#include <Modules/ModuleLoader.hpp>
#include <Modules/SystemModule.hpp>

void volt_modules_load(void)
{
    ModuleLoader::Load<SystemModule>();
}

void volt_modules_dispose(void)
{
    ModuleLoader::Dispose();
}

bool volt_function_register(const char* name, VoltVMFunction fn_ptr)
{
    return Module::RegisterFunction(name, fn_ptr);
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

bool volt_assembly_get_label_info(Assembly* assembly, const char* name, uint64_t* offset)
{
    if(assembly == nullptr)
        return false;

    if(assembly->labels.count(name) == 0)
        return false;

    *offset = assembly->labels[name];

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

char** volt_assembly_get_labels(Assembly* assembly, uint64_t* count)
{
    if(assembly == nullptr)
    {
        *count = 0;
        return nullptr;
    }

    if(assembly->labels.size() == 0)
    {
        *count = 0;
        return nullptr;
    }

    *count = assembly->labels.size();

    char **labels = new char *[assembly->labels.size()];

    size_t index = 0;

    for(auto& item : assembly->labels)
    {
        char *str = new char[item.first.size() + 1];
        str[item.first.size()] = '\0';

        for (size_t i = 0; i < item.first.size(); i++)
        {
            str[i] = item.first[i];
        }

        labels[index] = str;
        index++;
    }

    return labels;
}

OpCode volt_assembly_get_instruction_opcode(Assembly* assembly, uint64_t offset)
{
    if(assembly == nullptr)
        return OpCode::NUM_OPCODES;

    if(offset >= assembly->instructions.size())
        return OpCode::NUM_OPCODES;

    return assembly->instructions[offset].opcode;
}

VirtualMachine* volt_virtual_machine_create(uint64_t stackCapacity)
{
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

bool volt_virtual_machine_set_instruction_pointer(VirtualMachine* vm, uint64_t offset)
{
    if(vm == nullptr)
        return false;

    vm->SetInstructionPointerOffset(offset);
    return true;
}

uint64_t volt_virtual_machine_get_instruction_pointer(VirtualMachine* vm)
{
    if(vm == nullptr)
        return 0;

    return vm->GetInstructionPointer();
}

ExecutionStatus volt_virtual_machine_run(VirtualMachine* vm)
{
    if(vm == nullptr)
        return ExecutionStatus::Error;
    return vm->Run();
}

ExecutionStatus volt_virtual_machine_call(VirtualMachine* vm, uint64_t labelOffset)
{
    if(vm == nullptr)
        return ExecutionStatus::Error;

    return vm->Call(labelOffset);
}

Object* volt_virtual_machine_get_registers(VirtualMachine* vm, uint64_t* size)
{
    if(vm == nullptr)
        return nullptr;

    *size = vm->GetRegisterCapacity();
    return vm->GetRegisters();
}

Stack<Object>* volt_virtual_machine_get_stack(VirtualMachine* vm)
{
    if(vm == nullptr)
        return nullptr;

    return vm->GetStack();
}

int64_t volt_virtual_machine_get_compare_flag(VirtualMachine* vm)
{
    if(vm == nullptr)
        return 0;

    return vm->GetCompareFlag();
}

int64_t volt_virtual_machine_get_zero_flag(VirtualMachine* vm)
{
    if(vm == nullptr)
        return 0;

    return vm->GetZeroFlag();
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

void volt_stack_clear(Stack<Object> *stack)
{
    if(stack == nullptr)
        return;
    stack->Clear();
}

bool volt_stack_push(Stack<Object>* stack, Object obj, Type type)
{
    if(stack == nullptr)
        return false;
    return stack->Push(obj);
}

bool volt_stack_pop(Stack<Object>* stack, Object* obj)
{
    if(stack == nullptr)
        return false;
    return stack->Pop(*obj);
}

Type volt_stack_get_top_type(Stack<Object>* stack)
{
    if(stack == nullptr)
        return Type::Undefined;
    return stack->GetTopType();
}

bool volt_stack_check_type(Stack<Object>* stack, Type type, int64_t index)
{
    if(stack == nullptr)
        return false;
    return stack->CheckType(type, index);
}

uint64_t volt_stack_get_capacity(Stack<Object>* stack)
{
    if(stack == nullptr)
        return 0;
    return stack->GetCapacity();
}

uint64_t volt_stack_get_count(Stack<Object>* stack)
{
    if(stack == nullptr)
        return 0;
    return stack->GetSize();
}

void volt_free_char_pointer(char* ptr)
{
    if(ptr == nullptr)
        return;
    
    delete[] ptr;
    ptr = nullptr;
}