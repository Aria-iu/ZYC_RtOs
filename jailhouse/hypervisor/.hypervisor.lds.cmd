cmd_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/hypervisor.lds := gcc -E -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/.hypervisor.lds.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/generated -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/arch/arm64 -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT=3     -P -Uarm64 -D__ASSEMBLY__ -DLINKER_SCRIPT -o /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/hypervisor.lds /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/hypervisor.lds.S

source_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/hypervisor.lds := /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/hypervisor.lds.S

deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/hypervisor.lds := \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/header.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/jailhouse_header.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/paging.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/types.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include/jailhouse/utils.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include/asm/dcaches.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/processor.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/sysregs.h \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/asm/sections.h \

/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/hypervisor.lds: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/hypervisor.lds)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/hypervisor.lds):
