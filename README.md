<!-- Please do not change this html logo with link -->
<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# ADC Basics with tinyAVR® 0- and 1-series, and megaAVR® 0-series

Microchip tinyAVR® 0- and 1-series, and megaAVR® 0-series devices feature a 10-bit successive approximation register (SAR) Analog-to-Digital Converter (ADC) and is capable of conversion rates up to 115 ksps. It features a flexible multiplexer, which allows the ADC to measure the voltage at multiple single-ended input pins. Single-ended input channels are referred to ground. The ADC input signal is fed through a sample-and-hold circuit which ensures that the input voltage to the ADC is held at a constant level during sampling. It also features multiple internal ADC reference voltages between 0.55V and VDD.

An ADC conversion can be started by software, or by using the Event System (EVSYS) to route an event from other peripherals. A window compare feature is available for monitoring the input signal and can be configured to trigger an interrupt on user-defined thresholds for under, over, inside, or outside a window, with minimum software intervention required.

This repository describes the basic functionality of the ADC in Microchip tinyAVR® 0- and 1-series, and megaAVR®  0-series devices in Single ended mode. It is explained in detail in the document [*AN2573 - ADC Basics with tinyAVR® 0- and 1-series, and megaAVR® 0-series*](https://www.microchip.com/DS00002573) from Microchip. The ATtiny817 Xplained Pro board will be used in these examples.

## Related Documentation

- [AN2573 - ADC Basics with tinyAVR® 0- and 1-series, and megaAVR® 0-series](https://www.microchip.com/DS00002573)
- [ATtiny817 Device Page](https://www.microchip.com/wwwproducts/en/ATtiny817)

## Software Used

- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) 5.40 or later
- [ATtiny DFP](http://packs.download.atmel.com/) 2.2.89 or later
- [MPLAB® XC8](http://www.microchip.com/mplab/compilers) 2.20 or a later
- [AVR/GNU C Compiler](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers) 5.4.0 or later

## Hardware Used

- [ATtiny817 Xplained Pro](https://www.microchip.com/DevelopmentTools/ProductDetails/attiny817-xpro)
- Micro-USB cable (Type-A/Micro-B)


## Operation

1. Connect the ATtiny817 Xplained Pro board to the PC using the USB cable.

2. Download the zip file or clone the example to get the source code.

3. Open the project in MPLAB X IDE.
      
4. Choose the use case by configuring the value of the macro *EXAMPLE_CODE* in *main.c*. Refer to the document [AN2573 - ADC Basics with tinyAVR® 0- and 1-series, and megaAVR® 0-series](https://www.microchip.com/DS00002573) to learn about the different use cases.

5. Build the solution and program the device by using the buttons *Build* and *Make and Program Device*.

6. The ADC result is converted to voltage format and printed through the USART to the terminal.

## Conclusion

This project is an illustration of four basic use cases based around the ADC of Microchip tinyAVR® 0- and 1-series, and megaAVR®  0-series devices.
