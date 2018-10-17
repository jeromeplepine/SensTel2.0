################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/dual_driver_vnh5019.c \
../src/encoder_ad36.c \
../src/main.c \
../src/pwm.c \
../src/uart.c 

OBJS += \
./src/dual_driver_vnh5019.o \
./src/encoder_ad36.o \
./src/main.o \
./src/pwm.o \
./src/uart.o 

C_DEPS += \
./src/dual_driver_vnh5019.d \
./src/encoder_ad36.d \
./src/main.d \
./src/pwm.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../standalone_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


