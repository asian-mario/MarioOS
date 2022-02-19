#include "types.h" //Our header file
#include "gdt.h" //global descriptor table



//stdlib cpp include replacements
void print(char* str){
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x = 0, y = 0; 

    for(int i = 0; str[i] != '\0'; i++){

        switch(str[i]){

            case '\n': //new line e.g if we put \n in our code
                y++;
                x = 0;
                break;


            default: //normal case that we normall would have
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


extern "C" void kernelMain(void* multiboot_struct, uint32_t){ //magic num int is for the bootloader to recognise this cpp program as a kernel 
    print("MARIO OS  ----  IN DEVELOPMENT"); //isnt this obvious
    print("VERSION V.0001 EARLY DEVELOPMENT BUILD");

    GlobalDescriptorTable gdt;

    while(1); //Infinite loop because there is literally nothing else for now
}

