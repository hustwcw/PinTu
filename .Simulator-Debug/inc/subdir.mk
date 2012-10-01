################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../inc/RefreshTimeTimerEventListener.cpp 

OBJS += \
./inc/RefreshTimeTimerEventListener.o 

CPP_DEPS += \
./inc/RefreshTimeTimerEventListener.d 


# Each subdirectory must supply rules for building sources it contributes
inc/%.o: ../inc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"D:/bada/1.0.0/include" -I"D:/bada/1.0.0/IDE/workspace/PinTu/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"D:/bada/1.0.0/include" -I"D:/bada/1.0.0/IDE/workspace/PinTu/inc" -O0 -g3 -Wall -E -fmessage-length=0 -o"D:/bada/1.0.0/IDE/workspace/repository/PinTu/Simulator-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '


