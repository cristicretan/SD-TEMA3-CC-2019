/*
 * @Author: Cristi Cretan
 * @Date:   30-04-2019 12:18:27
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 07-05-2019 22:04:25
 */
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "list.h"

typedef struct queue
{
	int size;
	List head, tail;
} *Queue;

Queue initQueue(void *item, int (*compare_func)(const void*, const void*));
bool isEmptyQueue(Queue Q);
Queue pushQueue(Queue Q, void *item, int (*compare_func)(const void*, const void*));
Queue popQueue(Queue Q);
void *front(Queue Q);
Queue freeQueue(Queue Q);
#endif
