#pragma once

#include "types.h"

class GlobalDescriptorTable
{
    public:

        class SegmentDescriptor
        {
            private:
                uint16_t limit_lo;
                uint16_t base_lo; //pointer
                uint8_t base_hi; //pointer extension
                uint8_t type; //excess
                uint8_t limit_hi; //flaglimit
                uint8_t base_vhi;

            public:
                SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
                uint32_t Base();
                uint32_t Limit();
        } __attribute__((packed));

    private:
        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

    public:

        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        uint16_t CodeSegmentSelector();
        uint16_t DataSegmentSelector();
};

