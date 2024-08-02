#include "usart.h"
#include <stdint.h>
#include "stm32f446xx.h"

// Define macros for alternate functions
#define PA2_AF           (2 << 4)  // Alternate function mode for PA2
#define PA2_AF_USART2_TX (7 << 8)  // USART2 TX alternate function for PA2
#define PA3_AF           (2 << 6)  // Alternate function mode for PA3
#define PA3_AF_USART2_RX (7 << 12) // USART2 RX alternate function for PA3

// Function to display menu options over UART
void displayoption(void)
{
	UART2_SendString("\n\r------------------------------------\n\r");
	UART2_SendString("\n\r    Embedded C: Project 2\n\r");
	UART2_SendString("\n\r------------------------------------\n\r");
	UART2_SendString("\n\rMenu:\n\r");
	UART2_SendString("1. Led Blinking with 5 different delays \n\r");
	UART2_SendString("2. Invoking a PWM and varying intensity of led\n\r");
	UART2_SendString("3. Exiting the utility\n\r");
	UART2_SendString("\n\rEnter your choice(1-3): ");
}

// Function to send a single character over UART2
void UART2_SendChar(char ch)
{
	USART2->DR = ch; // Load the data register with the character
	while(!(USART2->SR & USART_SR_TXE)); // Wait until the transmit data register is empty
}

// Function to send a string over UART2
void UART2_SendString(char *string)
{
	while(*string != '\0')
	{
		UART2_SendChar(*string); // Send each character of the string
		string++;
	}
}

// Function to configure USART2
void Usart2_config(void)
{
	// Enable the clocks for GPIOA and USART2
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable USART2 clock

	// Configure PA2 and PA3 for alternate function (USART2 TX/RX)
	GPIOA->MODER |= PA2_AF;  // Set PA2 to alternate function mode
	GPIOA->MODER |= PA3_AF;  // Set PA3 to alternate function mode

	GPIOA->OSPEEDR |= (3 << 4); // Set high speed for PA2
	GPIOA->OSPEEDR |= (3 << 6); // Set high speed for PA3

	GPIOA->AFR[0] |= PA2_AF_USART2_TX; // Set alternate function for PA2 as USART2 TX
	GPIOA->AFR[0] |= PA3_AF_USART2_RX; // Set alternate function for PA3 as USART2 RX

	USART2->CR1 = 0x00; // Clear all settings in CR1
	USART2->CR1 |= USART_CR1_UE; // Enable USART2

	USART2->CR1 &= ~(1 << 12); // Set word length to 8 bits

	USART2->BRR |= (1 << 0); // Set baud rate mantissa
	USART2->BRR |= (24 << 4); // Set baud rate fraction

	USART2->CR1 |= USART_CR1_RE; // Enable receiver
	USART2->CR1 |= USART_CR1_TE; // Enable transmitter
}

// Function to receive data from UART2
uint8_t receiverdata(void)
{
	while(!(USART2->SR & USART_SR_RXNE)); // Wait until data is received
	uint8_t data = USART2->DR; // Read the received data
	return data; // Return the received data
}
