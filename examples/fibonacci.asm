section data
    startText db : "Calculating first {:d} numbers of the fibonacci sequence:\n"
    iterations dq : 20
    counter dq : 0
section text
init:
    push iterations
    push startText
    call printf
    
    mov eax 1
    mov ebx 0
    mov edx 1
loop:
    cmp counter iterations
    jge end
    inc counter
    
    mov eax ebx
    add eax edx
    mov ebx edx
    mov edx eax
    
    push eax
    call printf
    call printf
    
    jmp loop
end:
    hlt