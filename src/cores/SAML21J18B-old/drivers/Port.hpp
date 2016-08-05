#pragma once

namespace port
{
    constexpr uint8_t PORTA = 0;
    constexpr uint8_t PORTB = 1;
    constexpr uint8_t PORTC = 2;

    template< uint8_t port, uint8_t pin >
    class CDigitalPin
    {
    public:
        static void Set()
        {
            PORT->Group[port].OUTSET.reg = (1 << pin);
        }

        static void Clear()
        {
            PORT->Group[port].OUTCLR.reg = (1 << pin);
        }

        static void Toggle()
        {
            PORT->Group[port].OUTTGL.reg = (1 << pin);
        }

        static void Write( int value )
        {
            if( value )
            {
                PORT->Group[port].OUTSET.reg = (1 << pin);
            }
            else
            {
                PORT->Group[port].OUTCLR.reg = (1 << pin);
            }
        }
    };

    template< uint8_t port, uint8_t pin >
    class CAnalogPin
    {
    public:
        static void Read( float &valueOut )
        {
            valueOut = 0.0f;
        }
    };
}