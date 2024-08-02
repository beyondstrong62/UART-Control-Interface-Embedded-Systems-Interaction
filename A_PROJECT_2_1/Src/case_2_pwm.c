#include <stdio.h>            // Include standard I/O functions
#include "stm32f446xx.h"      // Include STM32F446xx microcontroller definitions
#include "pll.h"              // Include PLL configuration functions
#include "sysTick.h"          // Include SysTick functions
#include "usart.h"        // Include the header file for USART communication

volatile int bright_pwm = 10; // Global variable to control PWM brightness

// Pin definitions
#define Led_Output_Pin_PA0 0  // Define PA0 as the output pin for PWM
#define Button_Input_Pin_PC13 13 // Define PC13 as the input pin for the button

// Function to initialize PWM intensity control
void PWM_Intensity_init(void)
{
    // Configure the system clock using PLL settings
    clockSpeed_PLL();
    
    // Initialize SysTick timer
    SysTick_Init();
    
    // Enable clock for GPIOA and GPIOC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
    
    // Configure PA0 for PWM output
    GPIOA->MODER &= ~(3 << (2 * Led_Output_Pin_PA0)); // Reset mode for PA0
    GPIOA->MODER |= (2 << (2 * Led_Output_Pin_PA0));  // Set PA0 to alternate function mode
    GPIOA->AFR[0] |= (1 << (4 * Led_Output_Pin_PA0)); // Set alternate function for PA0

    // Configure PC13 as input for button
    GPIOC->MODER &= ~(3 << (2 * Button_Input_Pin_PC13));
    
    // Enable clock for TIM2
    RCC->APB1ENR |=  RCC_APB1ENR_TIM2EN;
    
    // Configure TIM2 for PWM
    TIM2->ARR = 100;               // Set auto-reload register to 100
    TIM2->CCMR1 |= (1 << 5) | (1 << 6); // Set PWM mode 1 on channel 1
    TIM2->CCER |= (1 << 0);        // Enable capture/compare on channel 1
    TIM2->CR1 |= (1 << 0);         // Enable TIM2 counter
}

// Function to start PWM intensity control
void PWM_Intensity_start(void)
{
	char buffer[10];  // Buffer to hold string representations of numbers

	UART2_SendString("\n\rPWM Starts\n\r");
	UART2_SendString("Led glowing at ");
	sprintf(buffer, "%d", bright_pwm);  // Convert bright_pwm to string
	UART2_SendString(buffer);  // Print the current PWM brightness value
	UART2_SendString("x intensity\n\r");
	TIM2->CCR1 = bright_pwm;
    while (bright_pwm <= 100)  // Loop while PWM brightness is less than or equal to 100
    {
        if (!(GPIOC->IDR & (1 << Button_Input_Pin_PC13)))  // Check if button (PC13) is pressed
        {

            TIM2->CCR1 = bright_pwm; // Set PWM duty cycle
            bright_pwm += 10;       // Increase brightness
            if (bright_pwm > 100)  // If brightness exceeds 100, exit loop
            {
                break;
            }
            while (!(GPIOC->IDR & (1 << Button_Input_Pin_PC13)));  // Wait until button is released
            UART2_SendString("Led glowing at ");
            sprintf(buffer, "%d", bright_pwm);  // Convert bright_pwm to string
            UART2_SendString(buffer);  // Print the current PWM brightness value
            UART2_SendString("x intensity\n\r");
        }
    }
    bright_pwm = 10;  // Reset brightness after loop
}

// Function to stop PWM intensity control
void PWM_Intensity_close(void)
{
    TIM2->CCR1 = 0;  // Set PWM duty cycle to 0 (turn off PWM)
}
