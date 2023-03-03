################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/Driver/CAN/%.o: ../Source/Driver/CAN/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc-9.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16 -DPART_TM4C123GH6PM -I"D:/embedded/CCS/Projects/Software_test/TM4C123_PRJ_TEST" -I"D:/embedded/CCS/Projects/Software_test/TM4C123_PRJ_TEST/Source/CMSIS" -I"D:/embedded/CCS/Projects/Software_test/TM4C123_PRJ_TEST/Source/Interface" -I"D:/embedded/CCS/Projects/Software_test/TM4C123_PRJ_TEST/Source/BSP" -I"D:/embedded/CCS/Projects/Software_test/TM4C123_PRJ_TEST/Source/Common" -I"C:/ti/ccs1220/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/arm-none-eabi/include" -Og -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -specs="nosys.specs" -MMD -MP -MF"Source/Driver/CAN/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


