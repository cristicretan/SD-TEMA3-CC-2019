/*
 * @Author: Cristi Cretan
 * @Date:   30-04-2019 12:23:25
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 08-05-2019 17:05:56
 */

#include "queue.h"

/**
 * Initialises a generic queue with a given item and a given compare function.
 * @param item         [Item]
 * @param compare_func [Compare function]
 * @return             [Initialised queue]
 */
Queue initQueue(void *item, int (*compare_func)(const void*, const void*))
{
	Queue Q = (Queue)malloc(sizeof(struct queue));

	Q->size = 1;
	Q->head = Q->tail = initList(item, compare_func);

	return Q;
}

/**
 * Checks if the queue is empty or not.
 * @param  Q [Queue]
 * @return   [True if it's empty, false otherwise]
 */
bool isEmptyQueue(Queue Q)
{
	if (!Q || !Q->head || Q->size == 0)
		return true;
	return false;
}

/**
 * Pushes an item in queue.
 * @param Q            [Queue to push item into]
 * @param item         [Item]
 * @param compare_func [Compare function]
 * @return             [Queue with the item pushed]
 */
Queue pushQueue(Queue Q, void *item, int (*compare_func)(const void*, const void*))
{
	if (isEmptyQueue(Q))
		return initQueue(item, compare_func);

	List new = initList(item, compare_func);

	Q->tail->next = new;
	Q->tail = new;
	Q->size++;
	return Q;
}

/**
 * Pops an item from the queue.
 * @param  Q [Queue]
 * @return   [Queue with the first item popped]
 */
Queue popQueue(Queue Q)
{
	if (!isEmptyQueue(Q))
	{
		List toDEL = Q->head;

		Q->head = Q->head->next;
		Q->size--;
		free(toDEL);
	}
	return Q;
}

/**
 * Returns the head of the queue.
 * @param  Q [Queue]
 * @return   [Item from the head of the queue, NULL if Q is empty]
 */
void *front(Queue Q)
{
	if (!isEmptyQueue(Q))
		return Q->head->item;

	return NULL;
}

/**
 * Frees queue.
 * @param  Q [Queue]
 * @return   [NULL]
 */
Queue freeQueue(Queue Q)
{
	while (!isEmptyQueue(Q))
		Q = popQueue(Q);

	if (Q)
		free(Q);

	return NULL;
}