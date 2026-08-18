#include <xc.h>
#include <stdio.h>

// PIC18F4520 Configuration Bits
#pragma config OSC = INTIO67
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = ON
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = OFF
#pragma config CCP2MX = PORTC
#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config XINST = OFF

#define _XTAL_FREQ 8000000UL

// ---------------- LCD connections ----------------
// LCD D0-D7 -> PORTD
// LCD RS    -> RC1
// LCD RW    -> GND
// LCD EN    -> RC2

#define LCD_RS  PORTCbits.RC1
#define LCD_EN  PORTCbits.RC2

// Relay control -> RC0
#define RELAY   PORTCbits.RC0


// --------------------------------------------------
// LCD FUNCTIONS
// --------------------------------------------------

void LCD_Pulse(void)
{
    LCD_EN = 1;
    __delay_us(5);
    LCD_EN = 0;
    __delay_us(100);
}

void LCD_Command(unsigned char cmd)
{
    LCD_RS = 0;
    PORTD = cmd;
    LCD_Pulse();

    if(cmd == 0x01 || cmd == 0x02)
        __delay_ms(2);
}

void LCD_Data(unsigned char data)
{
    LCD_RS = 1;
    PORTD = data;
    LCD_Pulse();
}

void LCD_Init(void)
{
    __delay_ms(20);

    LCD_Command(0x38);   // 8-bit, 2-line, 5x7
    LCD_Command(0x0C);   // Display ON, cursor OFF
    LCD_Command(0x06);   // Increment cursor
    LCD_Command(0x01);   // Clear display

    __delay_ms(2);
}

void LCD_String(const char *str)
{
    while(*str)
    {
        LCD_Data(*str++);
    }
}

void LCD_SetCursor(unsigned char row, unsigned char column)
{
    unsigned char address;

    if(row == 1)
        address = 0x80 + column;
    else
        address = 0xC0 + column;

    LCD_Command(address);
}


// --------------------------------------------------
// ADC FUNCTIONS
// --------------------------------------------------

void ADC_Init(void)
{
    // RA0 = AN0 analog input
    // Other pins digital

    ADCON1 = 0x0E;

    // Right justified
    // Acquisition time = 8 TAD
    // ADC clock = Fosc/32
    ADCON2 = 0xAA;

    // ADC ON, channel AN0
    ADCON0 = 0x01;

    TRISAbits.TRISA0 = 1;
}

unsigned int ADC_Read(void)
{
    unsigned int result;

    // Select AN0
    ADCON0bits.CHS = 0;

    __delay_us(20);

    // Start conversion
    ADCON0bits.GO = 1;

    while(ADCON0bits.GO);

    result = ((unsigned int)ADRESH << 8) | ADRESL;

    return result;
}


// --------------------------------------------------
// MAIN PROGRAM
// --------------------------------------------------

void main(void)
{
    unsigned int adc_value;
    unsigned int voltage;
    char text[17];

    // Internal oscillator = 8 MHz
    OSCCON = 0x72;

    // PORT configuration
    TRISA = 0x01;      // RA0 input
    TRISC = 0x00;      // RC0, RC1, RC2 outputs
    TRISD = 0x00;      // LCD data outputs

    PORTA = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;

    // Initialize ADC
    ADC_Init();

    // Initialize LCD
    LCD_Init();

    LCD_SetCursor(1, 0);
    LCD_String("LIGHT CONTROL");

    __delay_ms(1500);

    LCD_Command(0x01);

    while(1)
    {
        // Read LDR
        adc_value = ADC_Read();

        // Convert ADC reading to voltage in mV
        // 10-bit ADC, Vref = 5V
        voltage = ((unsigned long)adc_value * 5000UL) / 1023UL;

        // Display LDR voltage
        LCD_SetCursor(1, 0);
        LCD_String("LDR:");

        sprintf(text, "%4umV", voltage);
        LCD_String(text);

        // ------------------------------------------------
        // LIGHT CONTROL
        //
        // Your circuit:
        // +5V -> 10K resistor -> ADC -> LDR -> GND
        //
        // Dark  = LDR resistance high = ADC voltage high
        // Bright = LDR resistance low = ADC voltage low
        //
        // Change 2500 below to suit your Proteus simulation.
        // ------------------------------------------------

        if(adc_value > 512)
        {
            // DARK
            RELAY = 1;

            LCD_SetCursor(2, 0);
            LCD_String("LIGHT: ON ");

        }
        else
        {
            // BRIGHT
            RELAY = 0;

            LCD_SetCursor(2, 0);
            LCD_String("LIGHT: OFF");
        }

        __delay_ms(300);
    }
}