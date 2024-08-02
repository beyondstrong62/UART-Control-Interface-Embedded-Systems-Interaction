/*
 * case_1_led_blinking.h
 *
 *  Created on: Jul 29, 2024
 *      Author: SUGAM SHAW
 */

// Ensure this file is included only once in a single compilation
#pragma once

// Function prototypes for initializing, starting, and stopping PWM intensity control

// Function to initialize the PWM intensity control setup
void PWM_Intensity_init(void);

// Function to start the PWM intensity control
void PWM_Intensity_start(void);

// Function to stop the PWM intensity control
void PWM_Intensity_close(void);
