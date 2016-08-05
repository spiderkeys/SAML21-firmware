#include "sam.h"

// Macros
#define DUMMY __attribute__ ((weak, alias ("Dummy_Handler")))

// Sections
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;

int main();
void __libc_init_array(void);

// Default handler
void Dummy_Handler(void);

// Cortex-M0+ core handlers
DUMMY void NMI_Handler             ( void );
DUMMY void HardFault_Handler       ( void );
DUMMY void SVC_Handler             ( void );
DUMMY void PendSV_Handler          ( void );
DUMMY void SysTick_Handler         ( void );

/* Peripherals handlers */
DUMMY void SYSTEM_Handler          ( void ); /* MCLK, OSC32KCTRL, OSCCTRL, PAC, PM, SUPC, TAL */
DUMMY void WDT_Handler             ( void );
DUMMY void RTC_Handler             ( void );
DUMMY void EIC_Handler             ( void );
DUMMY void NVMCTRL_Handler         ( void );
DUMMY void DMAC_Handler            ( void );

#ifdef ID_USB
DUMMY void USB_Handler             ( void );
#endif

DUMMY void EVSYS_Handler           ( void );
DUMMY void SERCOM0_Handler         ( void );
DUMMY void SERCOM1_Handler         ( void );
DUMMY void SERCOM2_Handler         ( void );
DUMMY void SERCOM3_Handler         ( void );

#ifdef ID_SERCOM4
DUMMY void SERCOM4_Handler         ( void );
#endif
#ifdef ID_SERCOM5
DUMMY void SERCOM5_Handler         ( void );
#endif

DUMMY void TCC0_Handler            ( void );
DUMMY void TCC1_Handler            ( void );
DUMMY void TCC2_Handler            ( void );
DUMMY void TC0_Handler             ( void );
DUMMY void TC1_Handler             ( void );

#ifdef ID_TC2
DUMMY void TC2_Handler             ( void );
#endif
#ifdef ID_TC3
DUMMY void TC3_Handler             ( void );
#endif
DUMMY void TC4_Handler             ( void );
#ifdef ID_ADC
DUMMY void ADC_Handler             ( void );
#endif
#ifdef ID_AC
DUMMY void AC_Handler              ( void );
#endif
#ifdef ID_DAC
DUMMY void DAC_Handler             ( void );
#endif
#ifdef ID_PTC
DUMMY void PTC_Handler             ( void );
#endif
#ifdef ID_AES
DUMMY void AES_Handler             ( void );
#endif
#ifdef ID_TRNG
DUMMY void TRNG_Handler            ( void );
#endif

