/*
 * @Author: Cristi Cretan
 * @Date:   22-04-2019 18:12:24
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 07-05-2019 21:59:27
 */
#ifndef __LIST_H__
#define __LIST_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helpers.h"

typedef struct list
{
	int size;
	void *item;
	int (*compare_func)(const void*, const void*);
	struct list *tail;
	struct list *next;
	struct list *prev;
} *List;

typedef struct sentinel
{
	char *name;
	List head;
} *Sentinel;

List initList(void *item, int (*compare_func)(const void*, const void*));
List addLast(List adjList, void *item, int (*compare_func)(const void*, const void*));
List deleteNode(List adjList, void *item);
List copyList(List adjList);
bool containsInList(List adjList, void *item);
List intersectList(List adjList1, List adjList2);
List freeIntList(List adjList);
#endif
