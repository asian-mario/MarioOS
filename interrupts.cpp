#include "interrupts.h"

void printf(char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void InterruptManager::SetInterruptDescriptorTableEntry(
    uint8_t interruptNum, 
    uint16_t codeSegmentSelectorOffset,
    void (*handler)(),
    uint8_t DescriptorPrivelageLevel,
    uint8_t descType
){
    const uint8_t IDT_DESC_PRESENT = 0x80;

    interruptDescriptorTable[interruptNum].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
    interruptDescriptorTable[interruptNum].handlerAddressHighBits = (((uint32_t)handler) >> 16) & 0xFFFF;
    interruptDescriptorTable[interruptNum].gdt_codeSegmentSelector =  codeSegmentSelectorOffset;
    interruptDescriptorTable[interruptNum].reserved = 0; 
    interruptDescriptorTable[interruptNum].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivelageLevel&3) << 5);

}

InterruptManager(GlobalDescriptorTable* gdt){
    uint16_t CodeSegment = gdt->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for(uint16_t i = 0; i < 256; i++){
        SetInterruptDescriptorTableEntry(i, CodeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    }

    //shifted by IRQ_BASE
    SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

    InterruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1
    idt.base = (uint32_t)interruptDescriptorTable;
    asm volatile("lidt %0 : : m (idt)")
}
~InterruptManager(){

}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNum, uint32_t esp){
    printf("INTERRUPT");
    
    return esp;
}