// Exception table
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = 
{
        // Configure Initial Stack Pointer, using linker-generated symbols
        (void*) (&_estack),

        (void*) Reset_Handler,
        (void*) NMI_Handler,
        (void*) HardFault_Handler,
        (void*) (0UL),                  /* Reserved */
        (void*) (0UL),                  /* Reserved */
        (void*) (0UL),                  /* Reserved */
        (void*) (0UL),                  /* Reserved */
        (void*) (0UL),                  /* Reserved */
        (void*) (0UL),                  /* Reserved */
        (void*) (0UL),                  /* Reserved */
        (void*) SVC_Handler,
        (void*) (0UL),                  /* Reserved */
        (void*) (0UL),                  /* Reserved */
        (void*) PendSV_Handler,
        (void*) SysTick_Handler,

        /* Configurable interrupts */
        (void*) SYSTEM_Handler,         /*  0 Main Clock, 32k Oscillators Control, Oscillators Control, Peripheral Access Controller, Power Manager, Supply Controller, Trigger Allocator */
        (void*) WDT_Handler,            /*  1 Watchdog Timer */
        (void*) RTC_Handler,            /*  2 Real-Time Counter */
        (void*) EIC_Handler,            /*  3 External Interrupt Controller */
        (void*) NVMCTRL_Handler,        /*  4 Non-Volatile Memory Controller */
        (void*) DMAC_Handler,           /*  5 Direct Memory Access Controller */

#ifdef ID_USB
        (void*) USB_Handler,            /*  6 Universal Serial Bus */
#else
        (void*) (0UL),                  /* Reserved */
#endif

        (void*) EVSYS_Handler,          /*  7 Event System Interface */
        (void*) SERCOM0_Handler,        /*  8 Serial Communication Interface 0 */
        (void*) SERCOM1_Handler,        /*  9 Serial Communication Interface 1 */
        (void*) SERCOM2_Handler,        /* 10 Serial Communication Interface 2 */
        (void*) SERCOM3_Handler,        /* 11 Serial Communication Interface 3 */

#ifdef ID_SERCOM4
        (void*) SERCOM4_Handler,        /* 12 Serial Communication Interface 4 */
#else
        (void*) (0UL),                  /* Reserved */
#endif

#ifdef ID_SERCOM5
        (void*) SERCOM5_Handler,        /* 13 Serial Communication Interface 5 */
#else
        (void*) (0UL),                  /* Reserved */
#endif

        (void*) TCC0_Handler,           /* 14 Timer Counter Control 0 */
        (void*) TCC1_Handler,           /* 15 Timer Counter Control 1 */
        (void*) TCC2_Handler,           /* 16 Timer Counter Control 2 */
        (void*) TC0_Handler,            /* 17 Basic Timer Counter 0 */
        (void*) TC1_Handler,            /* 18 Basic Timer Counter 1 */

#ifdef ID_TC2
        (void*) TC2_Handler,            /* 19 Basic Timer Counter 2 */
#else
        (void*) (0UL),                  /* Reserved */
#endif

#ifdef ID_TC3
        (void*) TC3_Handler,            /* 20 Basic Timer Counter 3 */
#else
        (void*) (0UL),                  /* Reserved */
#endif

        (void*) TC4_Handler,            /* 21 Basic Timer Counter 4 */

#ifdef ID_ADC
        (void*) ADC_Handler,            /* 22 Analog Digital Converter */
#else
        (void*) (0UL),                  /* Reserved */
#endif

#ifdef ID_AC
        (void*) AC_Handler,             /* 23 Analog Comparators */
#else
        (void*) (0UL),                  /* Reserved */
#endif

#ifdef ID_DAC
        (void*) DAC_Handler,            /* 24 Digital-to-Analog Converter */
#else
        (void*) (0UL),                  /* Reserved */
#endif

#ifdef ID_PTC
        (void*) PTC_Handler,            /* 25 Peripheral Touch Controller */
#else
        (void*) (0UL),                  /* Reserved */
#endif

#ifdef ID_AES
        (void*) AES_Handler,            /* 26 Advanced Encryption Standard */
#else
        (void*) (0UL),                  /* Reserved */
#endif

#ifdef ID_TRNG
        (void*) TRNG_Handler,           /* 27 True Random Generator */
#else
        (void*) (0UL),                  /* Reserved */
#endif

        (void*) (0UL)                   /* Reserved */
};

// Called on system resets
void Reset_Handler(void)
{
        uint32_t *pSrc, *pDest;

        // Initialize the relocate segment
        pSrc    = &_etext;
        pDest   = &_srelocate;

        if (pSrc != pDest) 
        {
                for (; pDest < &_erelocate;) 
                {
                        *pDest++ = *pSrc++;
                }
        }

        // Clear the zero segment
        for (pDest = &_szero; pDest < &_ezero;) 
        {
                *pDest++ = 0;
        }

        // Set the vector table base address
        pSrc = (uint32_t *)&_sfixed;
        SCB->VTOR = ((uint32_t) pSrc & SCB_VTOR_TBLOFF_Msk);

        // Overwriting the default value of the NVMCTRL.CTRLB.MANW bit (errata reference 13134)
        NVMCTRL->CTRLB.bit.MANW = 1;

        // Initialize the C library
        __libc_init_array();

        // Branch to main function
        main();

        // Infinite loop
        while (1);
}

// Default interrupt handler for unused IRQs.
void Dummy_Handler(void)
{
        while (1) {}
}
