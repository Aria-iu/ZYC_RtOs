cmd_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/timing.o := gcc -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/.timing.o.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64 -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../include/arch/arm64 -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/log -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/mem -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/mem/fsc -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/core/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/include/armv8 -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/include/armv8 	 -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../hypervisor/arch/arm-common/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/include -include ./include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT=3 -g -Os -Wall -Wstrict-prototypes -Wtype-limits -Wmissing-declarations -Wmissing-prototypes -fno-strict-aliasing -fomit-frame-pointer -fno-pic -fno-common -fno-stack-protector -ffreestanding -ffunction-sections -D__LINUX_COMPILER_TYPES_H    -DKBUILD_BASENAME='"timing"' -DKBUILD_MODNAME='"timing"' -c -o /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/timing.o /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/timing.c

source_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/timing.o := /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/timing.c

deps_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/timing.o := \
  include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/include/asm/sysregs.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/include/string.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/include/asm/sysregs_common.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/include/inmate.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/include/asm/processor.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/include/arch/inmate.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/include/inmate_common.h \
    $(wildcard include/config/inmate/base.h) \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/../include/jailhouse/hypercall.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/../include/jailhouse/console.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/../include/arch/arm64/asm/jailhouse_hypercall.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/../include/arch/arm64/../arm-common/asm/jailhouse_hypercall.h \

/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/timing.o: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/timing.o)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/timing.o):
