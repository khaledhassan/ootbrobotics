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
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../adc.c \
../ATtinyServo.c \
../clock.c \
../example4.c \
../lcd.c \
../main.c \
../motor.c \
../RTC.c \
../uart.c \
../utility.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
adc.o \
ATtinyServo.o \
clock.o \
example4.o \
lcd.o \
main.o \
motor.o \
RTC.o \
uart.o \
utility.o

OBJS_AS_ARGS +=  \
adc.o \
ATtinyServo.o \
clock.o \
example4.o \
lcd.o \
main.o \
motor.o \
RTC.o \
uart.o \
utility.o

C_DEPS +=  \
adc.d \
ATtinyServo.d \
clock.d \
example4.d \
lcd.d \
main.d \
motor.d \
RTC.d \
uart.d \
utility.d

C_DEPS_AS_ARGS +=  \
adc.d \
ATtinyServo.d \
clock.d \
example4.d \
lcd.d \
main.d \
motor.d \
RTC.d \
uart.d \
utility.d

OUTPUT_FILE_PATH +=Epiphany_v2.elf

OUTPUT_FILE_PATH_AS_ARGS +=Epiphany_v2.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler





















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -DF_CPU=32000000  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atxmega128a1u -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Epiphany_v2.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=atxmega128a1u -Wl,-u,vfprintf -lprintf_flt -lm 
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Epiphany_v2.elf" "Epiphany_v2.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Epiphany_v2.elf" "Epiphany_v2.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Epiphany_v2.elf" > "Epiphany_v2.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "Epiphany_v2.elf" "Epiphany_v2.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-size.exe" "Epiphany_v2.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Epiphany_v2.elf" "Epiphany_v2.a" "Epiphany_v2.hex" "Epiphany_v2.lss" "Epiphany_v2.eep" "Epiphany_v2.map" "Epiphany_v2.srec"
	