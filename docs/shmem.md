# 共享内存通信
从前面的测试可以看出，对于共享内存部分，我们需要设计一种结构来实现 inmate 之间的通信。

结构如下（暂时只处理文本消息，其它消息使用者可以自行处理，默认实现中直接忽略）：
```c
typedef enum {
  MSG_TYPE_TEXT = 1,      // 文本消息
  MSG_TYPE_COMMAND,       // 命令消息
  MSG_TYPE_ACK,           // 确认消息
  MSG_TYPE_ERROR,         // 错误消息
} MessageType;

struct Message {
  MessageType type;       // 消息类型
  uint16_t length;        // 消息长度
  uint32_t sender_id;     // 发送者ID
  uint32_t receiver_id;   // 接收者ID
  char     data[256];     // 消息数据
};
```
对于每一个 inmate 所独占的 out 内存段，我们将其格式化为 Message 形式。

当一个 inmate 收到虚拟中断时，它检查发送中断的 out 内存段，然后读取其中的 data 也就是消息字段，显示出来。

## 测试结果
可以看出，host 端在收到 inmate-demo 发来的中断后，读取其 out 内存段，然后打印出来，其中内容是 "Hi!"。

而 inmate-demo 端收到 host 端发送来的中断后，读取其内容，有两种，我们在host初始化时写入 "Host init" 被读取，之后我们将信息设置为
 "Host Get interrupt" 并在中断之间保持不变。从端口输出可见设置正确，读取也没有错误。
```
Adding virtual PCI device 00:00.0 to cell "inmate-demo"
Shared memory connection established, peer cells:
 "Raspberry-Pi4"
Created cell "inmate-demo"
Page pool usage after cell creation: mem 75/994, remap 5/131072
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
state[2] = 536870917
rw[0] = 1
rw[1] = 0
rw[2] = 0
in@0x0000 = 0
in@0x2000 = 0
in@0x4000 = 270663680

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: got interrupt 0 (#1)
Get message from Host: Host init

IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: got interrupt 0 (#2)
Get message from Host: Host Get interrupt
 
IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: got interrupt 0 (#3)
Get message from Host: Host Get interrupt
 
IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: got interrupt 0 (#4)
Get message from Host: Host Get interrupt
 
IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: got interrupt 0 (#5)
Get message from Host: Host Get interrupt
 
IVSHMEM: sending IRQ 0 to peer 0

IVSHMEM: got interrupt 0 (#6)
Get message from Host: Host Get interrupt

```

```
ubuntu@ubuntu:~/jailhouse$ sudo ../ZYC_RtOs/jailhouse/tools/ivshmem-demo 
ID = 0
state[0] = 1
state[1] = 2
state[2] = 536870917
rw[0] = 0
rw[1] = 0
rw[2] = 0
in@0x0000 = 0
in@0x2000 = 0
in@0x4000 = 270663680

host get interrupt

Received message from Inmate: Hi!

Sending interrupt 0 to peer 1

host get interrupt

Received message from Inmate: Hi!

Sending interrupt 0 to peer 1

host get interrupt

Received message from Inmate: Hi!

Sending interrupt 0 to peer 1

host get interrupt

Received message from Inmate: Hi!

Sending interrupt 0 to peer 1

host get interrupt
```

# 使用建议
这里简单实现了一种通信方法，通过结构体 Message 的字段来验证发送者和接收者的身份并且设置信息内容。

## 处理消息
可以看到处理消息的示例：  
  
在 ZYC_RtOs/examples 下有host端运行的代码和inmate端运行的代码（这些代码需要和Jailhouse源码一起编译，这里列出只是作为示例）。

使用者可以根据自己的需要设计通信过程。这里只是提供了简单的通信方法。