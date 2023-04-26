################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1220/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Source/App/Main/main.o" \
"./Source/BSP/bsp.o" \
"./Source/BSP/startup_tm4c_gnu.o" \
"./Source/Driver/ADC/ADC_Driver.o" \
"./Source/Driver/CAN/CAN_Driver.o" \
"./Source/Driver/GPIO/GPIOdriver.o" \
"./Source/Driver/I2C/I2C.o" \
"./Source/Driver/LCD/LCD.o" \
"./Source/Driver/SPI/SPI.o" \
"./Source/Driver/Timer/Timer.o" \
"./Source/Driver/Timer/timercnter.o" \
"./Source/Driver/UART/UART.o" \
"./Source/Middleware/MCP3208/MCP3208.o" \
"./Source/Middleware/OLED_SSD1306/SSD1306.o" \
"./Source/Middleware/RTC_DS3231/DS3231.o" \
-Wl,-T"../tm4c123gh6pm.lds" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-lc \
-Wl,--end-group \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Source/App/Main/subdir_vars.mk
-include Source/BSP/subdir_vars.mk
-include Source/Driver/ADC/subdir_vars.mk
-include Source/Driver/CAN/subdir_vars.mk
-include Source/Driver/GPIO/subdir_vars.mk
-include Source/Driver/I2C/subdir_vars.mk
-include Source/Driver/LCD/subdir_vars.mk
-include Source/Driver/SPI/subdir_vars.mk
-include Source/Driver/Timer/subdir_vars.mk
-include Source/Driver/UART/subdir_vars.mk
-include Source/Middleware/MCP3208/subdir_vars.mk
-include Source/Middleware/OLED_SSD1306/subdir_vars.mk
-include Source/Middleware/RTC_DS3231/subdir_vars.mk
-include subdir_rules.mk
-include Source/App/Main/subdir_rules.mk
-include Source/BSP/subdir_rules.mk
-include Source/Driver/ADC/subdir_rules.mk
-include Source/Driver/CAN/subdir_rules.mk
-include Source/Driver/GPIO/subdir_rules.mk
-include Source/Driver/I2C/subdir_rules.mk
-include Source/Driver/LCD/subdir_rules.mk
-include Source/Driver/SPI/subdir_rules.mk
-include Source/Driver/Timer/subdir_rules.mk
-include Source/Driver/UART/subdir_rules.mk
-include Source/Middleware/MCP3208/subdir_rules.mk
-include Source/Middleware/OLED_SSD1306/subdir_rules.mk
-include Source/Middleware/RTC_DS3231/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Application.out \

EXE_OUTPUTS__QUOTED += \
"Application.out" \


# All Target
all: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Application.out"

# Tool invocations
Application.out: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: GNU Linker'
	"C:/ti/ccs1220/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc-9.2.1.exe" -mfpu=fpv4-sp-d16 -DPART_TM4C123GH6PM -O0 -fsigned-char -ffunction-sections -fdata-sections -Wall -specs="nosys.specs" -march=armv7e-m -mthumb -mfloat-abi=soft -Wl,-Map,"Application.map" -o"Application.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "Source\App\Main\main.o" "Source\BSP\bsp.o" "Source\BSP\startup_tm4c_gnu.o" "Source\Driver\ADC\ADC_Driver.o" "Source\Driver\CAN\CAN_Driver.o" "Source\Driver\GPIO\GPIOdriver.o" "Source\Driver\I2C\I2C.o" "Source\Driver\LCD\LCD.o" "Source\Driver\SPI\SPI.o" "Source\Driver\Timer\Timer.o" "Source\Driver\Timer\timercnter.o" "Source\Driver\UART\UART.o" "Source\Middleware\MCP3208\MCP3208.o" "Source\Middleware\OLED_SSD1306\SSD1306.o" "Source\Middleware\RTC_DS3231\DS3231.o" 
	-$(RM) "Source\App\Main\main.d" "Source\BSP\bsp.d" "Source\BSP\startup_tm4c_gnu.d" "Source\Driver\ADC\ADC_Driver.d" "Source\Driver\CAN\CAN_Driver.d" "Source\Driver\GPIO\GPIOdriver.d" "Source\Driver\I2C\I2C.d" "Source\Driver\LCD\LCD.d" "Source\Driver\SPI\SPI.d" "Source\Driver\Timer\Timer.d" "Source\Driver\Timer\timercnter.d" "Source\Driver\UART\UART.d" "Source\Middleware\MCP3208\MCP3208.d" "Source\Middleware\OLED_SSD1306\SSD1306.d" "Source\Middleware\RTC_DS3231\DS3231.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

