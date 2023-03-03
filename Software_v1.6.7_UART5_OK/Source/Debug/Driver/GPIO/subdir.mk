################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/GPIO/GPIOdriver.c 

C_DEPS += \
./Driver/GPIO/GPIOdriver.d 

OBJS += \
./Driver/GPIO/GPIOdriver.o 


# Each subdirectory must supply rules for building sources it contributes
Driver/GPIO/%.o: ../Driver/GPIO/%.c Driver/GPIO/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Driver-2f-GPIO

clean-Driver-2f-GPIO:
	-$(RM) ./Driver/GPIO/GPIOdriver.d ./Driver/GPIO/GPIOdriver.o

.PHONY: clean-Driver-2f-GPIO

