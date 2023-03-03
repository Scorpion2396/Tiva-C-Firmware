################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/SPI/SPI.c 

C_DEPS += \
./Driver/SPI/SPI.d 

OBJS += \
./Driver/SPI/SPI.o 


# Each subdirectory must supply rules for building sources it contributes
Driver/SPI/%.o: ../Driver/SPI/%.c Driver/SPI/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Driver-2f-SPI

clean-Driver-2f-SPI:
	-$(RM) ./Driver/SPI/SPI.d ./Driver/SPI/SPI.o

.PHONY: clean-Driver-2f-SPI

