.set IRQ_BASE, 0x20

.section .text

.extern _ZN16InterruptManager15handleInterruptEht
.global _ZN16InterruptManager22IgnoreInterruptRequestEv


.macro HandleException num
.global _ZN16InterruptManager16HandleException\num\()Ev

_ZN16InterruptManager16HandleException\num\()Ev:
    movb $\num, (interruptNum)
    jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev

_ZN16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptNum)
    jmp int_bottom
.endm

# e v e r y i n t e r r u p t
HandleInterruptRequest 0x00
HandleInterruptRequest 0x01

int_bottom:

    pusha 
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs


    pushl %esp
    push (interruptNum)
    call _ZN16InterruptManager15handleInterruptEht

    movl %eax, %esp

    # reverse order
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

_ZN16InterruptManager22IgnoreInterruptRequestEv:

    # finished handling interrupt
    iret


.data
    interruptNum: .byte 0