# 多个核心启动 ZYC_RtOs
重新编写配置文件，在两个 CPU 上分别启动 ZYC_RtOs 。

rpi4-inmate-moremem1.c 如下，使用编号为 1 的 CPU。名称为 inmate-demo-1。
RAM 分配部分为 0x30000000 - 0x30100000 的物理内存。
```c
struct {
	// ... ...
} __attribute__((packed)) config = {
	.cell = {
	//  ... ...
		.name = "inmate-demo-1",
	//  ... ...
	},

	.cpus = {
		0b0010,
	},

	.mem_regions = {
		/* IVSHMEM shared memory regions (demo) */
		// IVSHMEM 内存部分
		/* UART */ {
			.phys_start = 0xfe215040,
			.virt_start = 0xfe215040,
			.size = 0x40,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO | JAILHOUSE_MEM_IO_8 |
				JAILHOUSE_MEM_IO_32 | JAILHOUSE_MEM_ROOTSHARED,
		},
		/* RAM */ {
			.phys_start = 0x30000000,
			.virt_start = 0,
			.size = 0x00100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE,
		},
		/* communication region */ {
			.virt_start = 0x80000000,
			.size = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_COMM_REGION,
		},
	},

	.irqchips = {
		/* GIC */ {
			.address = 0xff841000,
			.pin_base = 160,
			.pin_bitmap = {
				1 << (184 - 160),
				0,
				0,
				0
			},
		},
	},

	.pci_devices = {
		// pci 设备
	},
};

```

rpi4-inmate-moremem2.c 如下，使用编号为 0 的 CPU。名称为 inmate-demo-2。
RAM 分配部分为 0x30200000 - 0x30300000 的物理内存。
```c
struct {
	// ... ...
} __attribute__((packed)) config = {
	.cell = {
		// ... ...
		.name = "inmate-demo-2",
		// ... ...
	},

	.cpus = {
		0b0001,
	},

	.mem_regions = {
		/* IVSHMEM shared memory regions (demo) */
		// IVSHMEM 部分，省略。
		/* UART */ {
			.phys_start = 0xfe215040,
			.virt_start = 0xfe215040,
			.size = 0x40,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO | JAILHOUSE_MEM_IO_8 |
				JAILHOUSE_MEM_IO_32 | JAILHOUSE_MEM_ROOTSHARED,
		},
		/* RAM */ {
			.phys_start = 0x30200000,
			.virt_start = 0,
			.size = 0x00100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE,
		},
		/* communication region */ {
			.virt_start = 0x80000000,
			.size = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_COMM_REGION,
		},
	},

	.irqchips = {
		/* GIC */ {
			.address = 0xff841000,
			.pin_base = 160,
			.pin_bitmap = {
				1 << (184 - 160),
				0,
				0,
				0
			},
		},
	},

	.pci_devices = {
		// pci 设备部分
	},
};

```

## 编写脚本启动：
```shell
#!/bin/sh
sudo jailhouse cell create /home/ubuntu/jailhouse/configs/arm64/rpi4-inmate-moremem1.cell
sudo jailhouse cell load inmate-demo-1  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/demos/arm64/task-init-test2.bin 
sudo jailhouse cell start inmate-demo-1

sudo jailhouse cell create /home/ubuntu/jailhouse/configs/arm64/rpi4-inmate-moremem2.cell
sudo jailhouse cell load inmate-demo-2  /home/ubuntu/ZYC_RtOs/jailhouse/inmates/demos/arm64/task-init-test2.bin 
sudo jailhouse cell start inmate-demo-2
```

