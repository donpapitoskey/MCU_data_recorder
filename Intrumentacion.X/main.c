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

/*
                         Main application
 */



int my_val;
char curr_pointer=0;

union schrodi{
    char bit8[2];
    int bit16;
};



union schrodi frame[10];




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
    
    uint8_t eusart1Buffer[8] = {'h','o','l','i','w','i','s','1'};
    uint16_t *ADC_result;
    
    ADCC_Initialize();
    while (1)
    {
        // Add your application code
        
        
        
        /*LED_SetHigh();
        __delay_ms(500);
        LED_SetLow();
        __delay_ms(500);*/
        
        
        
        //ADC_result= get_adc();
        
        
        //fill_buffer(eusart1Buffer);
    }
}

void value_approved(int val){
    //charlist[newval] = val;
    //frame[curr_pointer].bit16 = parity_check(val);
    frame[curr_pointer].bit16 = val;
    //add_Buffer_val(frame[curr_pointer].bit8[0]);
    //add_Buffer_val(frame[curr_pointer].bit8[1]);
    curr_pointer++;
    
    if(curr_pointer ==10){
        
        curr_pointer =0;
    }
    LED_SetLow();
}

int parity_check(int parity){
    
     int copy_p = (unsigned int)parity;
    bool pari=0;
    while(copy_p){
        pari = !pari;
        copy_p = copy_p & (copy_p-1);
        
    }
    if(pari){
        copy_p = parity | (1<<12);
    }else{
        copy_p = parity & ~(1<<12);
    }
    return copy_p;
    
}




/**
 End of File
*/