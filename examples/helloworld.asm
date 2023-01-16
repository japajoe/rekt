section data
    helloText db : "Hello, world!\n"
section text
    push helloText
    call printf
    hlt