<!-- Please do not change this html logo with link -->
<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# ADC Basics with tinyAVR® 0- and 1-series, and megaAVR® 0-series

Microchip tinyAVR® 0- and 1-series, and megaAVR® 0-series devices feature a 10-bit successive approximation register (SAR) Analog-to-Digital Converter (ADC) and is capable of conversion rates up to 115 ksps. It features a flexible multiplexer, which allows the ADC to measure the voltage at multiple single-ended input pins. Single-ended input channels are referred to ground. The ADC input signal is fed through a sample-and-hold circuit which ensures that the input voltage to the ADC is held at a constant level during sampling. It also features multiple internal ADC reference voltages between 0.55V and VDD.

An ADC conversion can be started by software, or by using the Event System (EVSYS) to route an event from other peripherals. A window compare feature is available for monitoring the input signal and can be configured to trigger an interrupt on user-defined thresholds for under, over, inside, or outside a window, with minimum software intervention required.

This repository describes the basic functionality of the ADC in Microchip tinyAVR® 0- and 1-series, and megaAVR®  0-series devices in Single ended mode. It is explained thorougly in the document [*AN2573 - ADC Basics with tinyAVR® 0- and 1-series, and megaAVR® 0-series*](https://www.microchip.com/DS00002573) from Microchip. The ATtiny817 Xplained Pro board will be used in these examples.

## Related Documentation

- [AN2573 - ADC Basics with tinyAVR® 0- and 1-series, and megaAVR® 0-series](https://www.microchip.com/DS00002573)
- [ATtiny817 Xplained Pro User Guide](https://www.microchip.com/DS50002684)
- [ATtiny817 Data Sheet](https://www.microchip.com/DS40001901)
- [ATtiny817 Device Page](https://www.microchip.com/wwwproducts/en/ATtiny817)

## Software Used

- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) v5.40 or later
- [MPLAB® XC8](http://www.microchip.com/mplab/compilers) 2.20 or a later

## Hardware Used

- [ATtiny817 Xplained Pro](https://www.microchip.com/DevelopmentTools/ProductDetails/attiny817-xpro)
- Micro-USB cable (Type-A/Micro-B)

## Setup

1. Connect the ATtiny817 Xplained Pro board to the PC using the USB cable.


## Operation
1. Download the zip file or clone the example to get the source code.

2. Open the project in MPLAB X IDE.

3. One application with four use cases has been developed and tested on the ATtiny817 Xplained Pro board. The following configurations are common for all four use cases:
    - CPU Clock: 3.33 MHz
    - Peripherals used:
      - ADC, VREF and USART
    - Details of the peripheral configurations:
      - ADC
        - Resolution at 10 bits
        -  Input channel is AIN 6: pin PA6
      - VREF set to 2.5V
      - USART:
        - TXEN: Transmission Enable is set
        - Baud Rate: 9600
      - GPIO output pin PB4: LED0
      
4. Choose the use case by configuring the value of the macro *EXAMPLE_CODE* in *main.c*.
    - Case *FREE_RUNNING*: The first conversion is started when the initial configuration of the Free-Running mode is executed. When the conversion cycle is completed, the ADC result is read from the ADC0.res register. A new conversion cycle is then started immediately after the previous conversion cycle is completed.

    - Case *SINGLE_CONVERSION*: The conversion starts after the *read_adc_single_conversion()* function is called. After one conversion is completed a new single conversion has to be manually configured in order to start.

    - Case *WINDOW_COMPARATOR_MODE*: The ADC is set in Free-Running mode, and can raise a flag and request an interrupt when the result of a conversion is above and/or below certain thresholds. In this use case, the *result below window* option is chosen. LED0 is turned ON when the function *ADC_0_get_window_result()* returns true, meaning the ADC result is under the window threshold value and the interrupt flag bit of the windows compare mode is set. Otherwise, LED0 is kept OFF
    
    - Case *SAMPLE_ACCUMULATOR*:  In this use case, the ADC is configured to accumulate 64 samples automatically in one conversion in order to average out noise or to get averaged ADC result. Consequently, the conversion complete flag is only raised once, after taking the last sample of the accumulation. The ADC result is averaged over the configured number of samples. 


5. Build the solution and program the device by using the buttons *Build* and *Make and Program Device*.

6. The ADC result is converted to voltage format and printed through the USART to the terminal.

## Conclusion

This project is an illustration of four basic use cases based around the ADC of Microchip tinyAVR® 0- and 1-series, and megaAVR®  0-series devices.
