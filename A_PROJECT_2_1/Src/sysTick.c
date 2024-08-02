#include "stm32f446xx.h"  // Include STM32F446xx microcontroller definitions
#include "pll.h"          // Include PLL configuration functions

volatile uint32_t ms_counter = 0;  // Counter for delay management
volatile uint32_t millis = 0;      // Millisecond counter for timekeeping

// Function to initialize the SysTick timer
void SysTick_Init(){
    // Set SysTick timer value register to 0 (start counting from 0)
    SysTick->VAL = 0;
    
    // Set SysTick timer load value for 1 millisecond interval
    // HCLK_FREQ / 1000 gives the number of cycles per millisecond
    SysTick->LOAD = (HCLK_FREQ / 1000) - 1;
    
    // Configure SysTick:
    // - Use the processor clock as the clock source
    // - Enable SysTick interrupt
    // - Enable SysTick counter
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

// SysTick Handler function called every millisecond
void SysTick_Handler(){
    // Decrement ms_counter if it is greater than zero
    if (ms_counter) ms_counter--;
    
    // Increment millisecond counter
    millis++;
}

// Function to create a delay in milliseconds
void delay_ms(uint32_t ms){
    ms_counter = ms;      // Set the ms_counter to the requested delay
    while (ms_counter);   // Wait until ms_counter reaches zero
}

// Function to get the number of milliseconds since system startup
uint32_t getMillis(){
    return millis;        // Return the current millisecond count
}
