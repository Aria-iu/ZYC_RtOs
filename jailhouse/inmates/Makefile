#
# Jailhouse, a Linux-based partitioning hypervisor
#
# Copyright (c) Siemens AG, 2013
#
# Authors:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This work is licensed under the terms of the GNU GPL, version 2.  See
# the COPYING file in the top-level directory.
#

-include $(GEN_CONFIG_MK)

INMATES_LIB = $(src)/lib/$(SRCARCH)
export INMATES_LIB

INCLUDES := -I$(INMATES_LIB) \
	    -I$(src)/../include/arch/$(SRCARCH) \
	    -I$(src)/lib/include \
	    -I$(src)/../include \
		-I$(src)/../../ZYC_RtOs/log \
		-I$(src)/../../ZYC_RtOs/mem \
		-I$(src)/../../ZYC_RtOs/include \
		-I$(src)/../../ZYC_RtOs/mem/fsc \
		-I$(src)/../../ZYC_RtOs/core/include \
		-I$(src)/../../ZYC_RtOs/include/armv8 \
	       -I$(src)/../../ZYC_RtOs/include/armv8 	

ifeq ($(subst arm64,arm,$(SRCARCH)),arm)
INCLUDES += -I$(src)/../hypervisor/arch/arm-common/include
endif

LINUXINCLUDE  := $(INCLUDES)
KBUILD_AFLAGS := -D__ASSEMBLY__ -fno-PIE
KBUILD_CFLAGS := -g -Os -Wall -Wstrict-prototypes -Wtype-limits \
		 -Wmissing-declarations -Wmissing-prototypes \
		 -fno-strict-aliasing -fomit-frame-pointer -fno-pic \
		 -fno-common -fno-stack-protector -ffreestanding \
		 -ffunction-sections \
		 -D__LINUX_COMPILER_TYPES_H
ifneq ($(wildcard $(INC_CONFIG_H)),)
KBUILD_CFLAGS += -include $(INC_CONFIG_H)
endif

OBJCOPYFLAGS := -O binary
# prior to 4.19
LDFLAGS += --gc-sections -T
# since 4.19
KBUILD_LDFLAGS += --gc-sections -T

subdir-y := lib/$(SRCARCH) demos/$(SRCARCH) tests/$(SRCARCH) tools/$(SRCARCH)

# demos, tests and tools depend on the library
$(obj)/demos/$(SRCARCH) $(obj)/tests/$(SRCARCH) $(obj)/tools/$(SRCARCH): \
	$(obj)/lib/$(SRCARCH)
