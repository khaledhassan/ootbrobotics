################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
LIB_AS_ARGS :=
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
HEX_FLASH_FILE_PATH :=
HEX_FLASH_FILE_PATH_AS_ARGS :=
HEX_EEPROM_FILE_PATH :=
HEX_EEPROM_FILE_PATH_AS_ARGS :=
LSS_FILE_PATH :=
LSS_FILE_PATH_AS_ARGS :=
MAP_FILE_PATH :=
MAP_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=C:/Program Files (x86)/Atmel/AVR Studio 5.0/AVR ToolChain/bin/
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../src/ \
../src/asf/ \
../src/asf/common/ \
../src/asf/common/boards/ \
../src/asf/common/boards/user_board/ \
../src/asf/common/services/ \
../src/asf/common/utils/ \
../src/asf/common/utils/interrupt/ \
../src/asf/common/utils/make/ \
../src/asf/xmega/ \
../src/asf/xmega/drivers/ \
../src/asf/xmega/utils/ \
../src/asf/xmega/utils/assembler/ \
../src/asf/xmega/utils/bit_handling/ \
../src/asf/xmega/utils/preprocessor/ \
../src/config/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../ADC.c \
../lcd.c \
../motor.c \
../picServo.c \
../RTC.c \
../src/asf/common/boards/user_board/init.c \
../src/main.c \
../uart.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ADC.o \
lcd.o \
motor.o \
picServo.o \
RTC.o \
src/asf/common/boards/user_board/init.o \
src/main.o \
uart.o


OBJS_AS_ARGS +=  \
ADC.o \
lcd.o \
motor.o \
picServo.o \
RTC.o \
src/asf/common/boards/user_board/init.o \
src/main.o \
uart.o


C_DEPS +=  \
ADC.d \
lcd.d \
motor.d \
picServo.d \
RTC.d \
src/asf/common/boards/user_board/init.d \
src/main.d \
uart.d


C_DEPS_AS_ARGS +=  \
ADC.d \
lcd.d \
motor.d \
picServo.d \
RTC.d \
src/asf/common/boards/user_board/init.d \
src/main.d \
uart.d


OUTPUT_FILE_PATH +=Epiphany_DIY_v1.elf

OUTPUT_FILE_PATH_AS_ARGS +=Epiphany_DIY_v1.elf

HEX_FLASH_FILE_PATH +=Epiphany_DIY_v1.hex

HEX_FLASH_FILE_PATH_AS_ARGS +=Epiphany_DIY_v1.hex

HEX_EEPROM_FILE_PATH +=Epiphany_DIY_v1.eep

HEX_EEPROM_FILE_PATH_AS_ARGS +=Epiphany_DIY_v1.eep

LSS_FILE_PATH +=Epiphany_DIY_v1.lss

LSS_FILE_PATH_AS_ARGS +=Epiphany_DIY_v1.lss

MAP_FILE_PATH =Epiphany_DIY_v1.map

MAP_FILE_PATH_AS_ARGS =Epiphany_DIY_v1.map

LIB_AS_ARGS +=libEpiphany_DIY_v1.a

ADDITIONAL_DEPENDENCIES:= $(HEX_FLASH_FILE_PATH) size

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR/GNU C Compiler

















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -DBOARD=USER_BOARD -DF_CPU=32000000  -I"../src" -I"../src/asf/common/applications/user_application/user_board" -I"../src/asf/common/boards" -I"../src/asf/common/boards/user_board" -I"../src/asf/common/utils" -I"../src/asf/xmega/utils" -I"../src/asf/xmega/utils/preprocessor" -I"../src/config" -I".."  -Os -fdata-sections -ffunction-sections -g3 -Wall -c -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax  -mmcu=atxmega64a1   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<

src/asf/common/boards/user_board/%.o: ../src/asf/common/boards/user_board/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -DBOARD=USER_BOARD -DF_CPU=32000000  -I"../src" -I"../src/asf/common/applications/user_application/user_board" -I"../src/asf/common/boards" -I"../src/asf/common/boards/user_board" -I"../src/asf/common/utils" -I"../src/asf/xmega/utils" -I"../src/asf/xmega/utils/preprocessor" -I"../src/config" -I".."  -Os -fdata-sections -ffunction-sections -g3 -Wall -c -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax  -mmcu=atxmega64a1   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<

src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -DBOARD=USER_BOARD -DF_CPU=32000000  -I"../src" -I"../src/asf/common/applications/user_application/user_board" -I"../src/asf/common/boards" -I"../src/asf/common/boards/user_board" -I"../src/asf/common/utils" -I"../src/asf/xmega/utils" -I"../src/asf/xmega/utils/preprocessor" -I"../src/config" -I".."  -Os -fdata-sections -ffunction-sections -g3 -Wall -c -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax  -mmcu=atxmega64a1   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<



# AVR/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

# AVR/GNU C/C++ Linker
$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU C/C++ Linker
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -Wl,--gc-sections -mrelax -Wl,--relax  -mmcu=atxmega64a1   -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@



$(HEX_FLASH_FILE_PATH): $(OUTPUT_FILE_PATH)
	$(QUOTE)$(AVR_APP_PATH)avr-objcopy.exe$(QUOTE) -O ihex -R .eeprom -R .fuse -R .lock -R .signature  $(QUOTE)$<$(QUOTE) $(QUOTE)$@$(QUOTE)

$(HEX_EEPROM_FILE_PATH): $(OUTPUT_FILE_PATH)
	-$(QUOTE)$(AVR_APP_PATH)avr-objcopy.exe$(QUOTE) -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex $(QUOTE)$<$(QUOTE) $(QUOTE)$@$(QUOTE) || exit 0

$(LSS_FILE_PATH): $(OUTPUT_FILE_PATH)
	$(QUOTE)$(AVR_APP_PATH)avr-objdump.exe$(QUOTE) -h -S $(QUOTE)$<$(QUOTE) > $(QUOTE)$@$(QUOTE)

size: $(OUTPUT_FILE_PATH)
	@$(QUOTE)$(AVR_APP_PATH)avr-size.exe$(QUOTE) -C --mcu=atxmega64a1 $(OUTPUT_FILE_PATH_AS_ARGS)

# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) $(LIB_AS_ARGS) $(HEX_FLASH_FILE_PATH_AS_ARGS) $(HEX_EEPROM_FILE_PATH_AS_ARGS) $(LSS_FILE_PATH_AS_ARGS) $(MAP_FILE_PATH_AS_ARGS)

