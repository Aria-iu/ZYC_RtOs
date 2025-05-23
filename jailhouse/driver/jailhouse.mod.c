#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xdc2d8263, "module_layout" },
	{ 0x7cb1ae69, "cpu_down" },
	{ 0xe88560c6, "kobject_put" },
	{ 0x1ba7c500, "physvirt_offset" },
	{ 0x85bd1608, "__request_region" },
	{ 0x281f57b7, "kmalloc_caches" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x1fdc7df2, "_mcount" },
	{ 0x8cb7f2fb, "of_find_matching_node_and_match" },
	{ 0x4c8c3496, "sysfs_remove_bin_file" },
	{ 0x3c2b68f7, "of_changeset_apply" },
	{ 0x301fa007, "_raw_spin_unlock" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x24875537, "of_find_node_opts_by_path" },
	{ 0xc56a41e6, "vabits_actual" },
	{ 0x77358855, "iomem_resource" },
	{ 0x151f4898, "schedule_timeout_uninterruptible" },
	{ 0x4344c407, "device_release_driver" },
	{ 0x696f2b63, "of_changeset_init" },
	{ 0x84a8d0eb, "of_changeset_revert" },
	{ 0x6b7d4193, "pci_stop_and_remove_bus_device_locked" },
	{ 0xfe165538, "pci_get_slot" },
	{ 0xbcea4360, "pci_add_dynid" },
	{ 0xb5a5d8f1, "kobject_uevent" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x56470118, "__warn_printk" },
	{ 0x5790e7a0, "pci_unlock_rescan_remove" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0x999e8297, "vfree" },
	{ 0x33fe844, "pci_bus_assign_resources" },
	{ 0xb4ea7cf7, "kgdb_connected" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x30c52959, "sysfs_remove_group" },
	{ 0x2d39b0a7, "kstrdup" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x51f673a9, "kobject_create_and_add" },
	{ 0x3feea40, "cpumask_next" },
	{ 0x17de3d5, "nr_cpu_ids" },
	{ 0xbd4b08ad, "misc_register" },
	{ 0x35204337, "_dev_warn" },
	{ 0xdcb764ad, "memset" },
	{ 0x706c5a65, "preempt_count_sub" },
	{ 0x75dd4ebe, "of_overlay_remove" },
	{ 0x5610897, "of_changeset_destroy" },
	{ 0xb5136dc7, "mutex_lock_interruptible" },
	{ 0xc5850110, "printk" },
	{ 0x7b353f4f, "sysfs_create_group" },
	{ 0x5e3240a0, "__cpu_online_mask" },
	{ 0xc917e655, "debug_smp_processor_id" },
	{ 0x7c472226, "kobject_init_and_add" },
	{ 0x56d697ce, "cpu_up" },
	{ 0xd61eeee, "__bitmap_subset" },
	{ 0x65e0d6d7, "memory_read_from_buffer" },
	{ 0xcee88e7a, "of_overlay_fdt_apply" },
	{ 0xe4bbc1dd, "kimage_voffset" },
	{ 0x9e38fdbf, "pci_get_domain_bus_and_slot" },
	{ 0xc37836cf, "pci_bus_add_devices" },
	{ 0x4a550cb2, "of_changeset_action" },
	{ 0xebce599f, "noop_llseek" },
	{ 0x2bf62a88, "kobj_sysfs_ops" },
	{ 0xc58150f6, "pci_find_bus" },
	{ 0x952be1ab, "__root_device_register" },
	{ 0xe007de41, "kallsyms_lookup_name" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x6b4b2933, "__ioremap" },
	{ 0xe2e0c7c6, "__flush_icache_range" },
	{ 0x50e4d1fb, "pci_scan_slot" },
	{ 0x45451d31, "kobject_move" },
	{ 0xac1a55be, "unregister_reboot_notifier" },
	{ 0x42d6a784, "module_put" },
	{ 0x58afd679, "_dev_info" },
	{ 0x7699c76b, "root_device_unregister" },
	{ 0x3517383e, "register_reboot_notifier" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xb342df7a, "cpu_hwcaps" },
	{ 0x1333db27, "cpu_hwcap_keys" },
	{ 0x1035c7c2, "__release_region" },
	{ 0x2f98c181, "pci_unregister_driver" },
	{ 0xa429d888, "kmem_cache_alloc_trace" },
	{ 0xdbf17652, "_raw_spin_lock" },
	{ 0xddbeeecc, "pci_lock_rescan_remove" },
	{ 0x970c1bc3, "__get_vm_area" },
	{ 0x39b52d19, "__bitmap_and" },
	{ 0x37a0cba, "kfree" },
	{ 0x94961283, "vunmap" },
	{ 0x4829a47e, "memcpy" },
	{ 0xedc03953, "iounmap" },
	{ 0xd5750cdd, "sysfs_create_bin_file" },
	{ 0xeff2211e, "__pci_register_driver" },
	{ 0x96848186, "scnprintf" },
	{ 0x86fceaae, "request_firmware" },
	{ 0x63c4d61f, "__bitmap_weight" },
	{ 0x66fa4f79, "pci_dev_put" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xc60d0620, "__num_online_cpus" },
	{ 0x4df9f3f5, "of_property_read_variable_u32_array" },
	{ 0xf229424a, "preempt_count_add" },
	{ 0x294b9ea1, "on_each_cpu" },
	{ 0x6b107a85, "of_node_put" },
	{ 0x14b89635, "arm64_const_caps_ready" },
	{ 0xa6e1a69d, "kick_all_cpus_sync" },
	{ 0xf855a659, "misc_deregister" },
	{ 0x4f072cf1, "release_firmware" },
	{ 0x2ec4bf02, "try_module_get" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "353B9E06883C120F8E43910");
