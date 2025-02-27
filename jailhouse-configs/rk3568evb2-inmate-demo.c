// jailhouse-rk3568b2.c
#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
    struct jailhouse_cell_desc cell;
    __u64 cpus[1];
    struct jailhouse_memory mem_regions[13];
    struct jailhouse_irqchip irqchips[2];
    struct jailhouse_pci_device pci_devices[1];
} __attribute__((packed)) config = {
    .cell = {
        .signature = JAILHOUSE_CELL_DESC_SIGNATURE,
        .revision = JAILHOUSE_CONFIG_REVISION,
        .name = "rk3568b2-iname-demo",
        .flags = JAILHOUSE_CELL_PASSIVE_COMMREG,
        .architecture = JAILHOUSE_ARM64,

        .cpu_set_size = sizeof(config.cpus),
        .num_memory_regions = ARRAY_SIZE(config.mem_regions),
        .num_irqchips = ARRAY_SIZE(config.irqchips),
        .num_pci_devices = ARRAY_SIZE(config.pci_devices),

        // .vpci_irq_base = 128, // 虚拟PCI设备中断，根据GIC中断范围设置
	/*
        .console = {
			.address = 0xfe680000,
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_MMIO |
				 JAILHOUSE_CON_REGDIST_4,
		},
	*/
    },

    // CPU分配:核心3给Non-Root Cell
    // 1000
    .cpus = {
        0b1000, // 二进制1000，表示CPU3启用
    },

    .mem_regions = {
        /* 共享内存区域，用于network */
        // JAILHOUSE_SHMEM_NET_REGIONS(0x13000000, 1), //

        /* Non-Root Cell内存分配 RAM */ 
        {
            .phys_start = 0x13000000,        // 
            .virt_start = 0,
            .size = 0x1000000,              // 
            .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
                     JAILHOUSE_MEM_EXECUTE  | JAILHOUSE_MEM_LOADABLE,
        },
	
        //  UART0直通 (fe680000) 
        {
            .phys_start = 0xfe680000,
            .virt_start = 0xfe680000,
            .size = 0x100,
            .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
                     JAILHOUSE_MEM_IO | JAILHOUSE_MEM_ROOTSHARED,
        },
	
        /* GPIO控制器直通 
        {
            .phys_start = 0xfdd60000, // gpio0
            .virt_start = 0xfdd60000,
            .size = 0x100,
            .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
                     JAILHOUSE_MEM_IO,
        },
	*/
        /* GICD直通 
        {
            .phys_start = 0xfd400000,
            .virt_start = 0xfd400000,
            .size = 0x10000,
            .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
                     JAILHOUSE_MEM_IO,
        },
        */
    },

    .irqchips = {
        /* GICv3配置 
        {
            .address = 0xfd400000,
            .pin_base = 32,
            .pin_bitmap = {
                0,
                0,
                // 允许UART中断 (DTS中fe680000中断号0x78)
                1 << (0x78 - 96), // 计算实际中断号
                0
            },
        },
        {
            .address = 0xfd460000,
            .pin_base = 160,
            .pin_bitmap = {
                // 其他高优先级中断分配
            },
        },
        */
    },

    .pci_devices = {
        /* 现在不要pci设备，只要最简单的cpu + 内存 + 中断 + uart结构。
        {
            .type = JAILHOUSE_PCI_TYPE_IVSHMEM,
            .domain = 1,
            .bdf = 0 << 3,
            .bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_INTX,
            .shmem_regions_start = 0,
            .shmem_dev_id = 0,
            .shmem_peers = 2,
            .shmem_protocol = JAILHOUSE_SHMEM_PROTO_UNDEFINED,
        },
        */
    },
};