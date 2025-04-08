cmd_/home/ubuntu/ZYC_RtOs/jailhouse/driver/vpci_template.dtb.o := gcc -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/driver/.vpci_template.dtb.o.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I./arch/arm64/include -I./arch/arm64/include/generated  -I./include -I./arch/arm64/include/uapi -I./arch/arm64/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT=3 -D__ASSEMBLY__ -fno-PIE -DCONFIG_AS_LSE=1 -mabi=lp64 -DKASAN_SHADOW_SCALE_SHIFT=3  -DMODULE  -c -o /home/ubuntu/ZYC_RtOs/jailhouse/driver/vpci_template.dtb.o /home/ubuntu/ZYC_RtOs/jailhouse/driver/vpci_template.dtb.S

source_/home/ubuntu/ZYC_RtOs/jailhouse/driver/vpci_template.dtb.o := /home/ubuntu/ZYC_RtOs/jailhouse/driver/vpci_template.dtb.S

deps_/home/ubuntu/ZYC_RtOs/jailhouse/driver/vpci_template.dtb.o := \
  include/linux/kconfig.h \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  include/asm-generic/vmlinux.lds.h \
    $(wildcard include/config/ld/dead/code/data/elimination.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/kprobes.h) \
    $(wildcard include/config/function/error/injection.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/syscalls.h) \
    $(wildcard include/config/bpf/events.h) \
    $(wildcard include/config/serial/earlycon.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/timer/of.h) \
    $(wildcard include/config/irqchip.h) \
    $(wildcard include/config/common/clk.h) \
    $(wildcard include/config/of/reserved/mem.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/idle.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/thermal.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/unwinder/orc.h) \
    $(wildcard include/config/pm/trace.h) \
    $(wildcard include/config/blk/dev/initrd.h) \
    $(wildcard include/config/amd/mem/encrypt.h) \

/home/ubuntu/ZYC_RtOs/jailhouse/driver/vpci_template.dtb.o: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/driver/vpci_template.dtb.o)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/driver/vpci_template.dtb.o):
