cmd_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/dbg-write.o := gcc -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/.dbg-write.o.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/generated -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/arch/arm64 -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include -include ./include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT=3 -g -Os -Wall -Wstrict-prototypes -Wtype-limits -Wmissing-declarations -Wmissing-prototypes -fno-strict-aliasing -fno-pic -fno-common -fno-stack-protector -fno-builtin-ffsl -D__LINUX_COMPILER_TYPES_H    -DKBUILD_BASENAME='"dbg_write"' -DKBUILD_MODNAME='"dbg_write"' -c -o /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/dbg-write.o /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/dbg-write.c

source_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/dbg-write.o := /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/dbg-write.c

deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/dbg-write.o := \
  include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/control.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/bitops.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/percpu.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/cell.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/mmio.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/mmio.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/jailhouse/cell-config.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/jailhouse/console.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/jailhouse/pci_defs.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/paging.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/paging.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/utils.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/dcaches.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/processor.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/sysregs.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/string.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/entry.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/header.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/jailhouse_header.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/paging_modes.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/pci.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/cell.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/spinlock.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/jailhouse/hypercall.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/arch/arm64/asm/jailhouse_hypercall.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/arch/arm64/../arm-common/asm/jailhouse_hypercall.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/percpu.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/irqchip.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/percpu_fields.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/printk.h \
    $(wildcard include/config/trace/error.h) \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/uart.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/uart.h \

/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/dbg-write.o: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/dbg-write.o)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/../arm-common/dbg-write.o):
