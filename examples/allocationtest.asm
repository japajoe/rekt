section data
    allocationText db : "Allocated {:d} bytes at address {:p}\n"
    testText db : 1024  ;;reserves 1024 bytes, does not put the number 1024 into memory
    infoText db : "Enter some text: "
    numBytes dq : 1024
section text
test_1:
    call prompt_for_input

    push numBytes   ;;testing writing to pre-allocated memory
    push testText
    call fgets
    pop eax
    
    push eax
    call printf
test_2:
    push numBytes   ;;allocate some memory
    call malloc
    pop eax         ;;pop the pointer that malloc gave into eax
    
    push eax        ;;print allocation info
    push numBytes
    push allocationText
    call printf

    call prompt_for_input

    push numBytes   ;;puts some text into the allocated memory
    push eax        
    call fgets
    pop ebx         ;;returns a char* to the string

    push ebx        ;;print the text that you entered
    call printf

    push eax        ;;free memory (could also pass ebx because free takes any type of pointer, assuming it is allocated with malloc)
    call free
    jmp end
prompt_for_input:
    push infoText
    call printf
    ret
end:
    hlt