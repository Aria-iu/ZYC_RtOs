cmd_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/caches.o := gcc -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/.caches.o.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/generated -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include/arch/arm64 -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/../include -I/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm-common/include -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT=3 -D__ASSEMBLY__ -fno-PIE    -c -o /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/caches.o /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/caches.S

source_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/caches.o := /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/caches.S

deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/caches.o := \
  /home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/include/generated/asm/asm-defines.h \

/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/caches.o: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/caches.o)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/hypervisor/arch/arm64/caches.o):
