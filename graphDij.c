/*
 * @Author: Cristi Cretan
 * @Date:   22-04-2019 23:41:03
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 10-05-2019 21:52:57
 */

#include "graphDij.h"

/**
 * Initialises graph with a given number of vertices.
 * @param  V [The number of vertices]
 * @return   [Initialised graph]
 */
Graph initGraph(int V)
{
	Graph G = (Graph)malloc(sizeof(struct graph));

	if (!G)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	G->V = V;
	G->adjList = (List *)malloc(G->V * sizeof(List));

	if (!G->adjList)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	G->distance = (int *)malloc(G->V * sizeof(int));

	if (!G->distance)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	for (int i = 0; i < G->V; ++i)
	{
		G->adjList[i] = NULL;
		G->distance[i] = 0;
	}

	return G;
}

/**
 * Inserts an edge between 2 vertices.
 * @param G            [Graph]
 * @param u            [Vertex to insert to]
 * @param v            [Pair to insert]
 * @param compare_func [Compare function]
 * @return             [Graph with the edge inserted]
 */
Graph insertEdge(Graph G, int u, Pair v, int (*compare_func)(const void*, const void*))
{
	G->adjList[u] = addLast(G->adjList[u], v, intCompare);
	return G;
}

/**
 * Prints the path from a vertex to another based on the parents array.
 * @param parent [Parents array]
 * @param ind    [Path to what node]
 * @param stream      [File stream]
 */
void printPath(int *parent, int ind, FILE *stream)
{
	if (parent[ind] == -1)
		return;

	printPath(parent, parent[ind], stream);

	fprintf(stream, "%d ", parent[ind]);
}

/**
 * Checks if it's a guardian at the given time moment and also checks
 * if the current vertex we're looking at it's a escape vertex.
 * @param  timeMoment   [Given time moment]
 * @param  curentVertex [Curent vertex]
 * @param  end          [Escape vertices]
 * @param  end_count    [Number of escape vertices]
 * @param  guardians    [Guardians binary trees]
 * @return              [Necessary waiting time]
 */
int checkGuardian(int timeMoment, int curentVertex, int *escapeCells, int escapeCellsCount, int **guardians, int *guardiansSize)
{
	int location = binarySearch(escapeCells, 0, escapeCellsCount, curentVertex);
	if (location != -1)
		return 0;

	location = 0;
	int waitingTime = 0;
	while (location > -1)
	{
		location = binarySearch(guardians[curentVertex], 0, guardiansSize[curentVertex], timeMoment);
		if(location > -1) waitingTime++;
		timeMoment++;
	}
	return waitingTime;
}

/**
 * Find the minimum time for escaping between the starting cell and "the best"
 * escaping cell it can get to.
 * @param G         [Graph]
 * @param start     [Starting cell]
 * @param end       [Array with all the escaping cells]
 * @param end_count [Number of escaping cells]
 * @param guardians [Guardians binary tree]
 * @param stream    [File stream]
 */
void dijkstra(Graph G, int start, int *escapeCells, int escapeCellsCount, int **guardians, int *guardiansSize, FILE *stream)
{

	Multiset H = initMultiset();

	int *parent = (int *)malloc(G->V * sizeof(int));

	for (int i = 0; i < G->V; ++i)
	{
		G->distance[i] = INF;
		parent[i] = -1;
	}

	G->distance[start] = checkGuardian(0, start, escapeCells, escapeCellsCount, guardians, guardiansSize);

	H = insert(H, make_pair(start, 0));

	while (!isEmptyMultiset(H))
	{
		Pair first = extractMin(H);
		for (List iter = G->adjList[first->node]; iter; iter = iter->next)
		{
			Pair iterPair = (Pair)iter->item;

			int foo = checkGuardian(G->distance[first->node] + iterPair->cost, iterPair->node, escapeCells, escapeCellsCount, guardians, guardiansSize);

			if (G->distance[iterPair->node] > G->distance[first->node] + iterPair->cost + foo)
			{
				G->distance[iterPair->node] = G->distance[first->node] + iterPair->cost + foo;

				H = insert(H, make_pair(iterPair->node, G->distance[iterPair->node]));
				parent[iterPair->node] = first->node;
			}
		}
		free(first);
	}

	int realend;
	int realmin = INF;

	for (int i = 0; i < escapeCellsCount; ++i)
		if (realmin > G->distance[escapeCells[i]])
		{
			realmin = G->distance[escapeCells[i]];
			realend = escapeCells[i];
		}

	fprintf(stream, "%d\n", realmin);
	printPath(parent, realend, stream);
	fprintf(stream, "%d\n", realend);

	H = freeMultiset(H);
	free(parent);
}

/**
 * Frees graph.
 * @param  G [Graph]
 * @return   [NULL]
 */
Graph freeGraph(Graph G)
{
	if (!G)
		return NULL;

	for (int i = 0; i < G->V; ++i)
		G->adjList[i] = freeIntList(G->adjList[i]);

	free(G->adjList);
	free(G->distance);
	free(G);

	return NULL;
}
