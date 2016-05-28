#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack/stack.h"
#include "errors/errors.h"

#define DEFAULT_WEIGHT 1

int processArguments(int argc, char **argv);
void initialiseGraph(Graph **graph, int size);
void calculateNeighbours(Graph *graph, int size);
void printNeighbours(Graph *graph, int size);
double *dfs(Graph *graph, Vertex vertex, int size, double *total);
double iterativeDfs(Graph *graph, Vertex *vertex, Stack *stack, int size);

int main(int argc, char **argv)
{
	Stack *stack = NULL;
	Graph *graph = NULL;
	int number = processArguments(argc, argv);
	double total = 0;
	initialiseStack(&stack);
	initialiseGraph(&graph, number);
	double *noOfRoutes = dfs(graph, graph->vertices[0][0], number, &total);
	printf("This graph has %.0f routes\n", *noOfRoutes);
	return 0;
}

int processArguments(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "%s\n", "Usage: lattice GRID_SIZE");
		exit(EXIT_INCORRECT_PARAMS);
	}
	argv++;
	int gridSize = atoi(*argv);
	if(gridSize <= 0)
	{
		fprintf(stderr, "%s\n", "Grid size must be greater than zero.");
		exit(EXIT_INVALID_GRID_SIZE);
	}
	return gridSize;
}

void initialiseGraph(Graph **graph, int size)
{
	size_t graphSize = sizeof(Graph);
	*graph = (Graph *)malloc(graphSize);
	if(*graph == NULL)
	{
		fprintf(stderr, "Unable to allocate %lu bytes of memory, exiting...\n", graphSize);
		exit(EXIT_MALLOC_FAILURE);
	}
	(*graph)->vertices = (Vertex **)malloc(size * sizeof(Vertex *));
	for(int i = 0; i < size; i++)
	{
		(*graph)->vertices[i] = (Vertex *)malloc(size * sizeof(Vertex));
	}
	calculateNeighbours(*graph, size);
}

void calculateNeighbours(Graph *graph, int size)
{
	int i,j,id = 0;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			id++;
			graph->vertices[i][j].id = id;
			graph->vertices[i][j].visited = FALSE;
			graph->vertices[i][j].noOfNeighbours = 0;
			graph->vertices[i][j].neighbours = (Vertex **)malloc(2 * sizeof(Vertex *));
			if(i < size - 1)
			{
				graph->vertices[i][j].neighbours[graph->vertices[i][j].noOfNeighbours] = &(graph->vertices[i+1][j]);
				graph->vertices[i][j].noOfNeighbours++;
			}
			if(j < size - 1)
			{
				graph->vertices[i][j].neighbours[graph->vertices[i][j].noOfNeighbours] = &(graph->vertices[i][j+1]);
				graph->vertices[i][j].noOfNeighbours++;
			}
		}
	}
}

void printNeighbours(Graph *graph, int size)
{
	int i, j, k;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			printf("node %d=%d neighbours\n", graph->vertices[i][j].id, graph->vertices[i][j].noOfNeighbours);
			if(graph->vertices[i][j].noOfNeighbours > 0)
			{
				for(k = 0; k < graph->vertices[i][j].noOfNeighbours; k++)
				{
					printf("\tneighbour %d is node %d\n", k + 1, graph->vertices[i][j].neighbours[k]->id);
				}
			}
		}
	}
}

///todo:implement using iteration as recursion is too slow
double *dfs(Graph *graph, Vertex vertex, int size, double *total)
{
	if(vertex.visited)
		return total;
	
	if(vertex.id == size * size)
		*total += 1;
		
	vertex.visited = TRUE;
	int i;
	for(i = 0; i < vertex.noOfNeighbours; i++)
	{
		if(!vertex.neighbours[i]->visited)
		{
			dfs(graph, *(vertex.neighbours[i]), size, total);
		}
	}
	return total;
}

double iterativeDfs(Graph *graph, Vertex *vertex, Stack *stack, int size)
{
	double *total = (double *)malloc(sizeof(double));
	int i;
	*total = 0;
	push(stack, vertex);
	while(!isEmpty(stack))
	{
		vertex = pop(stack);
		//printf("Iterating into node %d\n", vertex->id);
		if(!vertex->visited)
		{
			vertex->visited = TRUE;
			//printf("We haven't visited node %d, iterating in\n", vertex->id);
			for(i = 0; i < vertex->noOfNeighbours; i++)
			{
				push(stack, vertex->neighbours[i]);
			}
		}
		else
		{
			//printf("We've already visited node %d, skipping\n", vertex->id);
		}
	}
	return *total;
}