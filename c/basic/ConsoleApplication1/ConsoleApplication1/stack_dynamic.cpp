#include "stdafx.h"
#include "stack_dynamic.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>


static STACK_TYPE  *stack;
static size_t  stack_size;
static int     top_element = -1;

void create_stack(size_t size)
{
	assert(stack_size == 0);
	stack_size = size;

	stack = (STACK_TYPE*) malloc(stack_size * sizeof(STACK_TYPE));
	assert(stack != NULL);
}


void destory_stack(void)
{
	assert(stack_size > 0);
	stack_size = 0;
	free(stack);
	stack = NULL;
}

void dpush(STACK_TYPE value)
{
	assert(!dis_full());
	top_element += 1;
	stack[top_element] = value;
}

STACK_TYPE dpop(void)
{
	assert(!dis_empty());
	STACK_TYPE tmp = stack[top_element];
	top_element -= 1;
	return tmp;
}

STACK_TYPE dtop(void)
{
	assert(!dis_empty());
	return stack[top_element];
}


bool dis_empty(void)
{
	assert(stack_size > 0);
	return top_element == -1;
}

bool dis_full(void)
{
	assert(stack_size > 0);
	return top_element == stack_size - 1;
}