//
// Created by zyc on 25-4-15.
//

#ifndef SHMEM_H
#define SHMEM_H

#include "ZYC_types.h"

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

void construct_message(struct Message *msg, MessageType type, uint32_t sender_id, uint32_t receiver_id, const char *data);

#endif //SHMEM_H
