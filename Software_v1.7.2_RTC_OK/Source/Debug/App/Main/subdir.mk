################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Main/main.c 

C_DEPS += \
./App/Main/main.d 

OBJS += \
./App/Main/main.o 


# Each subdirectory must supply rules for building sources it contributes
App/Main/%.o: ../App/Main/%.c App/Main/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-App-2f-Main

clean-App-2f-Main:
	-$(RM) ./App/Main/main.d ./App/Main/main.o

.PHONY: clean-App-2f-Main

