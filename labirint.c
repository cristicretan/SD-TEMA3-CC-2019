/*
 * @Author: Cristi Cretan
 * @Date:   22-04-2019 22:53:49
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 10-05-2019 21:52:42
 */

#include "list.h"
#include "multiset.h"
#include "graphDij.h"

/**
 * Reads input data and calls corresponding function to solve the task.
 */
int main(void)
{
	Graph G = NULL;
	int N, M, S;

	FILE *f = fopen("labirint.in", "r");

	fscanf(f, "%d %d %d\n", &N, &M, &S);

	G = initGraph(N + 2);

	int **guardians = (int **)malloc(G->V * sizeof(int *));
	int *guardiansSize = (int *)malloc(G->V * sizeof(int));

	for (int i = 0; i < M; ++i)
	{
		int x, y, cost;

		fscanf(f, "%d %d %d\n", &x, &y, &cost);

		G = insertEdge(G, x, make_pair(y, cost), intCompare);
		G = insertEdge(G, y, make_pair(x, cost), intCompare);
	}

	int capacity = resizeFactor;
	int *escapeCells = (int *)malloc(capacity * sizeof(int));
	int escapeCellsCount = 0;

	for (int i = 0; i < N; ++i)
	{
		char c;

		fscanf(f, "%c", &c);

		if (c == 'Y')
		{
			escapeCells[escapeCellsCount++] = i + 1;

			if (escapeCellsCount == capacity)
			{
				capacity *= resizeFactor;
				escapeCells = (int *)realloc(escapeCells, capacity * sizeof(int));
			}
		}

		int nrguard;

		fscanf(f, " %d", &nrguard);
		fscanf(f, "%c", &c);

		guardians[i + 1] = (int *)malloc(nrguard * sizeof(int));
		int k = 0;
		for (int j = 0; j < nrguard; ++j)
		{
			int x;

			fscanf(f, "%d", &x);

			guardians[i + 1][k++] = x;

			fscanf(f, "%c", &c);
		}
		guardiansSize[i + 1] = nrguard;
	}

	fclose(f);

	f = fopen("labirint.out", "w");
	
	dijkstra(G, S, escapeCells, escapeCellsCount, guardians, guardiansSize, f);

	fclose(f);

	G = freeGraph(G);
	for (int i = 0; i < N + 2; ++i)
		free(guardians[i]);
	free(guardians);
	free(guardiansSize);
	free(escapeCells);
	return 0;
}