#include "gdt.h"

// note, i have forgotten to catch up on this, i am sticking with GDT until further notice. Unfortunately i have also forgotten some aspects of developing this
// more notes, correct commenting and removing comments complaining about my coding will be corrected and removed soon

GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,64*1024*1024, 0x9A), //0x9a == code segment access byte
dataSegmentSelector(0,64*1024*1034, 0x92) //0x92 == data segment access byte
{

    uint32_t i[2];
    i[0] = *((uint32_t*)(this));
    i[1] = sizeof(GlobalDescriptorTable) << 16;

    asm volatile("lgdt (%0)": :"p"(((uint8_t *) i)+2));

}

GlobalDescriptorTable::~GlobalDescriptorTable(){

}
                                                                                            // literally why am i writing this could use paging WHY. 
uint16_t GlobalDescriptorTable::DataSegmentSelector(){
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector(){
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags){
    uint8_t* target = (uint8_t*)this;

    if(limit <= 65536){ //if 16 bit limit
        target[6] = 0x40; //0x40 == 'and'
    } 

    else{
        if((limit & 0xFFF) != 0xFFF)
            limit=(limit >> 12)-1;
        else 
            limit = limit >> 12;

        target[6] = 0xC0;
    }

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;


    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;  //pointer segment, i dont care anymore doing GDT after i remembered paging
    target[7] = (base >> 24) & 0xFF;

    target[5] = flags; //fleg

}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base(){
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];
    return result;
}


uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit(){
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[6] & 0xF;
    result = (result << 8) + target[1];       //shared segment
    result = (result << 8) + target[0];

    if((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;


    return result;
}