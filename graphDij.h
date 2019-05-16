/*
 * @Author: Cristi Cretan
 * @Date:   22-04-2019 23:40:49
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 10-05-2019 18:25:49
 */
#ifndef __GRAPHDIJ_H__
#define __GRAPHDIJ_H__

#include "list.h"
#include "helpers.h"
#include "multiset.h"
#include "binaryTree.h"

typedef struct graph
{
	int V;
	int *distance;
	List *adjList;
} *Graph;

Graph initGraph(int V);
Graph insertEdge(Graph G, int u, Pair v, int (*compare_func)(const void*, const void*));
void printPath(int *parent, int ind, FILE *stream);
int checkGuardian(int timeMoment, int curentVertex, int *escapeCells, int escapeCellsCount, int **guardians, int *guardiansSize);
void dijkstra(Graph G, int start, int *escapeCells, int escapeCellsCount, int **guardians, int *guardiansSize, FILE *stream);
Graph freeGraph(Graph G);
#endif
