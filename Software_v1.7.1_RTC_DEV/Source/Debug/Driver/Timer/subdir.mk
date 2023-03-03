################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Timer/Timer.c 

C_DEPS += \
./Driver/Timer/Timer.d 

OBJS += \
./Driver/Timer/Timer.o 


# Each subdirectory must supply rules for building sources it contributes
Driver/Timer/%.o: ../Driver/Timer/%.c Driver/Timer/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Driver-2f-Timer

clean-Driver-2f-Timer:
	-$(RM) ./Driver/Timer/Timer.d ./Driver/Timer/Timer.o

.PHONY: clean-Driver-2f-Timer

