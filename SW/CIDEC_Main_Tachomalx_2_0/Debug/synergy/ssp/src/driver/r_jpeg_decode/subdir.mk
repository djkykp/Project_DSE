################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/driver/r_jpeg_decode/r_jpeg_decode.c 

OBJS += \
./synergy/ssp/src/driver/r_jpeg_decode/r_jpeg_decode.o 

C_DEPS += \
./synergy/ssp/src/driver/r_jpeg_decode/r_jpeg_decode.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/driver/r_jpeg_decode/%.o: ../synergy/ssp/src/driver/r_jpeg_decode/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\eclipse\../Utilities/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DSF_MESSAGE_CLASS -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy_cfg\ssp_cfg\framework" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\inc\framework\api" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\inc\framework\instances" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\inc\framework\tes" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy_cfg\ssp_cfg\framework\el" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\inc\framework\el" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\src\framework\el\tx" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy_cfg\ssp_cfg\driver" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\inc" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\inc\bsp" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\inc\driver\api" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\synergy\ssp\inc\driver\instances" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\src" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\src\synergy_gen" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\src\guix_gen\GNU" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\src\guix_gen\IAR" -I"C:\Users\alexl\e2_studio\CIDEC_Main_Tachomalx_1_4\src\guix" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


