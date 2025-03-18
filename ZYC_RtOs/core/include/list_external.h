//
// Created by zyc on 25-3-18.
//

#ifndef LIST_EXTERNAL_H
#define LIST_EXTERNAL_H

#include "ZYC_types.h"

struct TagListObject {
    struct TagListObject *prev;
    struct TagListObject *next;
};

#define OS_LIST_INIT(head)     \
do {                       \
(head)->prev = (head); \
(head)->next = (head); \
} while (0)

#define LIST_OBJECT_INIT(object) { \
&(object), &(object)       \
}

#define INIT_LIST_OBJECT(object)   \
do {                           \
(object)->next = (object); \
(object)->prev = (object); \
} while (0)

#define LIST_LAST(object) ((object)->prev)
#define OS_LIST_FIRST(object) ((object)->next)

/* list action low level add */
OS_SEC_ALW_INLINE INLINE void ListLowLevelAdd(struct TagListObject *newNode, struct TagListObject *prev,
                                              struct TagListObject *next)
{
    newNode->next = next;
    newNode->prev = prev;
    next->prev = newNode;
    prev->next = newNode;
}

/* list action add */
OS_SEC_ALW_INLINE INLINE void ListAdd(struct TagListObject *newNode, struct TagListObject *listObject)
{
    ListLowLevelAdd(newNode, listObject, listObject->next);
}

/* list action tail add */
OS_SEC_ALW_INLINE INLINE void ListTailAdd(struct TagListObject *newNode, struct TagListObject *listObject)
{
    ListLowLevelAdd(newNode, listObject->prev, listObject);
}

/* list action lowel delete */
OS_SEC_ALW_INLINE INLINE void ListLowLevelDelete(struct TagListObject *prevNode, struct TagListObject *nextNode)
{
    nextNode->prev = prevNode;
    prevNode->next = nextNode;
}

/* list action delete */
OS_SEC_ALW_INLINE INLINE void ListDelete(struct TagListObject *node)
{
    ListLowLevelDelete(node->prev, node->next);

    node->next = NULL;
    node->prev = NULL;
}

#endif //LIST_EXTERNAL_H
