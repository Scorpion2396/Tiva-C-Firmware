################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/MCP3208/MCP3208.c 

C_DEPS += \
./Middleware/MCP3208/MCP3208.d 

OBJS += \
./Middleware/MCP3208/MCP3208.o 


# Each subdirectory must supply rules for building sources it contributes
Middleware/MCP3208/%.o: ../Middleware/MCP3208/%.c Middleware/MCP3208/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Middleware-2f-MCP3208

clean-Middleware-2f-MCP3208:
	-$(RM) ./Middleware/MCP3208/MCP3208.d ./Middleware/MCP3208/MCP3208.o

.PHONY: clean-Middleware-2f-MCP3208

