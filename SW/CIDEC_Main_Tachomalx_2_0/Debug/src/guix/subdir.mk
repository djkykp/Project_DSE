################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/guix/hmi_event_handler.c \
../src/guix/lcd_setup.c 

OBJS += \
./src/guix/hmi_event_handler.o \
./src/guix/lcd_setup.o 

C_DEPS += \
./src/guix/hmi_event_handler.d \
./src/guix/lcd_setup.d 


# Each subdirectory must supply rules for building sources it contributes
src/guix/%.o: ../src/guix/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\eclipse\../Utilities/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DSF_MESSAGE_CLASS -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy_cfg\ssp_cfg\framework" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\inc\framework\api" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\inc\framework\instances" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\inc\framework\tes" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy_cfg\ssp_cfg\framework\el" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\inc\framework\el" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\src\framework\el\tx" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy_cfg\ssp_cfg\driver" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\inc" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\inc\bsp" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\inc\driver\api" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\synergy\ssp\inc\driver\instances" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\src" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\src\synergy_gen" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\src\guix_gen\GNU" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\src\guix_gen\IAR" -I"C:\Users\JeLar\OneDrive\Documentos\Curso de SW Embebido UTEQ\Project_DSE\SW\CIDEC_Main_Tachomalx_2_0\src\guix" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


