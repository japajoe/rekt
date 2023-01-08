# volt
A stack and register based virtual machine which can compile and execute arbitrary code in runtime.

Support for integer types like
- int64/uint64
- double

# Dependencies
- None

# About
This is a similar project to https://github.com/japajoe/StackVMCPP but with quite a lot of changes. I have decided I don't want to deal with all these push/pop instructions anymore, so I got rid of them. I also felt little need to support so many numeric types because it only complicates matters in an already complicated project. There is now also support for defining string literals, which is so much more fun than pushing individual characters to the stack.

As anything in life, there are always ifs and buts. I can not guarantee this project solves your problems, and I can not guarantee it has no bugs or problems. In fact there must be issues that I'm either not aware of, or haven't found a solution for yet. Please open an issue if you find something, because only then I know people actually use this. I personally have used this successfully in different applications where there was a need to have an embedded programming language with a small footprint. I have found it reasonably fast and pretty capable.

# News
- As of 01/05/2023 it is possible to print formatted strings. For more info on what string formatting options there are, see https://github.com/fmtlib/fmt

# Note
In contrary to my previous project, the instruction opcodes are case sensitive and MUST be lower case!

# Example use
```cpp
#include <iostream>
#include <chrono>
#include <memory>
#include <exception>
#include <IO/File.hpp>
#include <Compilation/Compiler.hpp>
#include <Compilation/Instruction.hpp>
#include <Core/VirtualMachine.hpp>
#include <Core/Assembly.hpp>
#include <Modules/ModuleLoader.hpp>
#include <Modules/SystemModule.hpp>
#include <Modules/MemoryModule.hpp>
#include <Modules/MathModule.hpp>

using namespace VoltLang;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

int main(int argc, char** argv)
{
    std::string filepath = "helloworld.vlt";

    if(argc > 1)
    {
        filepath = std::string(argv[1]);
    }

    //Load some standard modules so you can call functions such as printf etc.
    ModuleLoader::Load<SystemModule>();
    ModuleLoader::Load<MemoryModule>();
    ModuleLoader::Load<MathModule>();

    Assembly assembly;
    VirtualMachine machine;

    if (!File::Exists(filepath))
    {
        std::cout << "File does not exist: " << filepath << std::endl;
        return 1;
    }

    std::string source = File::ReadAllText(filepath);

    Compiler compiler;

    if(compiler.Compile(source, &assembly))
    {
        machine.LoadAssembly(&assembly);

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

    //Release resources allocated by modules (if any).
    ModuleLoader::Dispose();

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