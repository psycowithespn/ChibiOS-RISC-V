# List of the ChibiOS/RT RISCV generic port files.
PORTSRC = $(CHIBIOS_RV)/os/common/ports/RISCV-CLINT/chcore.c

PORTASM = $(CHIBIOS_RV)/os/common/ports/RISCV-CLINT/compilers/GCC/chcoreasm.S

PORTINC = $(CHIBIOS_RV)/os/common/ports/RISCV-CLINT \
          $(CHIBIOS)/os/common/ports/RISCV-CLINT/compilers/GCC

# Shared variables
ALLXASMSRC += $(PORTASM)
ALLCSRC    += $(PORTSRC)
ALLINC     += $(PORTINC)
