################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/LCD/LCD.c 

C_DEPS += \
./Driver/LCD/LCD.d 

OBJS += \
./Driver/LCD/LCD.o 


# Each subdirectory must supply rules for building sources it contributes
Driver/LCD/%.o: ../Driver/LCD/%.c Driver/LCD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Driver-2f-LCD

clean-Driver-2f-LCD:
	-$(RM) ./Driver/LCD/LCD.d ./Driver/LCD/LCD.o

.PHONY: clean-Driver-2f-LCD

