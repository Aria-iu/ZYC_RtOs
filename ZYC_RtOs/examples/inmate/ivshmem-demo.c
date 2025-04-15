/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2014-2020
 *
 * Authors:
 *  Henning Schild <henning.schild@siemens.com>
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */
#include <inmate.h>
#include "shmem.h"

#define VENDORID			0x110a
#define DEVICEID			0x4106

#define BAR_BASE			0xff000000

#define IVSHMEM_CFG_STATE_TAB_SZ	0x04
#define IVSHMEM_CFG_RW_SECTION_SZ	0x08
#define IVSHMEM_CFG_OUT_SECTION_SZ	0x10
#define IVSHMEM_CFG_ADDRESS		0x18

#define JAILHOUSE_SHMEM_PROTO_UNDEFINED	0x0000

#if defined(__x86_64__)
#define DEFAULT_IRQ_BASE	32
#elif defined(__arm__) || defined(__aarch64__)
#define DEFAULT_IRQ_BASE	(comm_region->vpci_irq_base + 32)
#else
#error Not implemented!
#endif

#define MAX_VECTORS	4

static int irq_counter[MAX_VECTORS];
static struct ivshmem_dev_data dev;
static unsigned int irq_base, vectors;

struct ivshm_regs {
	u32 id;
	u32 max_peers;
	u32 int_control;
	u32 doorbell;
	u32 state;
};

struct ivshmem_dev_data {
	u16 bdf;
	struct ivshm_regs *registers;
	u32 *state_table;
	u32 state_table_sz;
	u32 *rw_section;
	u64 rw_section_sz;
	u32 *in_sections;
	u32 *out_section;
	u64 out_section_sz;
	u32 *msix_table;
	u32 id;
	int msix_cap;
};

static u64 pci_cfg_read64(u16 bdf, unsigned int addr)
{
	return pci_read_config(bdf, addr, 4) |
		((u64)pci_read_config(bdf, addr + 4, 4) << 32);
}

static void print_shmem(struct ivshmem_dev_data *d)
{
	printk("state[0] = %d\n", d->state_table[0]);
	printk("state[1] = %d\n", d->state_table[1]);
	printk("state[2] = %d\n", d->state_table[2]);
	printk("rw[0] = %d\n", d->rw_section[0]);
	printk("rw[1] = %d\n", d->rw_section[1]);
	printk("rw[2] = %d\n", d->rw_section[2]);
	printk("in@0x0000 = %d\n", d->in_sections[0/4]);
	printk("in@0x2000 = %d\n", d->in_sections[0x2000/4]);
	printk("in@0x4000 = %d\n", d->in_sections[0x4000/4]);
}

// 暂时实现 两个 inmate 都和 host 进行通信，两个 inmate之间暂时不进行直接通信
// inmate 每次得到中断，检查 host 发送的消息，验证是否是发送给自己的消息，然后做出回答。
// 消息处理函数
void handle_message(struct ivshmem_dev_data *d, struct Message *msg) {
	switch (msg->type) {
		case MSG_TYPE_TEXT:
			handle_text_message(d, msg);
		break;
		case MSG_TYPE_COMMAND:

		break;
		case MSG_TYPE_ACK:

		break;
		case MSG_TYPE_ERROR:

		break;
		default:
			printk("IVSHMEM: Unknown message type %d\n", msg->type);
		break;
	}
}

// 文本消息处理函数
void handle_text_message(struct ivshmem_dev_data *d, struct Message *msg) {
	printk("IVSHMEM: Received text message from peer %d: data=%s\n", msg->sender_id, msg->data);

	// 准备响应消息
	struct Message response;
	construct_message(&response, MSG_TYPE_TEXT, d->id, msg->sender_id, "Text message received");

	// 发送响应
	send_message(d, &response);
}

// 消息发送函数
void send_message(struct ivshmem_dev_data *d, struct Message *msg) {
	// 将消息写入自己的独占输出区域
	memcpy((void *)(d->out_section+0x2000), msg, sizeof(struct Message));
	send_irq(&dev);
}

static void irq_handler(unsigned int irq)
{
	unsigned int n;
	u32 value;

	if (irq < irq_base || irq >= irq_base + vectors)
		return;

	n = irq - irq_base;
	irq_counter[n]++;
	if (dev.msix_cap > 0)
		value = irq_counter[dev.id];
	else
		value = irq_counter[0];
	printk("dev.id is %d\n",dev.id);
	dev.rw_section[dev.id] = value;
	// dev.out_section[0] = 114514;

	printk("\nIVSHMEM: got interrupt %d (#%d)\n", n, irq_counter[n]);

	// 读取来自 host 的消息 , 解析为 Message 结构体
	// printk("Get message from Host: %s \n",dev.in_sections);
	struct Message msg;
	memcpy(&msg, dev.in_sections, sizeof(struct Message));
    if handle_message(&dev, &msg){
     	return;
    }
	// print_shmem(&dev);
}

