#ifndef __PORT_H
#define __PORT_H

#include "types.h"

    class Port{
    protected:
        uint16_t portnumber; //port number are 16 bit
        Port(uint16_t portnumber); //our class
        ~Port();
    };


    class Port8Bit : public Port { 
    public:
        Port8Bit(uint16_t portnumber); //our class
        ~Port8Bit();
        virtual void Write(uint8_t data);
        virtual uint8_t Read();   
    };

    class Port8BitSlow : public Port8Bit{ //inheritance of Port8Bit class. P.S 8bitslow is basically 8bit but... slow.
    public:
        Port8BitSlow(uint16_t portnumber); //port number are 16 bit
        ~Port8BitSlow();
        virtual void Write(uint8_t data);
    };

    class Port16Bit : public Port{
    public:
        Port16Bit(uint16_t portnumber); //our class
        ~Port16Bit();
        virtual void Write(uint16_t data);
        virtual uint16_t Read();
    };

    class Port32Bit : public Port{
    public:
        Port32Bit(uint16_t portnumber); //our class
        ~Port32Bit();
        virtual void Write(uint32_t data);
        virtual uint32_t Read();
    };




    
#endif