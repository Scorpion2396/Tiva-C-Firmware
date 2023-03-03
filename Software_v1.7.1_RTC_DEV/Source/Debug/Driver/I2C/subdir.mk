################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/I2C/I2C.c 

C_DEPS += \
./Driver/I2C/I2C.d 

OBJS += \
./Driver/I2C/I2C.o 


# Each subdirectory must supply rules for building sources it contributes
Driver/I2C/%.o: ../Driver/I2C/%.c Driver/I2C/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Driver-2f-I2C

clean-Driver-2f-I2C:
	-$(RM) ./Driver/I2C/I2C.d ./Driver/I2C/I2C.o

.PHONY: clean-Driver-2f-I2C

