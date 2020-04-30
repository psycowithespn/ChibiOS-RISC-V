# List of the ChibiOS/RT RISCV generic port files.
PORTSRC = $(CHIBIOS_RV)/os/common/ports/RISCV/chcore.c

PORTASM = $(CHIBIOS_RV)/os/common/ports/RISCV/compilers/GCC/chcoreasm.S

PORTINC = $(CHIBIOS_RV)/os/common/ports/RISCV \
          $(CHIBIOS)/os/common/ports/RISCV/compilers/GCC

# Shared variables
ALLXASMSRC += $(PORTASM)
ALLCSRC    += $(PORTSRC)
ALLINC     += $(PORTINC)
