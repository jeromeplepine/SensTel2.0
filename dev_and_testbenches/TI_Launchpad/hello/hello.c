//*****************************************************************************
//
// hello.c - Simple SSI demo.
//
// This example demonstrates SSI communication between a master (SSI2) and a
// slave (SSI0).
// Use the code below, as well as a EK-TM4C123GXL Launchpad devboard to try it.
// Pay attention to PB4 (SSI2 clock pin) and PA5 (SSI0 tx pin).
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"


#define NUM_SSI_DATA 8
#define SSI_RESOLUTION  12
const uint16_t pui8DataTx[NUM_SSI_DATA] =
//{0x88, 0xF8, 0xF8, 0x88, 0x01, 0x1F, 0x1F, 0x01};
//{0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
//{0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66};
//{0xDE, 0xAD, 0xBE, 0xEF, 0xFA, 0xCE, 0xF0, 0x0D, 0xAB, 0xCD, 0xEF, 0xD0};
{0x7DE, 0x7AD, 0x7BE, 0x7EF, 0x7FA, 0x7CE, 0x7F0, 0x70D};

uint8_t Reverse(uint8_t ui8Number)
{
    uint8_t ui8Index;
    uint8_t ui8ReversedNumber = 0;
    for(ui8Index=0; ui8Index<8; ui8Index++)
    {
        ui8ReversedNumber = ui8ReversedNumber << 1;
        ui8ReversedNumber |= ((1 << ui8Index) & ui8Number) >> ui8Index;
    }
return ui8ReversedNumber;
}

//*****************************************************************************
// SSI peripherals init functions:
// Freescale mode 3 (clk polarity HI, clk phase HI)
// Slave loads a 16bit word in its transmit FIFO and then the master outputs a msg.
// This enables the master's clock which in turn initiates the slave's serial
// transmission. On every clock rising edge, the slave's data is valid.
//
//*****************************************************************************

uint8_t ConfigSSI0(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_2);

    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_SLAVE, 10000, SSI_RESOLUTION);
//    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_SLAVE, 10000, 16);
    SSIEnable(SSI0_BASE);
    return 1;
}

uint8_t ConfigSSI2(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB4_SSI2CLK);
    GPIOPinConfigure(GPIO_PB5_SSI2FSS);
    GPIOPinConfigure(GPIO_PB7_SSI2TX);
    GPIOPinConfigure(GPIO_PB6_SSI2RX);
    GPIOPinTypeSSI(GPIO_PORTB_BASE,GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4);

    SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_MASTER, 10000, 16);
    SSIEnable(SSI2_BASE);
}
//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Hello World (hello)</h1>
//!
//! A very simple ``hello world'' example.  It simply displays ``Hello World!''
//! on the UART and is a starting point for more complicated applications.
//!
//! UART0, connected to the Virtual Serial Port and running at
//! 115,200, 8-N-1, is used to display messages from this application.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif



//*****************************************************************************
//
// Use SSI0 as a slave and SSI2 as a master.
//
//*****************************************************************************

int main(void)
{
    uint32_t ui32Index;
    uint32_t ui32Data;

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    ConfigSSI0();
    ConfigSSI2();


    while(1)
    {
        for(ui32Index = 0; ui32Index < NUM_SSI_DATA; ui32Index++)
        {
//            ui32Data = (Reverse(pui8DataTx[ui32Index]) << 8) + (1 << ui32Index);
            ui32Data = pui8DataTx[ui32Index];
            SSIDataPut(SSI0_BASE, ui32Data);
//            SSIDataPut(SSI2_BASE, ui32Data);
//            while(SSIBusy(SSI0_BASE))
//            {
//            }
        }
    }
}
