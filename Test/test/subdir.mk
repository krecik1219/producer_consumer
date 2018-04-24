################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/ProducerConsumerTest.cpp 

OBJS += \
./test/ProducerConsumerTest.o 

CPP_DEPS += \
./test/ProducerConsumerTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -I"/media/kretek/Workspace/cpp/eclipse-linux/producer_consumer/contrib" -I"/media/kretek/Workspace/cpp/eclipse-linux/producer_consumer/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


