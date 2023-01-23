;This code does the following things:
; - Dynamically allocate memory and return a pointer to the memory
; - Store the pointer in a separate variable which is used for operations
; - Cast the void* to a int64*
; - Loop through all bytes in the data and assign a value to each index, then increment the pointer by 8 bytes
; - Reset the loop counter and the pointer back to its base address
; - Loop through the data again and print the result to the console
; - Free the memory
section data
    statusText db : "Done!\n"
    dataPtr db : 0  ;Uninitialized pointer
    dataPtrCopy db : 0  ;Uninitialized pointer
    numBytes dq : 512   ;In order for this to work correctly, this value must be a multiple of 8
    counter dq : 0      ;Don't set manually, counter should just start at 0
    iterations dq : 0   ;Don't set this manually, will get calculated in 'init'
section text
init:
    ;;Dynamically determine how many items to iterate through, so the entire memory space is used
    mov iterations numBytes
    div iterations 8
    ;Allocate some memory
    push numBytes
    call malloc
    pop dataPtr
    ;Initialize memory to 0
    push numBytes
    push 0
    push dataPtr
    call memset    
cast_to_target_type:
    ;Convert void* to int64* (we can't just start writing to a void* so we need to convert it)
    ;We don't use the original pointer directly because it's useful to know where our memory begins
    push dataPtr
    call to_int64_ptr
    pop dataPtrCopy
set_data_loop:
    cmp counter iterations
    jge reset_counter
    mov dataPtrCopy counter
    call increment_memory
    inc counter
    jmp set_data_loop
reset_counter:
    ;Set counter back to 0
    mov counter 0    
    mov dataPtrCopy dataPtr
display_results:
    cmp counter iterations
    jge dispose
    inc counter
    call dump_memory
    call increment_memory
    jmp display_results
dispose:
    push dataPtr
    call free
    push statusText
    call printf
    hlt
increment_memory:
    push 8
    push dataPtrCopy
    call memadd
    pop dataPtrCopy
    ret
dump_memory:
    push dataPtrCopy
    call printf
    call printf
    ret