/**
  ADCC Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adcc.c

  @Summary
    This is the generated driver implementation file for the ADCC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for ADCC.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC16F18446
        Driver Version    :  2.1.4
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB             :  MPLAB X 5.30
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "adcc.h"
#include "mcc.h"
#include <math.h>

/**
  Section: ADCC Module Variables
*/
void (*ADCC_ADI_InterruptHandler)(void);

unsigned int acumulator = 0;
int samples_count = 0;
unsigned int mean = 0;
double std_ref = 1;
char docon=0;
int adc_vect[10];

union schrodi{
    char bit8[2];
    unsigned int bit16;
};

union schrodi my_schrodi;
/**
  Section: ADCC Module APIs
*/
void value_approved(int val);
int parity_check(int parity);
void ADCC_Initialize(void)
{
    // set the ADCC to the options selected in the User Interface
    // ADLTH 0; 
    ADLTHL = 0x00;
    // ADLTH 0; 
    ADLTHH = 0x00;
    // ADUTH 0; 
    ADUTHL = 0x00;
    // ADUTH 0; 
    ADUTHH = 0x00;
    // ADSTPT 0; 
    ADSTPTL = 0x00;
    // ADSTPT 0; 
    ADSTPTH = 0x00;
    // ADACC 0; 
    ADACCU = 0x00;
    // ADRPT 0; 
    ADRPT = 0x00;
    // ADPCH ANA0; 
    ADPCH = 0x00;
    // ADACQ 0; 
    ADACQL = 0x00;
    // ADACQ 0; 
    ADACQH = 0x00;
    // ADCAP Additional uC disabled; 
    ADCAP = 0x00;
    // ADPRE 0; 
    ADPREL = 0x00;
    // ADPRE 0; 
    ADPREH = 0x00;
    // ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL Vss; 
    ADCON1 = 0x00;
    // ADCRS 0; ADMD Basic_mode; ADACLR disabled; ADPSIS RES; 
    ADCON2 = 0x00;
    // ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared; 
    ADCON3 = 0x00;
    // ADMATH registers not updated; 
    ADSTAT = 0x00;
    // ADNREF external; ADPREF external; 
    ADREF = 0x12;
    // ADNREF internal; ADPREF internal; 
    //ADREF = 0x00;
    // ADACT disabled; 
    ADACT = 0x00;
    // ADCS FOSC/8; 
    ADCLK = 0x03;
    // ADGO stop; ADFM right; ADON enabled; ADCS FOSC/ADCLK; ADCONT enabled; 
    ADCON0 = 0xC4;
    
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
    // Enabling ADCC interrupt.
    PIE1bits.ADIE = 1;

    ADCC_SetADIInterruptHandler(ADCC_DefaultInterruptHandler);

}

void ADCC_StartConversion(adcc_channel_t channel)
{
    // select the A/D channel
    ADPCH = 16;      
  
    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Start the conversion
    ADCON0bits.ADGO = 1;
}

bool ADCC_IsConversionDone()
{
    // Start the conversion
    return ((unsigned char)(!ADCON0bits.ADGO));
}