static void init_device(struct ivshmem_dev_data *d)
{
	unsigned long baseaddr, addr, size;
	int vndr_cap, n;
	u32 max_peers;

	vndr_cap = pci_find_cap(d->bdf, PCI_CAP_VENDOR);
	if (vndr_cap < 0) {
		printk("IVSHMEM ERROR: missing vendor capability\n");
		stop();
	}

	d->registers = (struct ivshm_regs *)BAR_BASE;
	pci_write_config(d->bdf, PCI_CFG_BAR, (unsigned long)d->registers, 4);
	printk("IVSHMEM: bar0 is at %p\n", d->registers);

	d->msix_table = (u32 *)(BAR_BASE + PAGE_SIZE);
	pci_write_config(d->bdf, PCI_CFG_BAR + 4,
			 (unsigned long)d->msix_table, 4);
	printk("IVSHMEM: bar1 is at %p\n", d->msix_table);

	pci_write_config(d->bdf, PCI_CFG_COMMAND,
			 (PCI_CMD_MEM | PCI_CMD_MASTER), 2);

	map_range((void *)BAR_BASE, 2 * PAGE_SIZE, MAP_UNCACHED);

	d->id = mmio_read32(&d->registers->id);
	printk("IVSHMEM: ID is %d\n", d->id);

	max_peers = mmio_read32(&d->registers->max_peers);
	printk("IVSHMEM: max. peers is %d\n", max_peers);

	d->state_table_sz =
		pci_read_config(d->bdf, vndr_cap + IVSHMEM_CFG_STATE_TAB_SZ, 4);
	d->rw_section_sz =
		pci_cfg_read64(d->bdf, vndr_cap + IVSHMEM_CFG_RW_SECTION_SZ);
	d->out_section_sz =
		pci_cfg_read64(d->bdf, vndr_cap + IVSHMEM_CFG_OUT_SECTION_SZ);
	baseaddr = pci_cfg_read64(d->bdf, vndr_cap + IVSHMEM_CFG_ADDRESS);

	addr = baseaddr;
	d->state_table = (u32 *)addr;

	addr += d->state_table_sz;
	d->rw_section = (u32 *)addr;

	addr += d->rw_section_sz;
	d->in_sections = (u32 *)addr;

	addr += d->id * d->out_section_sz;
	d->out_section = (u32 *)addr;

	printk("IVSHMEM: state table is at %p\n", d->state_table);
	printk("IVSHMEM: R/W section is at %p\n", d->rw_section);
	printk("IVSHMEM: input sections start at %p\n", d->in_sections);
	printk("IVSHMEM: output section is at %p\n", d->out_section);

	size = d->state_table_sz + d->rw_section_sz +
		max_peers * d->out_section_sz;
	map_range((void *)baseaddr, size, MAP_CACHED);

	d->msix_cap = pci_find_cap(d->bdf, PCI_CAP_MSIX);
	vectors = d->msix_cap > 0 ? MAX_VECTORS : 1;
	for (n = 0; n < vectors; n++) {
		if (d->msix_cap > 0)
			pci_msix_set_vector(d->bdf, irq_base + n, n);
		irq_enable(irq_base + n);
	}
}

static void send_irq(struct ivshmem_dev_data *d)
{
	u32 int_no = d->msix_cap > 0 ? (d->id + 1) : 0;
//	u32 target = d->id < 2 ? (d->id + 1) : 0;
	u32 target = 0;

	disable_irqs();
	printk("\nIVSHMEM: sending IRQ %d to peer %d\n", int_no, target);
	enable_irqs();
	mmio_write32(&d->registers->doorbell, int_no | (target << 16));
}

void inmate_main(void)
{
	unsigned int class_rev;
	int bdf;
	char * message = "hELLO FROM InATE!\n";
	irq_base = cmdline_parse_int("irq_base", DEFAULT_IRQ_BASE);

	irq_init(irq_handler);
	pci_init();

	bdf = pci_find_device(VENDORID, DEVICEID, 0);
	if (bdf == -1) {
		printk("IVSHMEM: No PCI devices found .. nothing to do.\n");
		stop();
	}

	printk("IVSHMEM: Found device at %02x:%02x.%x\n",
	       bdf >> 8, (bdf >> 3) & 0x1f, bdf & 0x3);
	class_rev = pci_read_config(bdf, 0x8, 4);
	if (class_rev != (PCI_DEV_CLASS_OTHER << 24 |
	    JAILHOUSE_SHMEM_PROTO_UNDEFINED << 8)) {
		printk("IVSHMEM: class/revision %08x, not supported\n",
		       class_rev);
		stop();
	}

	dev.bdf = bdf;
	init_device(&dev);
	printk("IVSHMEM: initialized device\n");

	mmio_write32(&dev.registers->int_control, 1);

	mmio_write32(&dev.registers->state, dev.id + 1);
	dev.rw_section[dev.id] = 0;
	dev.out_section[0] = 0;
//	memcpy((void* )dev.out_section,message,19);
//	memcpy((void* )dev.rw_section,message,19);
//	printk("IVSHMEM: Sent message to host\n");
	print_shmem(&dev);
	send_irq(&dev);
	enable_irqs();

	while (1) {
		delay_us(1000*1000);
		send_irq(&dev);
	}
}
