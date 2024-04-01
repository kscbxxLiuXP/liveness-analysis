        .file   "example.c"
        .text
        .globl  add1
        .type   add1, @function
add1:
.LFB6:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        movq    %rsp, %rbp
        .cfi_def_cfa_register 6
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movl    (%rax), %eax
        leal    1(%rax), %edx
        movq    -8(%rbp), %rax
        movl    %edx, (%rax)
        nop
        popq    %rbp
        .cfi_def_cfa 7, 8
        ret
        .cfi_endproc
.LFE6:
        .size   add1, .-add1
        .section        .rodata
.LC0:
        .string "%d\n"
.LC1:
        .string "%d "
        .text
        .globl  main
        .type   main, @function
main:
.LFB7:
        .cfi_startproc
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        movq    %rsp, %rbp
        .cfi_def_cfa_register 6
        subq    $16, %rsp
        movl    $17, -8(%rbp)
        movl    -8(%rbp), %eax
        cmpl    $5, %eax
        jle     .L3
        movl    -8(%rbp), %eax
        addl    $5, %eax
        movl    %eax, -8(%rbp)
        jmp     .L4
.L3:
        movl    -8(%rbp), %eax
        subl    $5, %eax
        movl    %eax, -8(%rbp)
.L4:
        leaq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    add1
        movl    -8(%rbp), %eax
        movl    %eax, %esi
        movl    $.LC0, %edi
        movl    $0, %eax
        call    printf
        movl    $0, -4(%rbp)
        jmp     .L5
.L6:
        movl    -8(%rbp), %edx
        movl    -4(%rbp), %eax
        addl    %edx, %eax
        movl    %eax, %esi
        movl    $.LC1, %edi
        movl    $0, %eax
        call    printf
        addl    $1, -4(%rbp)
.L5:
        movl    -8(%rbp), %eax
        cltd
        xorl    %edx, %eax
        subl    %edx, %eax
        cmpl    %eax, -4(%rbp)
        jl      .L6
        movl    -8(%rbp), %eax
        addl    $7, %eax
        movl    %eax, -8(%rbp)
        movl    $0, %eax
        leave
        .cfi_def_cfa 7, 8
        ret
        .cfi_endproc
.LFE7:
        .size   main, .-main
        .ident  "GCC: (GNU) 8.5.0 20210514 (Red Hat 8.5.0-21)"
        .section        .note.GNU-stack,"",@progbits