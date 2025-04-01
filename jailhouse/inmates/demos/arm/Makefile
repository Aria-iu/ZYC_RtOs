#
# Jailhouse, a Linux-based partitioning hypervisor
#
# Copyright (c) ARM Limited, 2014
#
# Authors:
#  Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
#
# This work is licensed under the terms of the GNU GPL, version 2.  See
# the COPYING file in the top-level directory.
#

include $(INMATES_LIB)/Makefile.lib

INMATES := gic-demo.bin uart-demo.bin ivshmem-demo.bin

gic-demo-y	:= gic-demo.o
uart-demo-y	:= uart-demo.o
ivshmem-demo-y	:= ../ivshmem-demo.o
mem-init-demo-y := mem-init-demo.o

mem-init-demo1-y := mem-init-demo1.o

mem-alloc-demo1-y := mem-alloc-demo1.o
mem-alloc-demo2-y := mem-alloc-demo2.o
mem-alloc-demo3-y := mem-alloc-demo3.o
mem-free-demo1-y := mem-free-demo1.o


task-init-test-y := task-init-test.o
task-init-test1-y := task-init-test1.o
task-init-test2-y := task-init-test2.o

irq_test1-y := irq_test1.o
$(eval $(call DECLARE_TARGETS,$(INMATES)))
