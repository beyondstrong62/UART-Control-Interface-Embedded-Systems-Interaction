#include "stm32f446xx.h"  // Include the header file for the STM32F446xx microcontroller
#include "usart.h"        // Include the header file for USART communication
#include <stdio.h>        // Include the standard I/O header file for printf and other functions


#define Led_Output_Pin_PA1     1   // Define PA1 as the output pin for the LED
#define Button_Input_Pin_PA13  13  // Define PA1 as the output pin for the LED

// Declare a volatile integer variable for controlling the LED blinking delay
volatile int led_blinking_delay = 1;

// Function to initialize the LED blinking setup
void led_blinking_init(void)
{
    // Enable the clock for GPIOA and GPIOC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

    // Set PA1 as output
    GPIOA->MODER &= ~(3 << (2*Led_Output_Pin_PA1)); // Reset the MODER bits for PA1
    GPIOA->MODER |= (1 << (2*Led_Output_Pin_PA1));  // Set PA1 as output mode

    // Set PC13 as input
    GPIOC->MODER &= ~(3 << (2*Button_Input_Pin_PA13)); // Reset the MODER bits for PC13
}

// Function to start the LED blinking
void led_blinking_start(void)
{
	UART2_SendString("\n\rLed Blinking Starts\n\r");
	UART2_SendString("Led Blinking at delay speed ");
	UART2_SendChar((char)(led_blinking_delay + '0')); // Print the current delay value
	UART2_SendString("x\n\r");
    while (led_blinking_delay <= 5)  // Loop while the delay is less than or equal to 5
    {
        GPIOA->ODR ^= (1 << 1);  // Toggle the LED connected to PA1
        for (int i = 0; i < (1000000 * led_blinking_delay); i++)  // Delay loop
        {
            if (!(GPIOC->IDR & (1 << Button_Input_Pin_PA13)))  // Check if the button connected to PC13 is pressed
            {
                led_blinking_delay += 1;  // Increment the delay
                if (led_blinking_delay >= 6)  // If the delay exceeds 6, break the loop
                {
                    break;
                }

                while (!(GPIOC->IDR & (1 << Button_Input_Pin_PA13)));  // Wait until the button is released
                UART2_SendString("Led Blinking at delay speed ");
                UART2_SendChar((char)(led_blinking_delay + '0')); // Print the current delay value
                UART2_SendString("x\n\r");
                break;
            }
        }
    }
    led_blinking_delay = 1;  // Reset the delay to 1
}

// Function to stop the LED blinking
void led_blinking_stop(void)
{
    GPIOA->ODR &= ~(1 << 1);  // Turn off the LED connected to PA1
}
