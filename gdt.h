#ifndef __GDT_h
#define __GDT_h

#include "types.h"

    class GlobalDescriptorTable{


        public:
            class SegmentDescriptor{
                private:
                    uint16_t limit_lo; 
                    uint16_t base_lo; //pointer
                    uint8_t base_hi; //pointerextension
                    uint8_t type; //excess
                    uint8_t flags_limit_hi; //flaglimit
                    uint8_t base_vhi;
                
                public:
                    SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
                    uint32_t Base();
                    uint32_t Limit();

            } __attribute__((packed));

            //MEMORY SEGMENTS, the code and data segement being spread out is a risk for OS security but honestly. who is going to use this operating system except for me lmao

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



#endif