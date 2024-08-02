################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/case_1_led_blinking.c \
../Src/case_2_pwm.c \
../Src/main.c \
../Src/pll.c \
../Src/sysTick.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/usart.c 

OBJS += \
./Src/case_1_led_blinking.o \
./Src/case_2_pwm.o \
./Src/main.o \
./Src/pll.o \
./Src/sysTick.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/usart.o 

C_DEPS += \
./Src/case_1_led_blinking.d \
./Src/case_2_pwm.d \
./Src/main.d \
./Src/pll.d \
./Src/sysTick.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/case_1_led_blinking.cyclo ./Src/case_1_led_blinking.d ./Src/case_1_led_blinking.o ./Src/case_1_led_blinking.su ./Src/case_2_pwm.cyclo ./Src/case_2_pwm.d ./Src/case_2_pwm.o ./Src/case_2_pwm.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/pll.cyclo ./Src/pll.d ./Src/pll.o ./Src/pll.su ./Src/sysTick.cyclo ./Src/sysTick.d ./Src/sysTick.o ./Src/sysTick.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/usart.cyclo ./Src/usart.d ./Src/usart.o ./Src/usart.su

.PHONY: clean-Src

