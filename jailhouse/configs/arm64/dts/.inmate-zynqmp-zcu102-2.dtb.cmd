cmd_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/inmate-zynqmp-zcu102-2.dtb := mkdir -p /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/ ; gcc -E -Wp,-MD,/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/.inmate-zynqmp-zcu102-2.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/.inmate-zynqmp-zcu102-2.dtb.dts.tmp /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/inmate-zynqmp-zcu102-2.dts ; ./scripts/dtc/dtc -O dtb -o /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/inmate-zynqmp-zcu102-2.dtb -b 0 -i/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/ -i./scripts/dtc/include-prefixes -Wno-unit_address_vs_reg -Wno-unit_address_format -Wno-gpios_property -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address -Wno-pci_device_reg  -d /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/.inmate-zynqmp-zcu102-2.dtb.d.dtc.tmp /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/.inmate-zynqmp-zcu102-2.dtb.dts.tmp ; cat /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/.inmate-zynqmp-zcu102-2.dtb.d.pre.tmp /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/.inmate-zynqmp-zcu102-2.dtb.d.dtc.tmp > /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/.inmate-zynqmp-zcu102-2.dtb.d

source_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/inmate-zynqmp-zcu102-2.dtb := /home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/inmate-zynqmp-zcu102-2.dts

deps_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/inmate-zynqmp-zcu102-2.dtb := \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \

/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/inmate-zynqmp-zcu102-2.dtb: $(deps_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/inmate-zynqmp-zcu102-2.dtb)

$(deps_/home/ubuntu/ZYC_RtOs/jailhouse/configs/arm64/dts/inmate-zynqmp-zcu102-2.dtb):
