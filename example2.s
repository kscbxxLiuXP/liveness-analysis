        .file   "example.c"
        .text
        .section        .rodata
.LC0:
        .string "%d\n"
.LC1:
        .string "%d "
        .text
        .globl  main
        .type   main, @function
main:
.LFB15:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movl    $17, -8(%rbp)
        movl    -8(%rbp), %eax
        cmpl    $5, %eax
        setg    %al
        testb   %al, %al
        je      .L2
        movl    -8(%rbp), %eax
        addl    $5, %eax
        movl    %eax, -8(%rbp)
        jmp     .L3
.L2:
        movl    -8(%rbp), %eax
        subl    $5, %eax
        movl    %eax, -8(%rbp)
.L3:
        movl    -8(%rbp), %eax
        movl    %eax, %esi
        movl    $.LC0, %edi
        movl    $0, %eax
        call    printf
        movl    $0, -4(%rbp)
.L5:
        movl    -8(%rbp), %eax
        cltd
        xorl    %edx, %eax
        subl    %edx, %eax
        cmpl    %eax, -4(%rbp)
        setl    %al
        testb   %al, %al
        je      .L4
        movl    -8(%rbp), %edx
        movl    -4(%rbp), %eax
        addl    %edx, %eax
        movl    %eax, %esi
        movl    $.LC1, %edi
        movl    $0, %eax
        call    printf
        addl    $1, -4(%rbp)
        jmp     .L5
.L4:
        movl    -8(%rbp), %eax
        addl    $7, %eax
        movl    %eax, -8(%rbp)
        movl    $0, %eax
        leave
        ret
.LFE15:
        .size   main, .-main
        .ident  "GCC: (GNU) 8.5.0 20210514 (Red Hat 8.5.0-21)"
        .section        .note.GNU-stack,"",@progbits