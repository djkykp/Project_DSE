################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal_entry.c \
../src/hmi_thread_entry.c \
../src/hmi_thread_main.c 

OBJS += \
./src/hal_entry.o \
./src/hmi_thread_entry.o \
./src/hmi_thread_main.o 

C_DEPS += \
./src/hal_entry.d \
./src/hmi_thread_entry.d \
./src/hmi_thread_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\Synergy\e2studio_v6.2.1_ssp_v1.5.0\eclipse\../Utilities/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DSF_MESSAGE_CLASS -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy_cfg\ssp_cfg\framework" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\inc\framework\api" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\inc\framework\instances" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\inc\framework\tes" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy_cfg\ssp_cfg\framework\el" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\inc\framework\el" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\src\framework\el\tx" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy_cfg\ssp_cfg\driver" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\inc" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\inc\bsp" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\inc\driver\api" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\synergy\ssp\inc\driver\instances" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\src" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\src\synergy_gen" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\src\guix_gen\GNU" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\src\guix_gen\IAR" -I"C:\Users\alexl\e2_studio\v1.1\CIDEC_Main_Tachomalx_1_1\src\guix" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


