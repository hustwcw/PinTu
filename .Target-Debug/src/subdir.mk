################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Form1.cpp \
../src/FormHelp.cpp \
../src/FormMgr.cpp \
../src/PinTu.cpp \
../src/PinTuEntry.cpp 

OBJS += \
./src/Form1.o \
./src/FormHelp.o \
./src/FormMgr.o \
./src/PinTu.o \
./src/PinTuEntry.o 

CPP_DEPS += \
./src/Form1.d \
./src/FormHelp.d \
./src/FormMgr.d \
./src/PinTu.d \
./src/PinTuEntry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"D:/bada1.2.1/include" -I"C:/Users/Administrator/worksapce_bada1.2.1/PinTu/inc" -O0 -g -Wall -c -fpic -fshort-wchar -mcpu=cortex-a8 -mfpu=vfpv3 -mfloat-abi=hard -mlittle-endian -mthumb-interwork -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	arm-samsung-nucleuseabi-g++ -D_DEBUG -DSHP -I"D:/bada1.2.1/include" -I"C:/Users/Administrator/worksapce_bada1.2.1/PinTu/inc" -O0 -g -Wall -E -fpic -fshort-wchar -mcpu=cortex-a8 -mfpu=vfpv3 -mfloat-abi=hard -mlittle-endian -mthumb-interwork -o"C:/Users/Administrator/worksapce_bada1.2.1/repository/PinTu/Target-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


