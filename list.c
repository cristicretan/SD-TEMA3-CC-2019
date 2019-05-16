/*
 * @Author: Cristi Cretan
 * @Date:   22-04-2019 18:13:11
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 07-05-2019 21:58:56
 */

#include "list.h"

List initList(void *item, int (*compare_func)(const void*, const void*))
{
	List adjList = (List)malloc(sizeof(struct list));

	if (!adjList)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	adjList->size = 1;
	adjList->item = item;
	adjList->compare_func = compare_func;
	adjList->tail = adjList;

	adjList->next = NULL;
	adjList->prev = NULL;
	return adjList;
}

List addLast(List adjList, void *item, int (*compare_func)(const void*, const void*))
{
	if (!adjList)
		return initList(item, compare_func);

	List new = initList(item, compare_func);

	adjList->tail->next = new;
	new->prev = adjList->tail;
	adjList->tail = new;
	adjList->size++;

	return adjList;
}

List deleteNode(List adjList, void *item)
{
	if (!adjList)
		return NULL;

	if (adjList->compare_func(adjList->item, item) == 0)
	{
		List toDEL = adjList;

		adjList = adjList->next;
		if (adjList)
			adjList->prev = NULL;
		free(toDEL);
		return adjList;
	}

	for (List iter = adjList; iter; iter = iter->next)
		if (adjList->compare_func(iter->item, item) == 0)
		{
			List toDelete = iter;

			iter->prev->next = iter->next;

			if (iter->next)
				iter->next->prev = iter->prev;
			adjList->size--;

			free(toDelete);
		}

	return adjList;
}

List copyList(List adjList)
{
	List new = NULL;

	for (; adjList; adjList = adjList->next)
		new = addLast(new, adjList->item, adjList->compare_func);

	return new;
}

bool containsInList(List adjList, void *item)
{
	for (; adjList; adjList = adjList->next)
		if (adjList->compare_func(adjList->item, item) == 0)
			return true;
	return false;
}

List intersectList(List adjList1, List adjList2)
{
	List new = NULL;

	for (List iter = adjList1; iter; iter = iter->next)
		if (containsInList(adjList2, iter->item))
			new = addLast(new, iter->item, adjList1->compare_func);

	return new;
}

List freeIntList(List adjList)
{
	while (adjList)
	{
		List toDelete = adjList;
		
		adjList = adjList->next;
		free(toDelete->item);
		free(toDelete);
	}
	return NULL;
}
