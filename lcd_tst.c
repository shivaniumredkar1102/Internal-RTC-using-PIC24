
// PIC24FJ128GA010 Configuration Bit Settings

// 'C' source line config statements

// CONFIG2

// PIC24FJ64GA010 Configuration Bit Settings

// 'C' source line config statements

// CONFIG2
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG port is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define FCY 8000000UL
#include <xc.h>
#include <p24FJ128GA010.h>
#include <string.h>
#include <stdio.h>
#include <libpic30.h>


#define RS_PIN LATBbits.LATB15 // RD0 --> RS
#define E_PIN LATDbits.LATD4  // RD1 --> E 
#define RW_PIN LATDbits.LATD5 //RD5 --> RW
#define D0_PIN LATEbits.LATE0 
#define D1_PIN LATEbits.LATE1
#define D2_PIN LATEbits.LATE2
#define D3_PIN LATEbits.LATE3
#define D4_PIN LATEbits.LATE4 // RD2 --> D4
#define D5_PIN LATEbits.LATE5 // RD3 --> D5
#define D6_PIN LATEbits.LATE6 // RD4 --> D6
#define D7_PIN LATEbits.LATE7 // RD5 --> D7

#define RS_TRIS TRISBbits.TRISB15
#define E_TRIS TRISDbits.TRISD4
#define RW_TRIS TRISDbits.TRISD5
#define D0_TRIS TRISEbits.TRISE0
#define D1_TRIS TRISEbits.TRISE1
#define D2_TRIS TRISEbits.TRISE2
#define D3_TRIS TRISEbits.TRISE3
#define D4_TRIS TRISEbits.TRISE4
#define D5_TRIS TRISEbits.TRISE5
#define D6_TRIS TRISEbits.TRISE6
#define D7_TRIS TRISEbits.TRISE7
#include "lcd.h"
#include "rtc_tst.h"

void main()
{
    char buffer[20];
   unsigned char year;
   unsigned char month;
   unsigned char day;
   unsigned char weekday;
   unsigned char hour;
   unsigned char minutes;
   unsigned char seconds;
    RTCTime result;
    TRISEbits.TRISE0 = 0;
    LATEbits.LATE0 = 1;
    TRISB = 0;
    TRISA = 0;
    RS_TRIS = 0;
    E_TRIS=0;
    RW_TRIS = 0;
    D0_TRIS = 0;
    D1_TRIS = 0;
    D2_TRIS = 0;
    D3_TRIS = 0;
    D4_TRIS=0;
    D5_TRIS=0;
    D6_TRIS=0;
    D7_TRIS=0;
    
    E_PIN = 0;
    RS_PIN = 0;
    RW_PIN = 0;
    lcd_init();
    __delay_ms(100);
    lcd_cmd();
    __delay_ms(10);
    lcd_print("Hello_world :)");
    __delay_ms(10);
    
    __builtin_write_OSCCONL(OSCCON | 0x02); 
    
   // setRTCTime(0b11001,0b10001,0b100110,0b1,0b10110,0b1011001,0b1000101);
    setRTCTime(0x0012,0x000B,0x001B,0x0003,0x000D,0x0004,0x001E);
    __delay_ms(500);
     result =  getRTCTime();
     year = result.year;
     month = result.month;
     day = result.day;
     lcd_clr();
        sprintf(buffer,"%u",year);
        lcd_print(buffer);
        lcd_print("/");
        sprintf(buffer,"%u",month);
        lcd_print(buffer);
        lcd_print("/");
        sprintf(buffer,"%u",day);
        lcd_print(buffer);
        __delay_ms(500);
        lcd_clr();
         __delay_ms(100);
    while (1) // repeat continuously
    {
        result =  getRTCTime();
        weekday = result.weekday;
        hour = result.hour;
        minutes = result.minute;
        seconds = result.second;
       
      
        sprintf(buffer,"%u",hour);
        lcd_print(buffer);
        sprintf(buffer,"%u",minutes);
        lcd_print(":");
        lcd_print(buffer);
        sprintf(buffer,"%u",seconds);
        lcd_print(":");
        lcd_print(buffer);
        __delay_ms(300);
        lcd_clr();
    }
    
}
   