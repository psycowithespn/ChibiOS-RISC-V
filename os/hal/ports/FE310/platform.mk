# List of all the template platform files.
ifeq ($(USE_SMART_BUILD),yes)

# Configuration files directory
ifeq ($(CONFDIR),)
  CONFDIR = .
endif

HALCONF := $(strip $(shell cat $(CONFDIR)/halconf.h | egrep -e "\#define"))

PLATFORMSRC := ${CHIBIOS_RV}/os/hal/ports/common/RISCV/clint/hal_st_lld.c \
               ${CHIBIOS_RV}/os/hal/ports/common/RISCV/plic/plic.c \
               ${CHIBIOS_RV}/os/hal/ports/FE310/hal_lld.c
ifneq ($(findstring HAL_USE_PAL TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/FE310/hal_pal_lld.c
endif
ifneq ($(findstring HAL_USE_SERIAL TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/FE310/hal_serial_lld.c
endif
else
PLATFORMSRC = ${CHIBIOS_RV}/os/hal/ports/common/RISCV/clint/hal_st_lld.c \
              ${CHIBIOS_RV}/os/hal/ports/common/RISCV/plic/plic.c \
              ${CHIBIOS_RV}/os/hal/ports/FE310/hal_lld.c \
              ${CHIBIOS_RV}/os/hal/ports/FE310/hal_pal_lld.c
endif

# Required include directories
PLATFORMINC = ${CHIBIOS_RV}/os/hal/ports/common/RISCV/plic \
              ${CHIBIOS_RV}/os/hal/ports/common/RISCV/clint \
              ${CHIBIOS_RV}/os/hal/ports/FE310

# Shared variables
ALLCSRC += $(PLATFORMSRC)
ALLINC  += $(PLATFORMINC)
