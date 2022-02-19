#pragma once

#include "types.h"
#include "port.h"

class InterruptManager{
public:
    static uint32_t handleInterrupt(uint8_t interruptNum, uint32_t esp);
};