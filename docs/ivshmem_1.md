## 共享内存通信模块
IVSHMEM（Inter-VM Shared Memory）协议是一种用于虚拟机间通信的机制，其核心原理在于通过共享内存区域和中断机制实现高效、灵活的数据交换。
管理程序负责创建和配置IVSHMEM设备实例，这些实例对虚拟机表现为PCI设备。

## ivshmem 协议
在 ivshmem 协议中，inmate 和 root cell 之间使用一段共享内存进行通信，共享内存区域被划分为状态表、公共读写区和独占输出区，其中状态表存储所有对等体的状态值，这段内存的结构如下：

公共读写区允许所有虚拟机进行数据交换，而独占输出区为每个虚拟机提供一个独占的写入区域。
```
+-----------------------------+   -
|                             |   :
| Output Section for peer n-1 |   : Output Section Size
|     (n = Maximum Peers)     |   :
+-----------------------------+   -
:                             :
:                             :
:                             :
+-----------------------------+   -
|                             |   :
|  Output Section for peer 1  |   : Output Section Size
|                             |   :
+-----------------------------+   -
|                             |   :
|  Output Section for peer 0  |   : Output Section Size
|                             |   :
+-----------------------------+   -
|                             |   :
|     Read/Write Section      |   : R/W Section Size
|                             |   :
+-----------------------------+   -
|                             |   :
|         State Table         |   : State Table Size
|                             |   :
+-----------------------------+   <-- Shared memory base address
```
每个 cell 都有自己的输出区域，它们可以通过这些区域进行通信。

### cell 间通知
jailhouse 提供了基于中断（实际上是 jailhouse 提供的虚拟 PCI 中断）的通知方式，每次当一个 cell 将内容写入自己的输出区域之后，这个 cell 使用中断去通知其他
任何 cell （基于配置中的 shmem_dev_id 字段）。

中断机制通过MSI-X或INTx实现，用于通知状态变更和事件，
且中断状态不由硬件维护，而是通过共享内存中的协议信息判断。管理程序确保所有对等体的共享内存布局和中断特性一致，并处理状态变更和中断传递。

### 测试
通过简单的测试，可以看出，inmate 在自己的输出区域写入信息，也就是字符串 "Hi!" 之后,使用虚拟 PCI 中断通知 root cell，jailhouse 会将这个中断转发给 root cell，
root cell 接收到这个虚拟外设发来的中断之后，进行处理，也就是读取对应 inmate 的输出区域，得到 inmate 的输出信息。

inmate 端输出：
```
Cell "inmate-demo" can be loaded
Started cell "inmate-demo"
IVSHMEM: Found device at 00:00.0
IVSHMEM: bar0 is at 0x00000000ff000000
IVSHMEM: bar1 is at 0x00000000ff001000
IVSHMEM: ID is 1
IVSHMEM: max. peers is 3
IVSHMEM: state table is at 0x000000003faf0000
IVSHMEM: R/W section is at 0x000000003faf1000
IVSHMEM: input sections start at 0x000000003fafa000
IVSHMEM: output section is at 0x000000003fafc000
IVSHMEM: initialized device
state[0] = 0
state[1] = 2
state[2] = 536870913
rw[0] = 0
rw[1] = 0
rw[2] = 0
in@0x0000 = 0
in@0x2000 = 0
in@0x4000 = 131072

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0
dev.id is 1

IVSHMEM: got interrupt 0 (#1)

IVSHMEM: sending IRQ 0 to peer 0
dev.id is 1

IVSHMEM: got interrupt 0 (#2)

IVSHMEM: sending IRQ 0 to peer 0
dev.id is 1

IVSHMEM: got interrupt 0 (#3)

IVSHMEM: sending IRQ 0 to peer 0
dev.id is 1

IVSHMEM: got interrupt 0 (#4)

IVSHMEM: sending IRQ 0 to peer 0
dev.id is 1

IVSHMEM: got interrupt 0 (#5)

IVSHMEM: sending IRQ 0 to peer 0
dev.id is 1

IVSHMEM: got interrupt 0 (#6)

IVSHMEM: sending IRQ 0 to peer 0
dev.id is 1

IVSHMEM: got interrupt 0 (#7)

IVSHMEM: sending IRQ 0 to peer 0
dev.id is 1

IVSHMEM: got interrupt 0 (#8)

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0
```
root cell 端输出：
```
ubuntu@ubuntu:~/jailhouse$ sudo ../ZYC_RtOs/jailhouse/tools/ivshmem-demo 
ID = 0
state[0] = 1
state[1] = 2
state[2] = 536870913
rw[0] = 0
rw[1] = 0
rw[2] = 0
in@0x0000 = 0
in@0x2000 = 0
in@0x4000 = 131072
Host rw[id]'s id is 0
Received message from Inmate: Hi!


Sending interrupt 0 to peer 1
Host rw[id]'s id is 0
Received message from Inmate: Hi!


Sending interrupt 0 to peer 1
Host rw[id]'s id is 0
Received message from Inmate: Hi!


Sending interrupt 0 to peer 1
Host rw[id]'s id is 0
Received message from Inmate: Hi!


Sending interrupt 0 to peer 1
Host rw[id]'s id is 0
Received message from Inmate: Hi!


Sending interrupt 0 to peer 1
Host rw[id]'s id is 0
Received message from Inmate: Hi!


Sending interrupt 0 to peer 1
Host rw[id]'s id is 0
Received message from Inmate: Hi!

```

## 推荐用法
Jailhouse 的共享内存理论上来说最多可以有 65536 peers，但是实际使用中，最多只有 CPU 核心数量大小的 peer 数量（这里我们只有2个 peer 进行通信）。

使用这种共享内存进行通信，优势和劣势很明显：
    
优势是：
        1. 速度块。2. 编写程序简单。

劣势是：
      1. 各个 cell 都可以访问其他 cell 的内存，不安全。2. 无法明确知道信息是否已经被其他 cell 得到，是典型的拜占庭问题。

注意： 这段共享内存是所有 peer 共享共用的。

后面基于这段共享内存，可以实现一些简单的通信方法或者协议。
