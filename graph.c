/*
 * @Author: Cristi Cretan
 * @Date:   30-04-2019 11:42:32
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 08-05-2019 17:43:14
 */

#include "graph.h"

/**
 * Initialises a graph with maximum V vertices.
 * @param  V [Number of vertices]
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
	G->adjList = (Sentinel *)malloc(G->V * sizeof(Sentinel));

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
		G->adjList[i] = (Sentinel)malloc(sizeof(struct sentinel));

		if (!G->adjList[i])
		{
			fprintf(stderr, MEMERROR);
			exit(1);
		}

		G->adjList[i]->name = NULL;
		G->adjList[i]->head = NULL;
		G->distance[i] = 0;
	}

	return G;
}

/**
 * Inserts an edge between 2 vertices.
 * @param G [Graph]
 * @param u [Vertex to insert to]
 * @param v [Vertex to insert]
 * @param name [Actor's name of the vertex]
 * @param compare_func [Function comparation for the generic adjanceny list]
 */
Graph insertEdge(Graph G, int u, int v, char *name, int (*compare_func)(const void*, const void*))
{
	if (!G->adjList[u]->name)
		G->adjList[u]->name = strdup(name);

	int *toADD = allocInt(v);

	G->adjList[u]->head = addLast(G->adjList[u]->head, toADD, compare_func);

	return G;
}

/**
 * Performs a depth-first search of a given graph from a given start vertex.
 * @param  G     [Graph]
 * @param  start [Start vertex]
 * @return       [Graph]
 */
Graph DFS(Graph G, int start)
{
	G->distance[start] = 1;

	for (List iter = G->adjList[start]->head; iter; iter = iter->next)
		if (G->distance[*(int *)iter->item] == 0)
			G = DFS(G, *(int *)iter->item);
	return G;
}

/**
 * Performs a breadth-first search of a given graph from a given start vertex
 * and determines the distance from the given vertex to all the other vertices
 * from the start vertex's conex component.
 * @param  G     [Graph]
 * @param  start [Start vertex]
 * @return       [Graph]
 */
Graph BFS(Graph G, int start)
{
	G->distance[start] = 0;

	Queue q = NULL;

	q = pushQueue(q, &start, intCompare);

	while (!isEmptyQueue(q))
	{
		int node = *(int *)front(q);

		for (List iter = G->adjList[node]->head; iter; iter = iter->next)
			if (G->distance[*(int *)iter->item] == 0)
			{
				G->distance[*(int *)iter->item] = G->distance[node] + 1;
				q = pushQueue(q, (int *)iter->item, intCompare);
			}

		q = popQueue(q);
	}

	q = freeQueue(q);

	return G;
}

/**
 * Determines the cut vertices (articulation points) of a given graph.
 * @param  G           [Graph]
 * @param  cutVertices [The resulted Binary Search Tree of the cut vertices]
 * @param  node        [Start node]
 * @param  idx         [Discovery time of the node]
 * @param  low         [The lowest level a node can have without having a back-edge]
 * @param  root        [Root of the depth-first search]
 * @return             [Resulted Binary Search Treee with cut vertices]
 */
BinaryTree articulationP(Graph G, BinaryTree cutVertices, int node, int *idx,  int *low, int root)
{
	static int time = 0;

	int childcount = 0;

	idx[node] = low[node] = ++time;

	for (List iter = G->adjList[node]->head; iter; iter = iter->next)
	{
		if (idx[*(int *)iter->item] == -1)
		{
			childcount++;
			cutVertices = articulationP(G, cutVertices, *(int *)iter->item, idx, low, root);

			low[node] = min(low[node], low[*(int *)iter->item]);

			if (node == root && childcount > 1)
			{
				Actor toADD = actorFromName(G->adjList[node]->name);
				toADD->id = node;
				cutVertices = insertInBinaryTree(cutVertices, toADD, myStrcmp);
			}

			if (node != root && low[*(int *)iter->item] >= idx[node])
			{
				Actor toADD = actorFromName(G->adjList[node]->name);
				
				toADD->id = node;
				cutVertices = insertInBinaryTree(cutVertices, toADD, myStrcmp);
			}
		}
		else
			low[node] = min(low[node], idx[*(int *)iter->item]);
	}

	return cutVertices;
}

/**
 * Applies Bron-Kerbosch algorithm on a given graph to find maximal clique.
 * @param  G [Graph]
 * @param  R [The resulted maximal clique]
 * @param  P [A list of nodes which at first is filled with all the nodes]
 * @param  X [A List of excluded nodes that could not form a maximal clique]
 * @return   [The resulted maximal clique]
 */
BinaryTree BronKerbosch(Graph G, BinaryTree R, List P, List X)
{
	if ((!P) || (P->size == 0 && X->size == 0) )
		return R;

	for (List iter = P; iter; iter = iter->next)
	{
		List P_prime = intersectList(P, G->adjList[*(int *)iter->item]->head);

		Actor toADD = actorFromName(G->adjList[*(int *)iter->item]->name);
		toADD->id = *(int *)iter->item;

		R = insertInBinaryTree(R, toADD, myStrcmp);

		BinaryTree R_prime = copyBST(R);

		List X_prime = intersectList(X, G->adjList[*(int *)iter->item]->head);

		R = BronKerbosch(G, R_prime, P_prime, X_prime);
		P = deleteNode(P, (int *)iter->item);
		X = addLast(X, (int *)iter->item, intCompare);
	}

	return R;
}

/**
 * Reallocates the graph to the "necessary" size.
 * @param  G [Graph]
 * @param  V [Number of vertices]
 * @return   [Reallocated Graph]
 */
Graph reallocGraph(Graph G, int V)
{
	G->V = V;
	for (int i = G->V; i < MAX; ++i)
	{
		G->adjList[i]->head = freeIntList(G->adjList[i]->head);
		free(G->adjList[i]->name);
		free(G->adjList[i]);
	}
	G->adjList = (Sentinel *)realloc(G->adjList, G->V * sizeof(Sentinel));

	if (!G->adjList)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	G->distance = (int *)realloc(G->distance, G->V * sizeof(int));

	if (!G->distance)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	for (int i = 0; i < G->V; ++i)
		G->distance[i] = 0;

	return G;
}

/**
 * Frees the graph.
 * @param  G [Graph]
 * @return   [NULL]
 */
Graph freeGraph(Graph G)
{
	if (!G)
		return NULL;

	for (int i = 0; i < G->V; ++i)
	{
		G->adjList[i]->head = freeIntList(G->adjList[i]->head);
		free(G->adjList[i]->name);
		free(G->adjList[i]);
	}
	free(G->adjList);
	free(G->distance);
	free(G);

	return NULL;
}
