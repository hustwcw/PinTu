################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

REPOSITORY_ROOT := C:/Users/Administrator/worksapce_bada1.2.1/repository/PinTu/Target-Debug

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: PinTu.exe

# Tool invocations
PinTu.exe: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: bada C++ Linker'
	@echo 'ldflags: -nostdlib -lc-newlib -lm-newlib -L"D:/bada1.2.1/Model/Wave_LP1/Target" -L"D:/bada1.2.1/Tools/Toolchains/ARM/arm-samsung-nucleuseabi/lib" -L"D:/bada1.2.1/Tools/Toolchains/ARM/lib/gcc/arm-samsung-nucleuseabi/4.4.1" -L"C:/Users/Administrator/worksapce_bada1.2.1/PinTu/lib" -shared -o"PinTu.exe" ./src/Form1.o ./src/FormHelp.o ./src/FormMgr.o ./src/PinTu.o ./src/PinTuEntry.o '
	arm-samsung-nucleuseabi-ld @ldflags @ldobjs  $(USER_OBJS) $(LIBS) -lstdc++ -lgcc_s
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS) PinTu.exe $(REPOSITORY_ROOT)/*
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
