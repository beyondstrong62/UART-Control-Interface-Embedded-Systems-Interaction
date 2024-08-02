#pragma once  // Ensure this file is included only once in a single compilation

#include "stm32f446xx.h"  // Include STM32F446xx microcontroller definitions

// Function prototypes for SysTick timer initialization, handler, and delay functions

// Function to initialize the SysTick timer
void SysTick_Init(void);

// SysTick Handler function to be called when SysTick interrupt occurs
void SysTick_Handler(void);

// Function to create a delay in milliseconds
void delay_ms(uint32_t ms);

// Function to get the current milliseconds since the system started
uint32_t getMillis(void);
