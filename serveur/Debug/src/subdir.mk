################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/imdb.c \
../src/recherche.c \
../src/resultat.c 

OBJS += \
./src/imdb.o \
./src/recherche.o \
./src/resultat.o 

C_DEPS += \
./src/imdb.d \
./src/recherche.d \
./src/resultat.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/tomgs/tmp/ELE216/Eclipse/laboratoire3/troisieme-laboratoire/serveur/hdr" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


