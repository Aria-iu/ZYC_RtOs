cmd_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/hikey-inmate-demo.o := gcc -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/.hikey-inmate-demo.o.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/home/ubuntu/ZYC_RtOs/jailhouse/configs/../hypervisor/arch/arm64/include -I/home/ubuntu/ZYC_RtOs/jailhouse/configs/../hypervisor/include -I/home/ubuntu/ZYC_RtOs/jailhouse/configs/../include -include ./include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT=3 -Wextra -D__LINUX_COMPILER_TYPES_H    -DKBUILD_BASENAME='"hikey_inmate_demo"' -DKBUILD_MODNAME='"hikey_inmate_demo"' -c -o /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/hikey-inmate-demo.o /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/hikey-inmate-demo.c

source_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/hikey-inmate-demo.o := /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/hikey-inmate-demo.c

deps_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/hikey-inmate-demo.o := \
  include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  /home/ubuntu/ZYC_RtOs/jailhouse/configs/../hypervisor/include/jailhouse/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/configs/../hypervisor/arch/arm64/include/asm/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/configs/../include/jailhouse/cell-config.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/configs/../include/jailhouse/console.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/configs/../include/jailhouse/pci_defs.h \

/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/hikey-inmate-demo.o: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/hikey-inmate-demo.o)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/hikey-inmate-demo.o):
