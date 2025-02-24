.PHONY: clean all

src = $(CURDIR)

# 使用arm交叉编译器。
# CROSS_COMPILE ?= arm-linux-gnueabihf-
CROSS_COMPILE ?= aarch64-linux-gnu-
# gcc ld ar和objcopy
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar
OBJCOPY = $(CROSS_COMPILE)objcopy

# CFLAGS += -mcpu=cortex-a7 -mtune=cortex-a7 -mfpu=vfpv4-d16 -mfloat-abi=hard -O2
# CFLAGS += -DCONFIG_MACH_SUN7I=1
# CFLAGS += -Wall -MMD -pipe
CFLAGS += -march=armv8-a+nosimd+nofp
CFLAGS += -ffreestanding -MMD -pipe -Wall -Wextra -Wfatal-errors -Werror -Wno-psabi -O2 -g3 -D__LITTLE_ENDIAN
ASMFLAGS += -march=armv8-a+nosimd+nofp
ASMFLAGS += -ffreestanding -Wextra -Wfatal-errors -Werror -O2 -g3 -D__ASSEMBLY__
# 头文件位置：
# 	1. /
#	2. /freertos/Source/include
#	3. /freertos-runtime
#	4. /freertos/Source/portable/GCC/ARM_A7jailhouse
# CFLAGS += -I $(src) -I $(src)/freertos/Source/include -I $(src)/freertos-runtime -I $(src)/freertos/Source/portable/GCC/ARM_A7jailhouse
CFLAGS += -I $(src)

# 链接脚本
LDFLAGS += -T lscript.lds -Map=cell.map -nostdlib

# 命名。
EXE_STEM = freertos-demo

# 需要编译的源文件。
#FREERTOS_OBJS = freertos/Source/queue.o \
#	freertos/Source/list.o \
#	freertos/Source/croutine.o \
#	freertos/Source/event_groups.o \
#	freertos/Source/portable/MemMang/heap_1.o \
#	freertos/Source/portable/GCC/ARM_A7jailhouse/port.o \
#	freertos/Source/portable/GCC/ARM_A7jailhouse/gic-v2.o \
#	freertos/Source/portable/GCC/ARM_A7jailhouse/portASM.o \
#	freertos/Source/timers.o \
#	freertos/Source/tasks.o

# runtime文件夹下的源文件
#FREERTOS_RUNTIME_OBJS = freertos-runtime/string.o \
#	freertos-runtime/serial.o \
#	freertos-runtime/printf-stdarg.o \
#	freertos-runtime/lib1funcs.o

# 合并源文件目标
# RUNTIME_OBJS = $(FREERTOS_RUNTIME_OBJS) $(FREERTOS_OBJS)
OBJS = main.o boot_stub.o

RUNTIME_AR = libfreertos.a

all: $(EXE_STEM).bin

DEPS := $(OBJS:.o=.d) $(RUNTIME_OBJS:.o=.d)

# elf文件依赖于 main.o boot_stub.o、libfreertos.a、以及链接脚本。
$(EXE_STEM).elf: $(OBJS) #$(RUNTIME_AR)
	$(LD) $(LDFLAGS) -o $@ $^

# libfreertos.a依赖于源文件目标包括 $(FREERTOS_RUNTIME_OBJS) $(FREERTOS_OBJS)
#$(RUNTIME_AR): $(RUNTIME_OBJS)
#	$(AR) -srcv $@ $^

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OBJS) $(EXE_STEM).elf $(EXE_STEM).bin $(RUNTIME_OBJS) $(RUNTIME_AR)

distclean: clean
	rm -f $(DEPS)

-include $(DEPS)
