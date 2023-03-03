################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CAN/CAN_Driver.c 

C_DEPS += \
./Driver/CAN/CAN_Driver.d 

OBJS += \
./Driver/CAN/CAN_Driver.o 


# Each subdirectory must supply rules for building sources it contributes
Driver/CAN/%.o: ../Driver/CAN/%.c Driver/CAN/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Driver-2f-CAN

clean-Driver-2f-CAN:
	-$(RM) ./Driver/CAN/CAN_Driver.d ./Driver/CAN/CAN_Driver.o

.PHONY: clean-Driver-2f-CAN

