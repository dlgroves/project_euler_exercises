#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "../errors/errors.h"

void initialiseStack(Stack **stack)
{
	size_t stackSize = sizeof(Stack);
	*stack = (Stack *)malloc(stackSize);
	if(*stack == NULL)
	{
		fprintf(stderr, "Unable to allocate %lu bytes of memory, exiting...\n", stackSize);
		exit(EXIT_MALLOC_FAILURE);
	}
}

void initialiseStackElem(StackElem **stackElem)
{
	size_t stackElemSize = sizeof(StackElem);
	*stackElem = (StackElem *)malloc(stackElemSize);
	if(*stackElem == NULL)
	{
		fprintf(stderr, "Unable to allocate %lu bytes of memory, exiting...\n", stackElemSize);
		exit(EXIT_MALLOC_FAILURE);
	}
}

Vertex *pop(Stack *stack)
{
	if(stack == NULL)
	{
		fprintf(stderr, "%s", "Tried to pop an empty stack.");
		exit(EXIT_NPE);
	}
	StackElem *output = stack->top;
	stack->top = stack->top->next;
	return output->vertex;
}

void push(Stack *stack, Vertex *vertex)
{
	StackElem *elem = NULL;
	initialiseStackElem(&elem);
	elem->vertex = vertex;
	elem->next = stack->top;
	stack->top = elem;
}

Boolean isEmpty(Stack *stack)
{
	return (stack->top == NULL);
}