#pragma once
#include "stdafx.h"
#include "stack_array.h"
#include <stdio.h>
#include <assert.h>

#define STACK_SIZE  100

static STACK_TYPE stack[STACK_SIZE];
static int top_element = -1;

void push(STACK_TYPE value){
	assert(!is_full());
	top_element += 1;
	stack[top_element] = value;
}

void pop(void)
{
	assert(!is_empty());
	top_element -= 1;
}

STACK_TYPE top(void)
{
	assert(!is_empty());
	return stack[top_element];
}

bool is_empty(void)
{
	return top_element == -1;
}

bool is_full(void)
{
	return top_element == (STACK_SIZE - 1);
}
