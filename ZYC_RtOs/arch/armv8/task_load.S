/*
 * 描述: void OsTskContextLoad(uintptr_t stackPointer)
 */
    .globl OsTskContextLoad
    .type OsTskContextLoad, @function
    .align 4
OsTskContextLoad:
    mov sp,x0
    blr x1
