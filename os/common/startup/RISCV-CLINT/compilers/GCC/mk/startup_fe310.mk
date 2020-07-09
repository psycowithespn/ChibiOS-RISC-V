# List of the ChibiOS generic FE310 startup files.
STARTUPSRC = $(CHIBIOS_RV)/os/common/startup/RISCV-CLINT/compilers/GCC/crt1.c
          
STARTUPASM = $(CHIBIOS_RV)/os/common/startup/RISCV-CLINT/compilers/GCC/crt0.S \
             $(CHIBIOS_RV)/os/common/startup/RISCV-CLINT/compilers/GCC/vectors.S

STARTUPINC = $(CHIBIOS)/os/common/portability/GCC \
             $(CHIBIOS_RV)/os/common/startup/RISCV-CLINT/compilers/GCC \
             $(CHIBIOS_RV)/os/common/startup/RISCV-CLINT/devices/FE310-G002 \

STARTUPLD  = $(CHIBIOS_RV)/os/common/startup/RISCV-CLINT/compilers/GCC/ld

# Shared variables
ALLXASMSRC += $(STARTUPASM)
ALLCSRC    += $(STARTUPSRC)
ALLINC     += $(STARTUPINC)

