#include "interrupts.h"

void printf(char* str);

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNum, uint32_t esp){
    printf("INTERRUPT");
    
    return esp;
}