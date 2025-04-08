cmd_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/inmate.lds := gcc -E -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/.inmate.lds.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64 -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../include/arch/arm64 -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/log -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/mem -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/mem/fsc -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/core/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/include/armv8 -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../../ZYC_RtOs/include/armv8 	 -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/../hypervisor/arch/arm-common/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/include -I/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/../arm-common/include -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT=3     -P -Uarm64 -D__ASSEMBLY__ -DLINKER_SCRIPT -o /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/inmate.lds /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/inmate.lds.S

source_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/inmate.lds := /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/inmate.lds.S

deps_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/inmate.lds := \
    $(wildcard include/config/inmate/base.h) \
  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/include/inmate_common.h \

/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/inmate.lds: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/inmate.lds)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/inmates/lib/arm64/inmate.lds):
