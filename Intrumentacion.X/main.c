/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC16F18446
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <math.h>

/*
                         Main application
 */
typedef struct{
    unsigned char h:1;
    unsigned int i:1;
}Vector;

int ADC_good_value;
char EUSART_recieved_val;
char *my_pointer;
char values[22] ={'h','1','0','h','o','l','a','m','u','n','d','o','0','0','h','o','l','a','m','u','n','t'};    
char myVar=2;



void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    EUSART1_Initialize();
    ADCC_Initialize();
    
    //uint8_t eusart1Buffer[8] = {'h','o','l','i','w','i','s','1'};
    //uint16_t *ADC_result;
    
    
    
   
    fill_buffer(values);
    while (1)
    {
        // Add your application code
        
        if(EUSART_recieved_val == 'k'){
            EUSART1_Write(values);
            //ADCC_StartConversion(0);
           /*PIN13_SetHigh();
            __delay_ms(500);
            PIN13_SetLow();
            __delay_ms(500);
            PIN12_SetHigh();
            __delay_ms(500);
            PIN12_SetLow();
            __delay_ms(500);
            PIN11_SetHigh();
            __delay_ms(500);
            PIN11_SetLow();
            __delay_ms(500);  */  
            EUSART_recieved_val =0;
           
        
        }
            
        
        //ADC_result= get_adc();
    
    
        //fill_buffer(eusart1Buffer);
    }
}


/**
 End of File
*/
void vector_filler(char *my_pointer){
    for(char i=0;i<10;i++){
        *(my_pointer+2*i)=0;
    }
}



void parity_calculator (char *mypointer){
    //int parity;
}



void set_ADC_value(int value_ADCC){
    ADC_good_value=value_ADCC;
}


void set_EUSART_value(char EUSART_val){
    EUSART_recieved_val = EUSART_val;
}
