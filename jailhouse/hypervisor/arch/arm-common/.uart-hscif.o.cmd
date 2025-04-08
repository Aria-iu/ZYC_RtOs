cmd_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/uart-hscif.o := gcc -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/.uart-hscif.o.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/generated -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/arch/arm64 -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include -include ./include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT=3 -g -Os -Wall -Wstrict-prototypes -Wtype-limits -Wmissing-declarations -Wmissing-prototypes -fno-strict-aliasing -fno-pic -fno-common -fno-stack-protector -fno-builtin-ffsl -D__LINUX_COMPILER_TYPES_H    -DKBUILD_BASENAME='"uart_hscif"' -DKBUILD_MODNAME='"uart_hscif"' -c -o /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/uart-hscif.o /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/uart-hscif.c

source_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/uart-hscif.o := /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/uart-hscif.c

deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/uart-hscif.o := \
  include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/mmio.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/mmio.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/jailhouse/cell-config.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/jailhouse/console.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/jailhouse/pci_defs.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/processor.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/processor.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/utils.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/uart.h \

/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/uart-hscif.o: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/uart-hscif.o)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/uart-hscif.o):
