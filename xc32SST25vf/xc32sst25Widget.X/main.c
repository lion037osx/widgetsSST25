/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
//void f_interrupt(void);
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2	
#pragma config FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL

#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif
#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */
#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"           /* User funct/params, such as InitApp             */
#include "SST25VF016.h"
#include "Compiler.h"
#include "HardwareProfile.h"
#include "uart2.h"
#include "interrupts.h"

#ifdef __WRITE_LOGO__
#include "logo.h"
    //#include "logo480.h"
   // #include "domotics13_24bitsC32.h"
#endif

void read_sector_sst(void);
int flag=0;
char rxUart2[64];
BYTE *memory;

int32_t main(void)
{   
static DWORD address=0x0000;
static BYTE byteTmp;
static DWORD byteReads=CANT_DATA_READ;  
static char strSST[64];
static DWORD sizeLogo;
static int flagWrite;
static int counter=0;
DDPCONbits.JTAGEN = 0;
SYSTEMConfigPerformance(GetSystemClock());

TRISBbits.TRISB4=1;
TRISAbits.TRISA3=0;
TRISAbits.TRISA0=0;
PORTSetPinsDigitalIn(IOPORT_B,BIT_4);
UART2Init();
INTEnable(INT_SOURCE_UART_RX(UART2), INT_ENABLED);
INTSetVectorPriority(INT_VECTOR_UART(UART2), INT_PRIORITY_LEVEL_2);
INTSetVectorSubPriority(INT_VECTOR_UART(UART2), INT_SUB_PRIORITY_LEVEL_0);
INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
UART2PrintString("\r\nFirmware XC32 sst25vf\r\n");
SST25Init();
INTEnableInterrupts();
CFG_TRISA0();
CFG_TRISA1();
CFG_TRISA2();
CFG_TRISA3();
LED_RA0=0;
LED_RA1=0;
LED_RA2=0;
LED_RA3=0;
sizeLogo=SIZE_LOGO;
flagWrite=0;
DWORD iSearch=0x00000000;
while(BUTTON_STAT==PUSH)flagWrite=1;
#ifdef __ERASE_MEMORY_FLASH__
    if(flagWrite==1){
        UART2PrintString("init erase\r\n");
        SST25ChipErase();
        //UART2PrintString("end erase\r\n");
        UART2PrintString("Standby Write\r\n");    
    }else{    
    UART2PrintString("Only Read\r\n\r\n");
    read_sector_sst();
    }
#endif

while(1)LED_RA3=0;    
}



void read_sector_sst(void){
//sizeLogo=SIZE_LOGO;
static DWORD address=0x00000000;
static BYTE byteTmp;
static int byteReads;
static char strSST[32];
static BYTE cheksum=0x00;
static char strChks[64];
    for(byteReads=0;byteReads<128;)
    {

        if(!(byteReads%16)){
            sprintf(strChks,"\tcheksum:0x%X \t",cheksum);
            UART2PrintString(strChks);
            UART2PrintString("\r\n");
            cheksum=0x00;
        }
        byteTmp=(SST25ReadByte(address))&0xFF;
        cheksum=(cheksum +(BYTE)byteTmp)&0xFF;
        
        
        sprintf(strSST,"0x%X,",byteTmp);
        UART2PrintString(strSST); 
        
        
        
        byteReads++;
        address++;
    }
    UART2PrintString("\r\nend Read\r\n");
}


#define __UART2_FOUND__


#ifdef __UART2_FOUND__
void __ISR(_UART2_VECTOR, IPL2AUTO)IntUart2Handler(void)
{
static DWORD address=0x00000000;
  if (INTGetFlag(INT_SOURCE_UART_RX(UART2)))
    {             
        SST25WriteByte((unsigned char)UART2GetChar(),address);  
        //LED_RA3=~LED_RA3;
        address++;                   
    }
INTClearFlag(INT_SOURCE_UART_RX(UART2)); 
  //if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) )INTClearFlag(INT_SOURCE_UART_TX(UART2));            
}
#else


void __ISR(_UART2_VECTOR, IPL2AUTO)IntUart2Handler(void)
{
static DWORD address=0x00000000;
static UINT16 counter=0;
static char buffer_rx[18];
static unsigned char checksum=0x00;

    if (INTGetFlag(INT_SOURCE_UART_RX(UART2)))
    {             
        buffer_rx[counter]=UART2GetChar();
        checksum=(checksum + buffer_rx[counter] )&0xFF;
        SST25WriteByte((unsigned char)buffer_rx[counter],address);
        if(counter>=17){
            if(checksum==buffer_rx[17]){LED_RA1=~LED_RA1;}else{LED_RA1=0;}
            checksum=0x00;
            address--;counter=0;
        }
        //LED_RA3=~LED_RA3;
        address++;                   
    }
INTClearFlag(INT_SOURCE_UART_RX(UART2)); 
  //if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) )INTClearFlag(INT_SOURCE_UART_TX(UART2));            
}

#endif