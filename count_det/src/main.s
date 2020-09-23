.text
.global count_det

count_det:
    ldr r1, [r0], #4
    ldr r2, [r0], #4
    ldr r3, [r0], #4
    ldr r4, [r0], #4
    ldr r5, [r0], #4
    ldr r6, [r0], #4
    ldr r7, [r0], #4
    ldr r8, [r0], #4
    ldr r9, [r0], #4
    mul r0, r5, r9
    mul r5, r5, r7
    mul r7, r7, r6
    mul r6, r6, r8
    mul r8, r8, r4   
    mul r4, r4, r9
    sub r0, r0, r6
    sub r7, r7, r4
    sub r8, r8, r5
    mul r0, r0, r1
    mul r2, r2, r7
    mul r3, r3, r8
    add r2, r2, r3
    add r0, r0, r2
    mov r1, r0
    bx lr
    