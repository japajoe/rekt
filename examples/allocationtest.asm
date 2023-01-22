section data
    allocationText db : "Allocated {:d} bytes at address {:p}\n"
    testText db : 1024                  ;reserves 1024 bytes, does not put the number 1024 into memory
    infoText db : "Enter some text: "
    numBytes dq : 512                   ;the number of bytes to allocate
    somePointer dp : 0                  ;declares a pointer type
section text
test_1:
    call prompt_for_input

    push numBytes                       ;test writing to pre-allocated memory
    push testText
    call fgets
    pop eax                             ;returns a pointer to the string, could also pop into any pointer type such as 'somePointer'
    
    push eax
    call printf
test_2:
    push numBytes                       ;dynamically allocate some memory
    call malloc
    pop somePointer                     ;pop the pointer that malloc gave into somePointer
    
    push somePointer                    ;print allocation info
    push numBytes
    push allocationText
    call printf

    call prompt_for_input

    push numBytes                       ;puts some text into the allocated memory
    push somePointer        
    call fgets
    pop somePointer                     ;returns a char* to the string

    push somePointer                    ;print the text that you entered
    call printf

    push somePointer                    ;free memory (only call free on memory allocated with malloc)
    call free
    jmp end
prompt_for_input:
    push infoText
    call printf
    ret
end:
    hlt