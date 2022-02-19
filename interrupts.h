#pragma once

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager{
protected:
    struct GateDescriptor{
        uint16_t handlerAddressLowBits;
        uint16_t gdt_codeSegmentSelector;
        uint8_t reserved; 
        uint8_t access;
        uint16_t handlerAddressHighBits;


    }__attribute__{{packed}};

    static GateDescriptor interruptDescriptorTable[256];

    static void SetInterruptDescriptorTableEntry(
        uint8_t interruptNum, 
        uint16_t codeSegmentSelectorOffset,
        void (*handler)(),
        uint8_t DescriptorPrivelageLevel,
        uint8_t descType
    )

    struct InterruptDescriptorTablePointer{
        uint16_t size;
        uint32_t base;

    }__attribute__{{packed}};
public:
    InterruptManager(GlobalDescriptorTable* gdt);
    ~InterruptManager();

    static uint32_t handleInterrupt(uint8_t interruptNum, uint32_t esp);

    // create handler for each interrupt types

    static void IgnoreInterrutRequest(); 

    static void HandleInterruptRequest0x00(); //timer
    static void HandleInterruptRequest0x01(); //keyboard
};