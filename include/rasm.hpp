#ifndef REKT_HPP
#define REKT_HPP

#include <LibraryDefinitions.hpp>
#include <Compilation/Compiler.hpp>
#include <Core/Specification.hpp>
#include <Core/Stack.hpp>
#include <Core/Assembly.hpp>
#include <Core/VirtualMachine.hpp>
#include <Utilities/File.hpp>

using namespace REKT;

extern "C" REKT_API_EXPORT void rekt_modules_load(void);
extern "C" REKT_API_EXPORT void rekt_modules_dispose(void);
extern "C" REKT_API_EXPORT bool rekt_function_register(const char *name, REKTFunction fn_ptr);

extern "C" REKT_API_EXPORT Assembly* rekt_assembly_create(void);
extern "C" REKT_API_EXPORT void rekt_assembly_destroy(Assembly* assembly);
extern "C" REKT_API_EXPORT uint64_t rekt_assembly_get_num_instructions(Assembly* assembly);
extern "C" REKT_API_EXPORT bool rekt_assembly_get_symbol_info(Assembly* assembly, const char* name, uint64_t* startOffset, uint64_t* size, Type* type);
extern "C" REKT_API_EXPORT bool rekt_assembly_get_label_info(Assembly* assembly, const char* name, uint64_t* offset);
extern "C" REKT_API_EXPORT char** rekt_assembly_get_symbols(Assembly* assembly, uint64_t* count);
extern "C" REKT_API_EXPORT char** rekt_assembly_get_labels(Assembly* assembly, uint64_t* count);
extern "C" REKT_API_EXPORT OpCode rekt_assembly_get_instruction_opcode(Assembly* assembly, uint64_t offset);

extern "C" REKT_API_EXPORT VirtualMachine* rekt_virtual_machine_create(uint64_t stackCapacity);
extern "C" REKT_API_EXPORT void rekt_virtual_machine_destroy(VirtualMachine* vm);
extern "C" REKT_API_EXPORT bool rekt_virtual_machine_load_assembly(VirtualMachine* vm, Assembly* assembly);
extern "C" REKT_API_EXPORT bool rekt_virtual_machine_reset(VirtualMachine* vm);
extern "C" REKT_API_EXPORT bool rekt_virtual_machine_set_instruction_pointer(VirtualMachine* vm, uint64_t offset);
extern "C" REKT_API_EXPORT uint64_t rekt_virtual_machine_get_instruction_pointer(VirtualMachine* vm);
extern "C" REKT_API_EXPORT ExecutionStatus rekt_virtual_machine_run(VirtualMachine* vm);
extern "C" REKT_API_EXPORT ExecutionStatus rekt_virtual_machine_call(VirtualMachine* vm, uint64_t labelOffset);
extern "C" REKT_API_EXPORT Object* rekt_virtual_machine_get_registers(VirtualMachine* vm, uint64_t* size);
extern "C" REKT_API_EXPORT Stack<Object>* rekt_virtual_machine_get_stack(VirtualMachine* vm);
extern "C" REKT_API_EXPORT int64_t rekt_virtual_machine_get_compare_flag(VirtualMachine* vm);
extern "C" REKT_API_EXPORT int64_t rekt_virtual_machine_get_zero_flag(VirtualMachine* vm);

extern "C" REKT_API_EXPORT Compiler* rekt_compiler_create(void);
extern "C" REKT_API_EXPORT void rekt_compiler_destroy(Compiler* compiler);
extern "C" REKT_API_EXPORT bool rekt_compile_from_text(Compiler* compiler, const char* source, Assembly* assembly);
extern "C" REKT_API_EXPORT bool rekt_compile_from_file(Compiler* compiler, const char* filepath, Assembly* assembly);

extern "C" REKT_API_EXPORT void rekt_stack_clear(Stack<Object> *stack);
extern "C" REKT_API_EXPORT bool rekt_stack_push(Stack<Object>* stack, Object obj, Type type);
extern "C" REKT_API_EXPORT bool rekt_stack_pop(Stack<Object>* stack, Object* obj);
extern "C" REKT_API_EXPORT Type rekt_stack_get_top_type(Stack<Object>* stack);
extern "C" REKT_API_EXPORT bool rekt_stack_check_type(Stack<Object>* stack, Type type, int64_t index);
extern "C" REKT_API_EXPORT uint64_t rekt_stack_get_capacity(Stack<Object>* stack);
extern "C" REKT_API_EXPORT uint64_t rekt_stack_get_count(Stack<Object>* stack);

extern "C" REKT_API_EXPORT void rekt_free_char_pointer(char* ptr);

#endif
