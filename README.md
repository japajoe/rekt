# rekt
A stack and register based virtual machine which can compile and execute arbitrary code in runtime.

Support for types like
- int64/uint64
- double
- pointers

# News
- 01/22/2023: Added 'dp' directive to declare pointer types. With this you can hold on to any pointer, without having to sacrifice registers to store them.
- 01/18/2023: Renamed project because all cool names were taken and I wasn't feeling super creative.
- 01/16/2023: Rewrote entire project. All entities on the stack and in registers are now considered an Object. This is a breaking change, old code is moved to 'legacy' branche.
- 01/05/2023: It is possible to print formatted strings. For more info on what string formatting options there are, see https://github.com/fmtlib/fmt

# Note
The instruction opcodes are case sensitive and MUST be lower case!

# Example use
```cpp
#include <iostream>
#include <chrono>
#include <Compilation/Compiler.hpp>
#include <Core/VirtualMachine.hpp>
#include <Modules/ModuleLoader.hpp>
#include <Modules/SystemModule.hpp>
#include <Utilities/File.hpp>

using namespace REKT;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

int main(int argc, char **argv)
{
    std::string filepath = "fibonacci.asm";

    if(argc > 1)
    {
        filepath = std::string(argv[1]);
    }

    if(!File::Exists(filepath))
    {
        std::cout << "The file does not exist " << filepath << std::endl;
        return 1;
    }

    ModuleLoader::Load<SystemModule>();

    std::string source = File::ReadAllText(filepath);

    Compiler compiler;
    Assembly assembly;
    VirtualMachine machine;

    if(compiler.Compile(source, &assembly))
    {
        if(machine.LoadAssembly(&assembly))
        {
            ExecutionStatus status = ExecutionStatus::Ok;

            auto startTime = high_resolution_clock::now();

            while (status == ExecutionStatus::Ok)
            {
                status = machine.Run();
            }

            auto endTime = high_resolution_clock::now();
            auto elapsedMilliseconds = duration_cast<microseconds>(endTime - startTime).count() * 0.001;

            std::cout << "Execution finished with status " << (int)status << " in " << elapsedMilliseconds << " milliseconds" << std::endl;
        }
    }

    return 0;
}
```

# Building
In the root directory of the folder (where the include and src folder are located), create a directory called build. From within the build directory run one of the following commands
- cmake .. -DBUILD_SHARED_LIBRARY=0
- cmake .. -DBUILD_SHARED_LIBRARY=1

If you pass 0 to BUILD_SHARED_LIBRARY, CMake will configure the makefile to generate an executable. If you pass it 1, it will generate it for a shared library. After running the command run 'make' or whichever tool you use to execute a makefile.



# Instructions
**MOV**
Move a value into a register or into a variable. Registers are able to store any type, variables are constrained to only contain the type they are defined as.
- mov eax ebx
- mov eax myVariable
- mov eax 10
- mov myVariable eax
- mov myVariable anotherVariable
- mov myVariable 123.45

**INC**
Increments the value stored in a register or variable with 1.
- inc eax
- inc myVariable

**DEC**
Decrements the value stored in a register or variable with 1.
- dec eax
- dec myVariable

**ADD**
Adds a value to a value stored in a register or variable.
- add eax 30
- add eax myVariable
- add myVariable 30
- add myVariable eax

**SUB**
Subtract a value from a value stored in a register or variable.
- sub eax 30
- sub eax myVariable
- sub myVariable 30
- sub myVariable eax

**MUL**
Multiplies a value stored in a register or variable with another value.
- mul eax 30
- mul eax myVariable
- mul myVariable 30
- mul myVariable eax

**DIV**
Divides a value stored in a register or variable with another value.
- div eax 30
- div eax myVariable
- div myVariable 30
- div myVariable eax

**PUSH**
Pushes a value to the stack.
- push eax
- push myVariable
- push 10
- push 0.5

**POP**
Pops any value off the top of the stack.
- pop
- pop eax
- pop myVariable

**CMP**
Compares 2 values for equality and sets a flag whether the lefthandside is less than, greater than, or equal to the righthandside.
- cmp eax ebx
- cmp eax myVariable
- cmp eax 99
- cmp myVariable ebx
- cmp myVariable anotherVariable
- cmp myVariable 45

**CALL**
Makes a jump to a specific label defined by the user, OR calls predefined functions provided by your application. A label can be defined above any instruction and it could be seen like a function identifier. If a jump to a label is made, the return address will get placed on top of the stack. Then whenever a RET instruction is being executed, the return address will get popped off the top of the stack and the instruction pointer is set to this address. In order to prevent corruption of the stack, it is very important that you take good care of what you push and pop to/from the stack.
- call doWork
- call printInfo
- call doCalculation

**RET**
The RET instruction sets the instructionpointer back to the instruction that comes right after the CALL instruction. See description about the CALL opcode to get an understanding of how these two instructions relate.

**JMP**
Unconditional jump to a label
- jmp someLabel

**JE**
Jump to label if CMP instruction evaluated to equal.
- je someLabel

**JNE**
Jump to label if CMP instruction evaluated to not equal.
- jne someLabel

**JG**
Jump to label if CMP instruction evaluated to greater than.
- jg someLabel

**JGE**
Jump to label if CMP instruction evaluated to greater than or equal.
- jge someLabel

**JL**
Jump to label if CMP instruction evaluated to less than.
- jl someLabel

**JLE**
Jump to label if CMP instruction evaluated to less than or equal.
- jle someLabel

**JZ**
Jump to label if result of a add/sub/mul/div instruction equals to zero.
- jz someLabel

**JNZ**
Jump to label if result of a add/sub/mul/div instruction does not equal zero.
- jz someLabel

**NOP**
This opcode literally does nothing. In x86 assembly it can be used to disable instructions by overwriting them with NOP instructions

**HLT**
This effectively stops the program.
