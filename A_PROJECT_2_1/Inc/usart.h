#pragma once  // Ensure this file is included only once in a single compilation

#include <stdint.h>  // Include standard integer types

// Function prototypes for UART/USART communication

// Function to display available options or settings
void displayoption(void);

// Function to send a single character via UART2
void UART2_SendChar(char ch);

// Function to send a string via UART2
void UART2_SendString(char *string);

// Function to configure USART2 settings
void Usart2_config(void);

// Function to receive a byte of data via UART2
uint8_t receiverdata(void);
