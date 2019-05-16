/*
 * @Author: Cristi Cretan
 * @Date:   30-04-2019 11:43:28
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 07-05-2019 22:51:12
 */
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "queue.h"
#include "binaryTree.h"
#include "helpers.h"

typedef struct graph
{
	int V;
	int *distance;
	Sentinel *adjList;
} *Graph;

Graph initGraph(int V);
Graph insertEdge(Graph G, int u, int v, char *name,  int (*compare_func)(const void*, const void*));
Graph DFS(Graph G, int start);
Graph BFS(Graph G, int start);
BinaryTree articulationP(Graph G, BinaryTree cutVertices, int node, int *idx,  int *low, int root);
BinaryTree BronKerbosch(Graph G, BinaryTree R, List P, List X);
Graph reallocGraph(Graph G, int V);
Graph freeGraph(Graph G);
#endif
