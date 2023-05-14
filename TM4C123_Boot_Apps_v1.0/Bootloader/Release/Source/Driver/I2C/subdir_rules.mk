################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/Driver/I2C/%.o: ../Source/Driver/I2C/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc-9.2.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16 -DPART_TM4C123GH6PM -I"D:/embedded/Code_Composer_Studio/Boot_App/Bootloader" -I"D:/embedded/Code_Composer_Studio/Boot_App/Bootloader/Source/BSP" -I"D:/embedded/Code_Composer_Studio/Boot_App/Bootloader/Source/CMSIS" -I"D:/embedded/Code_Composer_Studio/Boot_App/Bootloader/Source/Common" -I"D:/embedded/Code_Composer_Studio/Boot_App/Bootloader/Source/Interface" -I"C:/ti/ccs1220/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/arm-none-eabi/include" -O0 -fsigned-char -ffunction-sections -fdata-sections -g -Wall -specs="nosys.specs" -MMD -MP -MF"Source/Driver/I2C/$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


