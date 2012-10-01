################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Form1.cpp \
../src/PinTu.cpp \
../src/PinTuEntry.cpp 

OBJS += \
./src/Form1.o \
./src/PinTu.o \
./src/PinTuEntry.o 

CPP_DEPS += \
./src/Form1.d \
./src/PinTu.d \
./src/PinTuEntry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	arm-samsung-nucleuseabi-g++ -DSHP -I"D:/bada1.2.0/include" -I"C:/Users/Administrator/worksapce_bada1.2/PinTu/inc" -Os -Wall -c -fpic -fshort-wchar -mcpu=cortex-a8 -mfpu=vfpv3 -mfloat-abi=hard -mlittle-endian -mthumb-interwork -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	arm-samsung-nucleuseabi-g++ -DSHP -I"D:/bada1.2.0/include" -I"C:/Users/Administrator/worksapce_bada1.2/PinTu/inc" -Os -Wall -E -fpic -fshort-wchar -mcpu=cortex-a8 -mfpu=vfpv3 -mfloat-abi=hard -mlittle-endian -mthumb-interwork -o"C:/Users/Administrator/worksapce_bada1.2/repository/PinTu/Target-Release/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


