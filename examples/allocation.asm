section data
    allocationText db : "Allocated {:d} bytes at address {:p}\n"
    infoText db : "Enter some text: "
    someText db : 0                     ;Uninitialized pointer
    numBytes dq : 512                   ;The number of bytes to allocate
section text
run_test:
    push numBytes                       ;dynamically allocate some memory
    call malloc
    pop someText                        ;pop the pointer that malloc gave into someText
    
    push someText                       ;print allocation info
    push numBytes
    push allocationText
    call printf

    call prompt_for_input

    push numBytes                       ;puts some text into the allocated memory
    push someText        
    call fgets
    pop someText                        ;returns a char* to the string

    push someText                       ;print the text that you entered
    call printf

    push someText                       ;free memory (only call free on memory allocated with malloc)
    call free
    jmp end
prompt_for_input:
    push infoText
    call printf
    ret
end:
    hlt