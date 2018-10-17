################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/ads1015.c \
../src/ann.c \
../src/can.c \
../src/cv7.c \
../src/encoder_ad36.c \
../src/fifo.c \
../src/i2c.c \
../src/inputcapture.c \
../src/interrupts.c \
../src/main.c \
../src/rfm95w_lora.c \
../src/ringbuffer.c \
../src/senstel_acq.c \
../src/senstel_sd.c \
../src/setup.c \
../src/spi.c \
../src/timer.c \
../src/uart.c 

OBJS += \
./src/ads1015.o \
./src/ann.o \
./src/can.o \
./src/cv7.o \
./src/encoder_ad36.o \
./src/fifo.o \
./src/i2c.o \
./src/inputcapture.o \
./src/interrupts.o \
./src/main.o \
./src/rfm95w_lora.o \
./src/ringbuffer.o \
./src/senstel_acq.o \
./src/senstel_sd.o \
./src/setup.o \
./src/spi.o \
./src/timer.o \
./src/uart.o 

C_DEPS += \
./src/ads1015.d \
./src/ann.d \
./src/can.d \
./src/cv7.d \
./src/encoder_ad36.d \
./src/fifo.d \
./src/i2c.d \
./src/inputcapture.d \
./src/interrupts.d \
./src/main.d \
./src/rfm95w_lora.d \
./src/ringbuffer.d \
./src/senstel_acq.d \
./src/senstel_sd.d \
./src/setup.d \
./src/spi.d \
./src/timer.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../freertos901_xilinx_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


