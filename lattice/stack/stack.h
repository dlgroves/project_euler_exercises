#include <stdio.h>
#ifndef STACK
#define STACK

typedef enum boolean
{
	FALSE, TRUE
} Boolean;

typedef struct vertex 
{
	int id;
	Boolean visited;
	struct vertex **neighbours;
	int noOfNeighbours;
} Vertex;

typedef struct graph 
{
	Vertex **vertices;
} Graph;

typedef struct stackelem
{
	Vertex *vertex;
	struct stackelem *next;
} StackElem;

typedef struct stack
{
	StackElem *top;
} Stack;

void initialiseStack(Stack **stack);
void initialiseStackElem(StackElem **stackElem);
Vertex *pop(Stack *stack);
void push(Stack *stack, Vertex *vertex);
Boolean isEmpty(Stack *stack);

#endif