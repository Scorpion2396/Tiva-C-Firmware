################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/ADC/ADC_Driver.c 

C_DEPS += \
./Driver/ADC/ADC_Driver.d 

OBJS += \
./Driver/ADC/ADC_Driver.o 


# Each subdirectory must supply rules for building sources it contributes
Driver/ADC/%.o: ../Driver/ADC/%.c Driver/ADC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Driver-2f-ADC

clean-Driver-2f-ADC:
	-$(RM) ./Driver/ADC/ADC_Driver.d ./Driver/ADC/ADC_Driver.o

.PHONY: clean-Driver-2f-ADC