## 测试结果：
```
ubuntu@ubuntu:~/jailhouse$ sudo ./build_rpi4_moremem1.sh 
ubuntu@ubuntu:~/jailhouse$ sudo ./build_rpi4_moremem2.sh 
ubuntu@ubuntu:~/jailhouse$ sudo jailhouse cell list 
ID      Name                    State             Assigned CPUs           Failed CPUs             
0       Raspberry-Pi4           running           2-3                                             
1       inmate-demo-1           running           1                                               
2       inmate-demo-2           running           0  
```
串口输出为：
```
Initializing Jailhouse hypervisor v0.12 (0-g92db71f2) on CPU 1
Code location: 0x0000ffffc0200800
Page pool usage after early setup: mem 39/994, remap 0/131072
Initializing processors:
 CPU 1... OK
 CPU 3... OK
 CPU 2... OK
 CPU 0... OK
Initializing unit: irqchip
Initializing unit: ARM SMMU v3
Initializing unit: PVU IOMMU
Initializing unit: PCI
Adding virtual PCI device 00:00.0 to cell "Raspberry-Pi4"
Adding virtual PCI device 00:01.0 to cell "Raspberry-Pi4"
Page pool usage after late setup: mem 61/994, remap 5/131072
Activating hypervisor
Adding virtual PCI device 00:00.0 to cell "inmate-demo-1"
Shared memory connection established, peer cells:
 "Raspberry-Pi4"
Created cell "inmate-demo-1"
Page pool usage after cell creation: mem 76/994, remap 5/131072
Cell "inmate-demo-1" can be loaded
Started cell "inmate-demo-1"
[ZYC_RtOs : INFO] : System alloc mem : begin 2590 , end 12590
[ZYC_RtOs : INFO] : task init begin
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2590
[ZYC_RtOs : INFO] : OS_MAX_TCB_NUM = 5
[ZYC_RtOs : INFO] : sizeof TagTskCb is 88
[ZYC_RtOs : INFO] : g_tskCbArray 's address is 122c0
[ZYC_RtOs : INFO] : task init end
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x2d8
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x2d8
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2590
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[1]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[1].node 			is 170a8
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].taskPid 			is 2
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[1].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[2]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[2].node 			is 12348
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].taskPid 			is 3
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[2].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[3]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[3].node 			is 123d0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].taskPid 			is 4
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[3].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbFreeList's next is 12348
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next is 123d0
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next next is 12458
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev is 12458
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev is 123d0
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev prev is 12348
[ZYC_RtOs : INFO] : g_testTskHandle is 2
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[1]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[1].node 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackPointer 	is 12168
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackSize 		is 200
[ZYC_RtOs : INFO] : g_tskCbArray[1].taskPid 			is 2
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackCfgFlg 			is 1
[ZYC_RtOs : INFO] : g_tskCbArray[1].priority 			is 25
[ZYC_RtOs : INFO] : g_tskCbArray[1].topOfStack 			is 0x12090
[ZYC_RtOs : INFO] : g_tskCbArray[1].name 			is TestTask
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[2]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[2].node 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackPointer 	is 11f38
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackSize 		is 200
[ZYC_RtOs : INFO] : g_tskCbArray[2].taskPid 			is 3
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackCfgFlg 			is 1
[ZYC_RtOs : INFO] : g_tskCbArray[2].priority 			is 20
[ZYC_RtOs : INFO] : g_tskCbArray[2].topOfStack 			is 0x11e60
[ZYC_RtOs : INFO] : g_tskCbArray[2].name 			is TestTask2
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[3]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[3].node 			is 170a8
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].taskPid 			is 4
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[3].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : Now We want to sche
[ZYC_RtOs : INFO] : find index is 1
[ZYC_RtOs : INFO] : g_running_task_idx is 1
[ZYC_RtOs : INFO] : let's go to task
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer is 0x12168
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer->x30 is 0x14008
[ZYC_RtOs : INFO] : This is task1 test's entry!!!
[ZYC_RtOs : INFO] : How is that run ???
[ZYC_RtOs : INFO] : find index is 2
[ZYC_RtOs : INFO] : g_running_task_idx is 2
[ZYC_RtOs : INFO] : let's go to task
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer is 0x11f38
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer->x30 is 0x14040
[ZYC_RtOs : INFO] : This is task2 test's entry!!!
[ZYC_RtOs : INFO] : How is that run ???
[ZYC_RtOs : INFO] : no more tasks in system , haltAdding virtual PCI device 00:00.0 to cell "inmate-demo-2"
Shared memory connection established, peer cells:
 "Raspberry-Pi4"
 "inmate-demo-1"
Created cell "inmate-demo-2"
Page pool usage after cell creation: mem 91/994, remap 5/131072
Cell "inmate-demo-2" can be loaded
Started cell "inmate-demo-2"
[ZYC_RtOs : INFO] : System alloc mem : begin 2590 , end 12590
[ZYC_RtOs : INFO] : task init begin
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x0
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2590
[ZYC_RtOs : INFO] : OS_MAX_TCB_NUM = 5
[ZYC_RtOs : INFO] : sizeof TagTskCb is 88
[ZYC_RtOs : INFO] : g_tskCbArray 's address is 122c0
[ZYC_RtOs : INFO] : task init end
[ZYC_RtOs : INFO] : fsc : g_fscMemBitMap is 0x10001
[ZYC_RtOs : INFO] : fsc : g_memTotalSize is 0xffe0
[ZYC_RtOs : INFO] : fsc : g_memUsage is 0x2d8
[ZYC_RtOs : INFO] : fsc : g_memPeakUsage is 0x2d8
[ZYC_RtOs : INFO] : fsc : g_memStartAddr is 0x2590
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[1]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[1].node 			is 170a8
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].taskPid 			is 2
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[1].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[2]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[2].node 			is 12348
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].taskPid 			is 3
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[2].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[3]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[3].node 			is 123d0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].taskPid 			is 4
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[3].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbFreeList's next is 12348
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next is 123d0
[ZYC_RtOs : INFO] : g_tskCbFreeList's next next next is 12458
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev is 12458
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev is 123d0
[ZYC_RtOs : INFO] : g_tskCbFreeList's prev prev prev is 12348
[ZYC_RtOs : INFO] : g_testTskHandle is 2
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[1]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[1].node 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackPointer 	is 12168
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackSize 		is 200
[ZYC_RtOs : INFO] : g_tskCbArray[1].taskPid 			is 2
[ZYC_RtOs : INFO] : g_tskCbArray[1].stackCfgFlg 			is 1
[ZYC_RtOs : INFO] : g_tskCbArray[1].priority 			is 25
[ZYC_RtOs : INFO] : g_tskCbArray[1].topOfStack 			is 0x12090
[ZYC_RtOs : INFO] : g_tskCbArray[1].name 			is TestTask
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[2]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[2].node 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackPointer 	is 11f38
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackSize 		is 200
[ZYC_RtOs : INFO] : g_tskCbArray[2].taskPid 			is 3
[ZYC_RtOs : INFO] : g_tskCbArray[2].stackCfgFlg 			is 1
[ZYC_RtOs : INFO] : g_tskCbArray[2].priority 			is 20
[ZYC_RtOs : INFO] : g_tskCbArray[2].topOfStack 			is 0x11e60
[ZYC_RtOs : INFO] : g_tskCbArray[2].name 			is TestTask2
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : ----------------------------This is g_tskCbArray[3]------------------------------------------
[ZYC_RtOs : INFO] : g_tskCbArray[3].node 			is 170a8
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackPointer 	is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackSize 		is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].taskPid 			is 4
[ZYC_RtOs : INFO] : g_tskCbArray[3].stackCfgFlg 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].priority 			is 0
[ZYC_RtOs : INFO] : g_tskCbArray[3].topOfStack 			is 0x0
[ZYC_RtOs : INFO] : g_tskCbArray[3].name 			is 
[ZYC_RtOs : INFO] : ----------------------------------------------------------------------------------------
[ZYC_RtOs : INFO] : Now We want to sche
[ZYC_RtOs : INFO] : find index is 1
[ZYC_RtOs : INFO] : g_running_task_idx is 1
[ZYC_RtOs : INFO] : let's go to task
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer is 0x12168
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer->x30 is 0x14008
[ZYC_RtOs : INFO] : This is task1 test's entry!!!
[ZYC_RtOs : INFO] : How is that run ???
[ZYC_RtOs : INFO] : find index is 2
[ZYC_RtOs : INFO] : g_running_task_idx is 2
[ZYC_RtOs : INFO] : let's go to task
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer is 0x11f38
[ZYC_RtOs : INFO] : g_tskCbArray[g_running_task_idx].stackPointer->x30 is 0x14040
[ZYC_RtOs : INFO] : This is task2 test's entry!!!
[ZYC_RtOs : INFO] : How is that run ???
[ZYC_RtOs : INFO] : no more tasks in system , halt
```