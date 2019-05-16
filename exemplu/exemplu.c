/*
* @Author: Cristi Cretan
* @Date:   02-05-2019 22:44:05
* @Last Modified by:   Cristi Cretan
* @Last Modified time: 07-05-2019 10:58:40
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMERROR "22"

typedef struct list
{
	int size;
	void *item;
	int (*compare_func)(const void*, const void*);
	struct list *tail;
	struct list *next;
	struct list *prev;
} *List;

List initList(void *item, int (*compare_func)(const void*, const void*))
{
	List adjList = (List)malloc(sizeof(struct list));

	if(!adjList)
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
	if(!adjList)
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
	if(!adjList) 
		return NULL;

	if(adjList->compare_func(adjList->item, item) == 0)
	{
		List toDEL = adjList;
		adjList = adjList->next;
		if(adjList) 
			adjList->prev = NULL;
		free(toDEL);
		return adjList;
	}

	for (List iter = adjList; iter; iter = iter->next)
	{
		if(adjList->compare_func(iter->item, item) == 0)
		{
			List toDEL = iter;
			iter->prev->next = iter->next;
			if(iter->next)
				iter->next->prev = iter->prev;

			adjList->size--;
			free(toDEL);
			break;
		}
	}

	return adjList;
}

int intCompare(const void *a_pointer, const void *b_pointer)
{
	return *(int *)a_pointer - *(int *)b_pointer;
}

void printIntList(List adjList)
{
	for (; adjList; adjList = adjList->next)
		printf("%d ", *(int *)adjList->item);
	printf("\n");
}

List freeList(List adjList)
{
	while(adjList)
	{
		List toDEL = adjList;
		adjList = adjList->next;
		free(toDEL->item);
		free(toDEL);
	}
	return NULL;
}

int main()
{
	List adjList = NULL;
	int *x = malloc(sizeof(int));
	*x = 5;
	adjList = addLast(adjList, x, intCompare);
	x = malloc(sizeof(int));
	*x = 3;
	adjList = addLast(adjList, x, intCompare);
	x = malloc(sizeof(int));
	*x = 7;
	adjList = addLast(adjList, x, intCompare);
	// int *y = malloc(sizeof(int));
	// *y = 7;
	// adjList = deleteNode(adjList, y);
	// adjList = deleteNode(adjList, x);
	// printf("%d\n", adjList->size);
	printIntList(adjList);

	adjList = freeList(adjList);
	return 0;
}