section .text
global dotProduct

dotProduct:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    xorps xmm0, xmm0
    xor rax, rax
    
loop_start:
    cmp rax, rcx
    jge loop_end
    movss xmm1, [rdx + rax*4]
    mulss xmm1, [r8 + rax*4]
    addss xmm0, xmm1
    inc rax
    jmp loop_start
    
loop_end:
    movss [r9], xmm0
    add rsp, 32
    pop rbp
    ret
