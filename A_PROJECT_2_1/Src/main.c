#include <stdint.h>         // Include standard integer types
#include <stdio.h>          // Include standard I/O functions
#include <stddef.h>         // Include standard definitions
#include "stm32f446xx.h"    // Include STM32F446xx microcontroller definitions
#include "pll.h"            // Include PLL configuration functions
#include "usart.h"          // Include USART functions
#include "sysTick.h"        // Include SysTick functions
#include "case_1_led_blinking.h" // Include LED blinking functions
#include "case_2_pwm.h"     // Include PWM intensity functions

volatile uint8_t choice;    // Global variable to store user choice

int main()
{
    // Configure USART2 for communication
    Usart2_config();

    // Initialize LED blinking functionality
    led_blinking_init();

    // Initialize PWM intensity control
    PWM_Intensity_init();

    while(1)  // Infinite loop to handle menu options
    {
        // Display available options to the user
        displayoption();

        // Receive user choice from UART
        choice = receiverdata();

        // Send the received choice back to the user
        UART2_SendString("\n\rYour choice is: ");
        UART2_SendChar(choice);

        // Handle the user's choice
        switch(choice)
        {
            case '1':
                // Start LED blinking and stop it after a certain condition
                led_blinking_start();
                led_blinking_stop();
                UART2_SendString("\n\rCase 1 ends here\n\r");
                break;

            case '2':
                // Start PWM intensity control and stop it after a certain condition
                PWM_Intensity_start();
                PWM_Intensity_close();
                UART2_SendString("\n\rCase 2 ends here\n\r");
                break;

            case '3':
                // Stop LED blinking and PWM intensity control, then exit
                led_blinking_stop();
                PWM_Intensity_close();
                UART2_SendString("\n\rExiting the utility\n\r");
            	UART2_SendString("\n\r      Thank You!! Visit Again\n\r");
            	UART2_SendString("\n\r------------------------------------\n\r");
                break;

            default:
                // Handle invalid choices
                UART2_SendString("\n\rInvalid choice!! Enter a correct value\n\r");
                break;
        }

        // Exit the loop if the user chooses option '3'
        if(choice == '3')
        {
            break;
        }
    }

    return 0; // Return 0 to indicate successful execution
}
