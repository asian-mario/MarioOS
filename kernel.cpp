#include "types.h" 
#include "gdt.h" 
#include "interrupts.h" 



//stdlib cpp include replacements
void printf(char* str){
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x = 0, y = 0; 

    for(int i = 0; str[i] != '\0'; i++){

        switch(str[i]){

            case '\n': 
                y++;
                x = 0;
                break;


            default: 
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;

        }
                
        if(x >= 80){
            y++;
            x = 0;
        }

        if(y >= 25){ //cleaning

            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';

            x = 0;
            y = 0;
        }
    }
}

typedef void(*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors(){
    for(constructor* i = &start_ctors; i != end_ctors; i++){
        (*i)();
    }
}


extern "C" void kernelMain(const void* multiboot_struct, uint32_t){ //magic num int is for the bootloader to recognise this cpp program as a kernel 
    printf("MARIO OS  ----  IN DEVELOPMENT \n"); 
    printf("EARLY DEVELOPMENT BUILD");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);

    interrupts.Activate();

    while(1); 
}

