################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/aff_mrp.c \
../src/aff_p4.c \
../src/main.c \
../src/pupitre.c 

OBJS += \
./src/aff_mrp.o \
./src/aff_p4.o \
./src/main.o \
./src/pupitre.o 

C_DEPS += \
./src/aff_mrp.d \
./src/aff_p4.d \
./src/main.d \
./src/pupitre.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

