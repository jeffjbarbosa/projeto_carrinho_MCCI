################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc_battery.c \
../src/avr_spi.c \
../src/avr_usart.c \
../src/main.c \
../src/motor.c 

OBJS += \
./src/adc_battery.o \
./src/avr_spi.o \
./src/avr_usart.o \
./src/main.o \
./src/motor.o 

C_DEPS += \
./src/adc_battery.d \
./src/avr_spi.d \
./src/avr_usart.d \
./src/main.d \
./src/motor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=61000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


