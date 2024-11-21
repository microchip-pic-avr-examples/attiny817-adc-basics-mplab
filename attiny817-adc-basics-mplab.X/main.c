 /*
 * MAIN Generated Driver File
 *
 * @file main.c
 *
 * @defgroup main MAIN
 *
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip
    software and any derivatives exclusively with Microchip products.
    You are responsible for complying with 3rd party license terms
    applicable to your use of 3rd party software (including open source
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.?
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include <util/delay.h>
#include <stdio.h>

/*
    Main application
*/

#define FREE_RUNNING 1
#define SINGLE_CONVERSION 2
#define WINDOW_COMPARATOR_MODE 3
#define SAMPLE_ACCUMULATOR 4

#define EXAMPLE_CODE FREE_RUNNING

#define MAX_VOL 2.5 // VREF=2.5V
#define RES_10BIT 0x3FF
#define ADC_CHANNEL 6

uint16_t adc_result = 0;
float    calc_volt;

void free_running();
void read_adc_single_conversion();
void read_adc_sample_accumulator();
void window_comparator_mode();

int main(void)
{
    SYSTEM_Initialize();

    #if EXAMPLE_CODE == FREE_RUNNING
    {
            ADC0.CTRLA |= 1 << ADC_FREERUN_bp;   /* ADC_FREERUN_bp: enabled */
            ADC0_StartConversion(ADC_CHANNEL); //
    }
    #elif EXAMPLE_CODE == SAMPLE_ACCUMULATOR
    {
            ADC0.CTRLB = ADC_SAMPNUM_ACC64_gc;
    }
    #elif EXAMPLE_CODE == WINDOW_COMPARATOR_MODE //will be run in free running mode
    {
            ADC0_SetWindowLow(0x100);
            ADC0_SetWindowMode(ADC_WINCM_BELOW_gc);
            ADC0.CTRLA |= 1 << ADC_FREERUN_bp;
            ADC0_StartConversion(ADC_CHANNEL);
    }
    #endif

    while (1) {

        #if EXAMPLE_CODE == SINGLE_CONVERSION
        {
                read_adc_single_conversion();
        }
        #elif EXAMPLE_CODE == FREE_RUNNING
        {
                free_running();
        }
        #elif EXAMPLE_CODE == WINDOW_COMPARATOR_MODE
        {
                window_comparator_mode();
        }
        #elif EXAMPLE_CODE == SAMPLE_ACCUMULATOR
        {
                read_adc_sample_accumulator();
        }
        #endif

        /* Print calc_volt to terminal*/
        printf("\n%2.3fV", calc_volt);

        /* Toggles LED0 in 3 application cases, except in WINDOW_COMPARATOR_MODE */
        if (EXAMPLE_CODE != WINDOW_COMPARATOR_MODE)
        {
            LED0_Toggle();
        }
        _delay_ms(200);
    }
}

void free_running()
{
    if (ADC0_IsConversionDone()) {
        adc_result = ADC0.RES;
        calc_volt  = (adc_result * MAX_VOL) / RES_10BIT;
    }
}

void read_adc_single_conversion()
{
    adc_result = ADC0_GetConversion(ADC_CHANNEL);
    calc_volt  = (adc_result * MAX_VOL) / RES_10BIT;
}

void read_adc_sample_accumulator()
{
    adc_result = ADC0_GetConversion(ADC_CHANNEL);
    adc_result = adc_result >> 6; // divide by 64
    calc_volt  = (adc_result * MAX_VOL) / RES_10BIT;
}

void window_comparator_mode()
{
    if (ADC0_IsConversionDone()) {
        adc_result = ADC0.RES;
        calc_volt  = (adc_result * MAX_VOL) / RES_10BIT;
    }

    if (ADC0_GetWindowResult()) {
        /* LED0 is ON when ADC result is below the pre-defined window value */
        LED0_SetLow(); // on
    }
    else {
        LED0_SetHigh(); // off
    }
}