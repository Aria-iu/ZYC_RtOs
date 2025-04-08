cmd_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/entry.o := gcc -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/.entry.o.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/generated -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/arch/arm64 -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT=3 -D__ASSEMBLY__ -fno-PIE    -c -o /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/entry.o /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/entry.S

source_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/entry.o := /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/entry.S

deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/entry.o := \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/generated/asm/asm-defines.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/paging.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/utils.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/dcaches.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/processor.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/sysregs.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/smccc.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/arch/arm64/asm/jailhouse_hypercall.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/arch/arm64/../arm-common/asm/jailhouse_hypercall.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/header.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/jailhouse_header.h \

/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/entry.o: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/entry.o)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/entry.o):
