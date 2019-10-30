################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5

ORDERED_OBJS += \
"./SystemConfig.obj" \
"./main.obj" \
"./startup_ccs.obj" \
"./WallFollow/Floodfill.obj" \
"./WallFollow/PID.obj" \
"./WallFollow/WallFollow.obj" \
"./Timer/Timer.obj" \
"./STR/Control_initialize.obj" \
"./STR/STR_Indirect.obj" \
"./STR/Uocluong.obj" \
"./STR/rtGetInf.obj" \
"./STR/rtGetNaN.obj" \
"./STR/rt_nonfinite.obj" \
"./STR/speed_control.obj" \
"./QEI/qei.obj" \
"./ImageProcess/HostComm.obj" \
"./ImageProcess/ImgProcess.obj" \
"./ImageProcess/Img_PID.obj" \
"./IR/IR.obj" \
"./Eeprom/EEPROM.obj" \
"./Buzzer/Buzzer.obj" \
"./Button/Button.obj" \
"./Bluetooth/Bluetooth.obj" \
"./Bluetooth/uartstdio.obj" \
"./Bluetooth/ustdlib.obj" \
"./Battery/Bettery.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"C:\ti\TivaWare_C_Series-2.1.1.71\driverlib\ccs\Debug\driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include WallFollow/subdir_vars.mk
-include Timer/subdir_vars.mk
-include STR/subdir_vars.mk
-include QEI/subdir_vars.mk
-include ImageProcess/subdir_vars.mk
-include IR/subdir_vars.mk
-include Eeprom/subdir_vars.mk
-include Buzzer/subdir_vars.mk
-include Button/subdir_vars.mk
-include Bluetooth/subdir_vars.mk
-include Battery/subdir_vars.mk
-include subdir_rules.mk
-include WallFollow/subdir_rules.mk
-include Timer/subdir_rules.mk
-include STR/subdir_rules.mk
-include QEI/subdir_rules.mk
-include ImageProcess/subdir_rules.mk
-include IR/subdir_rules.mk
-include Eeprom/subdir_rules.mk
-include Buzzer/subdir_rules.mk
-include Button/subdir_rules.mk
-include Bluetooth/subdir_rules.mk
-include Battery/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
RYA_robot_v1.2222.out \

EXE_OUTPUTS__QUOTED += \
"RYA_robot_v1.2222.out" \

BIN_OUTPUTS += \
RYA_robot_v1.2222.hex \

BIN_OUTPUTS__QUOTED += \
"RYA_robot_v1.2222.hex" \


# All Target
all: RYA_robot_v1.2222.out

# Tool invocations
RYA_robot_v1.2222.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -g --gcc --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off -z -m"RYA_robot_v1.2222.map" --heap_size=0 --stack_size=4096 -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="RYA_robot_v1.2222_linkInfo.xml" --rom_model -o "RYA_robot_v1.2222.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

RYA_robot_v1.2222.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.5/bin/armhex"  -o "RYA_robot_v1.2222.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "SystemConfig.pp" "main.pp" "startup_ccs.pp" "WallFollow\Floodfill.pp" "WallFollow\PID.pp" "WallFollow\WallFollow.pp" "Timer\Timer.pp" "STR\Control_initialize.pp" "STR\STR_Indirect.pp" "STR\Uocluong.pp" "STR\rtGetInf.pp" "STR\rtGetNaN.pp" "STR\rt_nonfinite.pp" "STR\speed_control.pp" "QEI\qei.pp" "ImageProcess\HostComm.pp" "ImageProcess\ImgProcess.pp" "ImageProcess\Img_PID.pp" "IR\IR.pp" "Eeprom\EEPROM.pp" "Buzzer\Buzzer.pp" "Button\Button.pp" "Bluetooth\Bluetooth.pp" "Bluetooth\uartstdio.pp" "Bluetooth\ustdlib.pp" "Battery\Bettery.pp" 
	-$(RM) "SystemConfig.obj" "main.obj" "startup_ccs.obj" "WallFollow\Floodfill.obj" "WallFollow\PID.obj" "WallFollow\WallFollow.obj" "Timer\Timer.obj" "STR\Control_initialize.obj" "STR\STR_Indirect.obj" "STR\Uocluong.obj" "STR\rtGetInf.obj" "STR\rtGetNaN.obj" "STR\rt_nonfinite.obj" "STR\speed_control.obj" "QEI\qei.obj" "ImageProcess\HostComm.obj" "ImageProcess\ImgProcess.obj" "ImageProcess\Img_PID.obj" "IR\IR.obj" "Eeprom\EEPROM.obj" "Buzzer\Buzzer.obj" "Button\Button.obj" "Bluetooth\Bluetooth.obj" "Bluetooth\uartstdio.obj" "Bluetooth\ustdlib.obj" "Battery\Bettery.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