adc_result_t ADCC_GetConversionResult(void)
{
    // Return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

adc_result_t ADCC_GetSingleConversion(adcc_channel_t channel)
{
    // select the A/D channel
    ADPCH = channel;  

    // Turn on the ADC module
    ADCON0bits.ADON = 1;
	
    //Disable the continuous mode.
    ADCON0bits.ADCONT = 0;    

    // Start the conversion
    ADCON0bits.ADGO = 1;


    // Wait for the conversion to finish
    while (ADCON0bits.ADGO)
    {
    }
    
    
    // Conversion finished, return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

void ADCC_StopConversion(void)
{
    //Reset the ADGO bit.
    ADCON0bits.ADGO = 0;
}

void ADCC_SetStopOnInterrupt(void)
{
    //Set the ADSOI bit.
    ADCON3bits.ADSOI = 1;
}

void ADCC_DischargeSampleCapacitor(void)
{
    //Set the ADC channel to AVss.
    ADPCH = 0x3b;   
}

void ADCC_LoadAcquisitionRegister(uint16_t acquisitionValue)
{
    //Load the ADACQH and ADACQL registers.
    ADACQH = acquisitionValue >> 8; 
    ADACQL = acquisitionValue;  
}

void ADCC_SetPrechargeTime(uint16_t prechargeTime)
{
    //Load the ADPREH and ADPREL registers.
    ADPREH = prechargeTime >> 8;  
    ADPREL = prechargeTime;
}

void ADCC_SetRepeatCount(uint8_t repeatCount)
{
    //Load the ADRPT register.
    ADRPT = repeatCount;   
}

uint8_t ADCC_GetCurrentCountofConversions(void)
{
    //Return the contents of ADCNT register
    return ADCNT;
}

void ADCC_ClearAccumulator(void)
{
    //Reset the ADCON2bits.ADACLR bit.
    ADCON2bits.ADACLR = 1;
}

uint24_t ADCC_GetAccumulatorValue(void)
{
    //Return the contents of ADACCU, ADACCH and ADACCL registers
    return (((uint24_t)ADACCU << 16)+((uint24_t)ADACCH << 8) + ADACCL);
}

bool ADCC_HasAccumulatorOverflowed(void)
{
    //Return the status of ADSTATbits.ADAOV
    return ADSTATbits.ADAOV;
}

uint16_t ADCC_GetFilterValue(void)
{
    //Return the contents of ADFLTRH and ADFLTRL registers
    return ((uint16_t)((ADFLTRH << 8) + ADFLTRL));
}

uint16_t ADCC_GetPreviousResult(void)
{
    //Return the contents of ADPREVH and ADPREVL registers
    return ((uint16_t)((ADPREVH << 8) + ADPREVL));
}

void ADCC_DefineSetPoint(uint16_t setPoint)
{
    //Sets the ADSTPTH and ADSTPTL registers
    ADSTPTH = setPoint >> 8;
    ADSTPTL = setPoint;
}

void ADCC_SetUpperThreshold(uint16_t upperThreshold)
{
    //Sets the ADUTHH and ADUTHL registers
    ADUTHH = upperThreshold >> 8;
    ADUTHL = upperThreshold;
}

void ADCC_SetLowerThreshold(uint16_t lowerThreshold)
{
    //Sets the ADLTHH and ADLTHL registers
    ADLTHH = lowerThreshold >> 8;
    ADLTHL = lowerThreshold;
}

uint16_t ADCC_GetErrorCalculation(void)
{
	//Return the contents of ADERRH and ADERRL registers
	return ((uint16_t)((ADERRH << 8) + ADERRL));
}

void ADCC_EnableDoubleSampling(void)
{
    //Sets the ADCON1bits.ADDSEN
    ADCON1bits.ADDSEN = 1;
}

void ADCC_EnableContinuousConversion(void)
{
    //Sets the ADCON0bits.ADCONT
    ADCON0bits.ADCONT = 1;
}

void ADCC_DisableContinuousConversion(void)
{
    //Resets the ADCON0bits.ADCONT
    ADCON0bits.ADCONT = 0;
}

bool ADCC_HasErrorCrossedUpperThreshold(void)
{
    //Returns the value of ADSTATbits.ADUTHR bit.
    return ADSTATbits.ADUTHR;
}

bool ADCC_HasErrorCrossedLowerThreshold(void)
{
    //Returns the value of ADSTATbits.ADLTHR bit.
    return ADSTATbits.ADLTHR;
}

uint8_t ADCC_GetConversionStageStatus(void)
{
    //Returns the contents of ADSTATbits.ADSTAT field.
    return ADSTATbits.ADSTAT;
}

void ADCC_ISR(void)
{
    // Clear the ADCC interrupt flag
    PIR1bits.ADIF = 0;
    acumulator = acumulator+((int)((ADRESH << 8) + ADRESL));
    adc_vect[samples_count]=(int)((ADRESH << 8) + ADRESL);
    
    if(docon ==1){
        LED_SetHigh();
        my_schrodi.bit16 = parity_check(adc_vect[samples_count]);
        add_Buffer_val(my_schrodi.bit8[1]);
        add_Buffer_val(my_schrodi.bit8[0]);
    
        LED_SetLow();
        
    }
    
    samples_count++;
    //add_Buffer_val(ADRESH);
    //add_Buffer_val(ADRESL);
    if(samples_count == 10){
        
        mean = acumulator/10;
        double std_s=0;
        
        for(char i=0;i<10;i++){
            
            std_s = std_s+pow(adc_vect[i]-mean,2);
        }
        
        std_s = sqrt(std_s/9);
        std_s = 0.5;
        
        if(docon ==2){
            //my_schrodi.bit16 =  mean;
            my_schrodi.bit16 = parity_check(mean);
            add_Buffer_val(my_schrodi.bit8[1]);
            add_Buffer_val(my_schrodi.bit8[0]);
            LED_SetHigh();
        }
        
        if(std_s<=std_ref){
             
        }
        
        samples_count =0;
        acumulator = 0;
        LED_SetLow();
        
    }
    
    
    
    
    
    
}

void ADCC_SetADIInterruptHandler(void (* InterruptHandler)(void)){
    ADCC_ADI_InterruptHandler = InterruptHandler;
}

void ADCC_DefaultInterruptHandler(void){
    // add your ADCC interrupt custom code
    // or set custom function using ADCC_SetADIInterruptHandler() or ADCC_SetADTIInterruptHandler()
}

void adc_one(char doit){
    docon=doit;
}
/**
 End of File
*/
