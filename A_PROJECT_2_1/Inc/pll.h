#pragma once  // Ensure this file is included only once in a single compilation

// PLL configuration values for setting the clock speed
#define PLL_M       8ul     // PLLM: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
#define PLL_N       180ul   // PLLN: Main PLL (PLL) multiplication factor for VCO
#define PLL_P       0ul     // PLLP: Main PLL (PLL) division factor for main system clock
#define PLL_Q       2ul     // PLLQ: Main PLL (PLL) division factor for USB OTG FS, SDIO, and random number generator clocks

// Clock frequencies
#define HCLK_FREQ   180000000uL   // HCLK frequency (System clock frequency)
#define APB1_FREQ   (HCLK_FREQ/4) // APB1 peripheral clock frequency (HCLK divided by 4)
#define APB2_FREQ   (HCLK_FREQ/2) // APB2 peripheral clock frequency (HCLK divided by 2)

// Function prototype for configuring the clock speed using PLL
void clockSpeed_PLL(void);
