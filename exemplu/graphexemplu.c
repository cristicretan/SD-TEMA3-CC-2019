/*
* @Author: Cristi Cretan
* @Date:   03-05-2019 13:20:43
* @Last Modified by:   Cristi Cretan
* @Last Modified time: 03-05-2019 22:37:40
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define SIZE 200

typedef struct list
{
	int size;
	int id;
	struct list *tail;
	struct list *next;
	struct list *prev;
} *List;

typedef struct sentinel
{
	char *name;
	List head;
} *Sentinel;

typedef struct graph
{
	int V;
	int *distance;
	Sentinel *adjList;
} *Graph;

List initList(int id)
{
	List new = (List)malloc(sizeof(struct list));
	new->size = 1;
	new->id = id;
	new->tail = new;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

List addLast(List adjList, int id)
{
	if(!adjList)
		return initList(id);

	List new = initList(id);

	adjList->tail->next = new;
	new->prev = adjList->tail;
	adjList->tail = new;
	adjList->size++;

	return adjList;
}

List deleteNode(List adjList, int id)
{
	if(!adjList) 
		return NULL;

	if(adjList->size == 1)
	{
		free(adjList);
		return NULL;
	}

	if(adjList->id == id)
	{
		List toDEL = adjList;
		adjList = adjList->next;
		adjList->prev = NULL;
		free(toDEL);
		return adjList;
	}

	for (List iter = adjList; iter; iter = iter->next)
		if(iter->id == id)
		{			
			List toDelete = iter;
			
			iter->prev->next = iter->next;
			
			if(iter->next) 
				iter->next->prev = iter->prev;
			
			free(toDelete);
		}

	return adjList;
}

List freeList(List adjList)
{
	List iter = adjList;
	while(iter)
	{
		List toDelete = iter;
		iter = iter->next;

		free(toDelete);
	}
	return NULL;
}

void printList(List adjList)
{
	for (; adjList; adjList = adjList->next)
	{
		printf("%d ", adjList->id);
	}
	printf("\n");
}

Graph initGraph(int V)
{
	Graph G = (Graph)malloc(sizeof(struct graph));

	G->V = V;
	G->adjList = (Sentinel *)malloc(G->V * sizeof(Sentinel));
	G->distance = (int *)malloc(G->V * sizeof(int));

	for (int i = 0; i < G->V; ++i)
	{
		G->adjList[i] = (Sentinel)malloc(sizeof(struct sentinel));
		G->adjList[i]->head = NULL;
		G->adjList[i]->name = NULL;
		G->distance[i] = 0;
	}

	return G;
}

Graph insertEdge(Graph G, int u, int v, char *name)
{
	if(!G->adjList[u]->name)
		G->adjList[u]->name = strdup(name);
	G->adjList[u]->head = addLast(G->adjList[u]->head, v);
	return G;
}

Graph removeVertex(Graph G, int V)
{
	if (!G)
		return NULL;

	for (int i = 0; i < G->V; ++i)
		G->adjList[i]->head = deleteNode(G->adjList[i]->head, V);

	G->adjList[V]->head = freeList(G->adjList[V]->head);
	free(G->adjList[V]);

	return G;
}

void printGraph(Graph G)
{
	for (int i = 0; i < G->V; ++i)
	{
		printf("i %d: ", i);
		printList(G->adjList[i]->head);
	}
	printf("\n");
}

Graph freeGraph(Graph G)
{
	if (!G)
		return NULL;

	for (int i = 0; i < G->V; ++i)
	{
		G->adjList[i]->head = freeList(G->adjList[i]->head);
		free(G->adjList[i]->name);
		free(G->adjList[i]);
	}
	free(G->adjList);
	free(G->distance);
	free(G);

	return NULL;
}

int main()
{
	Graph G = NULL;
	G = initGraph(1000);
	G = insertEdge(G, 1, 2, "wah\0");
	G = insertEdge(G, 3, 2, "www\0");
	G = insertEdge(G, 1, 3, "ccc\0");
	G = insertEdge(G, 4, 2, "ddd\0");
	G = insertEdge(G, 3, 4, "eee\0");
	G = insertEdge(G, 2, 4, "fff\0");

	G->V = 5;
	for (int i = 5; i < 1000; ++i)
	{
	 	G->adjList[i]->head = freeList(G->adjList[i]->head);
	 	free(G->adjList[i]->name);
		free(G->adjList[i]);
	}
	G->adjList = (Sentinel *)realloc(G->adjList, G->V*sizeof(Sentinel));
	
	G->distance = realloc(G->distance, G->V*sizeof(int));

	G = freeGraph(G);
	return 0;
}