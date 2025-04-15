//
// Created by zyc on 25-4-15.
//

#include "shmem.h"

void construct_message(struct Message *msg, MessageType type, uint32_t sender_id, uint32_t receiver_id, const char *data) {
    msg->type = type;
    msg->sender_id = sender_id;
    msg->receiver_id = receiver_id;
    memcpy(msg->data, data, sizeof(msg->data) - 1);
    msg->length = strlen(msg->data);
}