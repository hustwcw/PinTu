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
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"D:/bada1.2.1/include" -I"C:/Users/Administrator/worksapce_bada1.2.1/PinTu/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"D:/bada1.2.1/include" -I"C:/Users/Administrator/worksapce_bada1.2.1/PinTu/inc" -O0 -g3 -Wall -E -fmessage-length=0 -o"C:/Users/Administrator/worksapce_bada1.2.1/repository/PinTu/Simulator-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


