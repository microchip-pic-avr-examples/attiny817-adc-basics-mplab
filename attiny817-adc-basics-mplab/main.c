#include <atmel_start.h>
#include <util/delay.h>

#define FREE_RUNNING 1
#define SINGLE_CONVERSION 2
#define WINDOW_COMPARATOR_MODE 3
#define SAMPLE_ACCUMULATOR 4

#define EXAMPLE_CODE SAMPLE_ACCUMULATOR // WINDOW_COMPARATOR_MODE

#define MAX_VOL 2.5 // VREF=2.5V
#define RES_10BIT 0x3FF
#define ADC_CHANNEL 6

uint16_t adc_result = 0;
float    calc_volt;

void read_adc_single_conversion()
{
	adc_result = ADC_0_get_conversion(ADC_CHANNEL);
	calc_volt  = (adc_result * MAX_VOL) / RES_10BIT;
}

void read_adc_sample_accumulator()
{
	adc_result = ADC_0_get_conversion(ADC_CHANNEL);
	adc_result = adc_result >> 6; // divide by 64
	calc_volt  = (adc_result * MAX_VOL) / RES_10BIT;
}

void free_running()
{
	if (ADC_0_is_conversion_done()) {
		adc_result = ADC0.RES;
		calc_volt  = (adc_result * MAX_VOL) / RES_10BIT;
	}
}
void window_comparator_mode()
{
	if (ADC_0_is_conversion_done()) {
		adc_result = ADC0.RES;
		calc_volt  = (adc_result * MAX_VOL) / RES_10BIT;
	}

	if (ADC_0_get_window_result()) {
		/* LED0 is ON when ADC result is below the pre-defined window value */
		LED0_set_level(0); // on
	} else
		LED0_set_level(1); // off
}

// USART Functions
/**
 * \brief Write a string on USART
 */
void usart_put_string(const char str[], const uint8_t STR_LEN)
{
	for (int i = 0; i < STR_LEN; i++) {
		USART_0_write(str[i]);
	}
}

// USART print float number
void usart_send_float(float number)
{
	char string[6];

	dtostrf(number, 2, 3, string);
	usart_put_string(string, 5);
	usart_put_string("V\n", 2);
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

#if EXAMPLE_CODE == FREE_RUNNING
	{
		ADC0.CTRLA |= 1 << ADC_FREERUN_bp;   /* ADC_FREERUN_bp: enabled */
		ADC_0_start_conversion(ADC_CHANNEL); //
	}
#elif EXAMPLE_CODE == SAMPLE_ACCUMULATOR
	{
		ADC0.CTRLB = ADC_SAMPNUM_ACC64_gc;
	}
#elif EXAMPLE_CODE == WINDOW_COMPARATOR_MODE //will be run in free running mode
	{
		ADC_0_set_window_low(0x100);
		ADC_0_set_window_mode(ADC_WINCM_BELOW_gc);
		ADC0.CTRLA |= 1 << ADC_FREERUN_bp;
		ADC_0_start_conversion(ADC_CHANNEL);
	}
#endif

	/* Replace with your application code */
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
		usart_send_float(calc_volt);

		/* Toggles LED0 in 3 application cases, except in WINDOW_COMPARATOR_MODE */
		if (EXAMPLE_CODE != WINDOW_COMPARATOR_MODE)
			LED0_toggle_level();
		_delay_ms(200);
	}
}
