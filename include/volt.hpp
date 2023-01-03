#ifndef VOLT_HPP
#define VOLT_HPP

#include <LibraryDefinitions.hpp>
#include <Compilation/Compiler.hpp>
#include <IO/File.hpp>
#include <Compilation/Instruction.hpp>
#include <Core/VirtualMachine.hpp>
#include <Core/Assembly.hpp>
#include <Core/StandardLibrary.hpp>

using namespace VoltLang;

extern "C" VOLT_API_EXPORT void volt_library_init(void);
extern "C" VOLT_API_EXPORT bool volt_function_register(const char* name, VoltVMFunction fn_ptr);

extern "C" VOLT_API_EXPORT Assembly* volt_assembly_create(void);
extern "C" VOLT_API_EXPORT void volt_assembly_destroy(Assembly* assembly);
extern "C" VOLT_API_EXPORT uint64_t volt_assembly_get_num_instructions(Assembly* assembly);
extern "C" VOLT_API_EXPORT bool volt_assembly_get_symbol_info(Assembly* assembly, const char* name, uint64_t* startOffset, uint64_t* size, Type* type);
extern "C" VOLT_API_EXPORT bool volt_assembly_get_label_info(Assembly* assembly, const char* name, uint64_t* offset);
extern "C" VOLT_API_EXPORT char** volt_assembly_get_symbols(Assembly* assembly, uint64_t* count);
extern "C" VOLT_API_EXPORT char** volt_assembly_get_labels(Assembly* assembly, uint64_t* count);

extern "C" VOLT_API_EXPORT VirtualMachine* volt_virtual_machine_create(uint64_t stackCapacity);
extern "C" VOLT_API_EXPORT void volt_virtual_machine_destroy(VirtualMachine* vm);
extern "C" VOLT_API_EXPORT bool volt_virtual_machine_load_assembly(VirtualMachine* vm, Assembly* assembly);
extern "C" VOLT_API_EXPORT bool volt_virtual_machine_reset(VirtualMachine* vm);
extern "C" VOLT_API_EXPORT bool volt_virtual_machine_set_instruction_pointer(VirtualMachine* vm, uint64_t offset);
extern "C" VOLT_API_EXPORT uint64_t volt_virtual_machine_get_instruction_pointer(VirtualMachine* vm);
extern "C" VOLT_API_EXPORT ExecutionStatus volt_virtual_machine_run(VirtualMachine* vm);
extern "C" VOLT_API_EXPORT unsigned char* volt_virtual_machine_get_registers(VirtualMachine* vm, uint64_t* size);
extern "C" VOLT_API_EXPORT Stack* volt_virtual_machine_get_stack(VirtualMachine* vm);

extern "C" VOLT_API_EXPORT Compiler* volt_compiler_create(void);
extern "C" VOLT_API_EXPORT void volt_compiler_destroy(Compiler* compiler);
extern "C" VOLT_API_EXPORT bool volt_compile_from_text(Compiler* compiler, const char* source, Assembly* assembly);
extern "C" VOLT_API_EXPORT bool volt_compile_from_file(Compiler* compiler, const char* filepath, Assembly* assembly);

extern "C" VOLT_API_EXPORT void volt_stack_clear(Stack *stack);
extern "C" VOLT_API_EXPORT bool volt_stack_push(Stack* stack, unsigned char* data, Type type, uint64_t* stackOffset);
extern "C" VOLT_API_EXPORT bool volt_stack_push_double(Stack* stack, double value, uint64_t* stackOffset);
extern "C" VOLT_API_EXPORT bool volt_stack_push_int64(Stack* stack, int64_t value, uint64_t* stackOffset);
extern "C" VOLT_API_EXPORT bool volt_stack_push_uint64(Stack* stack, uint64_t value, uint64_t* stackOffset);
extern "C" VOLT_API_EXPORT bool volt_stack_push_string(Stack* stack, char* value, uint64_t* stackOffset);
extern "C" VOLT_API_EXPORT bool volt_stack_pop(Stack *stack, byte *target, uint64_t *stackOffset);
extern "C" VOLT_API_EXPORT unsigned char* volt_stack_get_buffer(Stack* stack);
extern "C" VOLT_API_EXPORT unsigned char* volt_stack_get_top(Stack* stack);
extern "C" VOLT_API_EXPORT bool volt_stack_check_type(Stack* stack, Type type, int64_t index);
extern "C" VOLT_API_EXPORT Type volt_stack_get_top_type(Stack* stack);
extern "C" VOLT_API_EXPORT uint64_t volt_stack_get_capacity(Stack* stack);
extern "C" VOLT_API_EXPORT uint64_t volt_stack_get_size(Stack* stack);
extern "C" VOLT_API_EXPORT uint64_t volt_stack_get_count(Stack* stack);

extern "C" VOLT_API_EXPORT void volt_free_char_pointer(char* ptr);

extern "C" VOLT_API_EXPORT void volt_get_module_address(const char* name, uintptr_t* address);

#endif