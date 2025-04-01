#
# Jailhouse AArch64 support
#
# Copyright (C) 2015 Huawei Technologies Duesseldorf GmbH
#
# Authors:
#  Antonios Motakis <antonios.motakis@huawei.com>
#
# This work is licensed under the terms of the GNU GPL, version 2.  See
# the COPYING file in the top-level directory.
#

include $(INMATES_LIB)/Makefile.lib

INMATES := gic-demo.bin uart-demo.bin ivshmem-demo.bin mem-init-demo.bin mem-init-demo1.bin mem-alloc-demo1.bin mem-alloc-demo2.bin mem-alloc-demo3.bin  mem-free-demo1.bin task-init-test.bin task-init-test1.bin task-init-test2.bin irq_test1.bin

gic-demo-y	:= ../arm/gic-demo.o
uart-demo-y	:= ../arm/uart-demo.o
ivshmem-demo-y	:= ../ivshmem-demo.o
mem-init-demo-y := ../arm/mem-init-demo.o

mem-init-demo1-y := ../arm/mem-init-demo1.o

mem-alloc-demo1-y := ../arm/mem-alloc-demo1.o
mem-alloc-demo2-y := ../arm/mem-alloc-demo2.o
mem-alloc-demo3-y := ../arm/mem-alloc-demo3.o
mem-free-demo1-y := ../arm/mem-free-demo1.o


task-init-test-y := ../arm/task-init-test.o
task-init-test1-y := ../arm/task-init-test1.o
task-init-test2-y := ../arm/task-init-test2.o

irq_test1-y := ../arm/irq_test1.o
$(eval $(call DECLARE_TARGETS,$(INMATES)))
