#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 10

typedef struct Stack
{
	int x, y;
	int index;
}Stack;

void ShowStack(Stack* stack, Stack* stack2,int index);
void Push(Stack* stack, int* index, Stack input);
Stack Pop(Stack* stack, int* index);
void PopAndPush(Stack* stack, int* index, Stack value);

int main()
{
	Stack stack[COUNT];
	memset(stack, -1, sizeof(stack));
	Stack stack2[COUNT];
	memset(stack2, -1, sizeof(stack2));

	int stackIndex = 0;
	int stack2Index = 0;

	for (int i = 0; i < COUNT - 5; ++i)
	{
		Stack temp;
		temp.x = rand() % 100;
		temp.y = rand() % 100;
		temp.index = stackIndex;

		Push(stack, &stackIndex, temp);
	}

	ShowStack(stack, stack2,stackIndex);

	Stack temp;
	temp.x = rand() % 20;
	temp.y = rand() % 20;
	temp.index = stackIndex;
	Push(stack, &stackIndex, temp);

	ShowStack(stack, stack2, stackIndex);

	for (int i = 0; i < COUNT - 5; ++i)
	{
		PopAndPush(stack2, &stack2Index, Pop(stack, &stackIndex));
		ShowStack(stack, stack2, stackIndex);
	}

	PopAndPush(stack2, &stack2Index, Pop(stack, &stackIndex));
	ShowStack(stack, stack2, stackIndex);


	PopAndPush(stack2, &stack2Index, Pop(stack, &stackIndex));
	ShowStack(stack, stack2, stackIndex);


	PopAndPush(stack, &stackIndex, Pop(stack2, &stack2Index));
	ShowStack(stack, stack2, stackIndex);


	temp.x = rand() % 100;
	temp.y = rand() % 100;
	temp.index = stackIndex;
	Push(stack, &stackIndex, temp);
	ShowStack(stack, stack2, stackIndex);


	temp.x = rand() % 100;
	temp.y = rand() % 100;
	temp.index = stackIndex;
	Push(stack, &stackIndex, temp);
	ShowStack(stack, stack2, stackIndex);



	PopAndPush(stack2, &stack2Index, Pop(stack, &stackIndex));
	ShowStack(stack, stack2, stackIndex);
}

void ShowStack(Stack* stack, Stack* stack2,int index)
{
	printf("\nStack\n");
	for (int i = 0; i < COUNT; ++i)
	{
		if (stack[i].index != -1)
		{
		printf("stack[%d] x = %d, y = %d\t", stack[i].index, stack[i].x, stack[i].y);
		}
		if (stack2[i].index != -1)
		{
		printf("stack2[%d] x = %d, y = %d\t", stack2[i].index, stack2[i].x, stack2[i].y);
		}
		printf("\n");
	}
}

void Push(Stack* stack, int* index, Stack input)
{
	if (((*index) + 1) > 10)
	{
		printf("Stack OverFlowed\n");
		(*index) = COUNT;
		return;
	}
	printf("Push\n");
	stack[(*index)] = input;
	(*index) += 1;
}

Stack Pop(Stack* stack, int* index)
{
	if (((*index) - 1) < 0)
	{
		Stack temp;
		temp.x = -1;
		temp.y = -1;
		temp.index - 1;

		printf("Stack UnderFlowed\n");
		(*index) = 0;
		return temp;
	}
	printf("\nPopValue\n");
	(*index) -= 1;
	printf("stack[%d] x = %d, y = %d\n", stack[(*index)].index, stack[(*index)].x, stack[(*index)].y);

	Stack out = stack[(*index)];
	memset(&stack[(*index)], -1, sizeof(Stack));

	return out;
}

void PopAndPush(Stack* stack, int* index, Stack value)
{
	if (value.x == -1)
	{
		return;
	}
	value.index = (*index);
	stack[(*index)] = value;
	(*index) += 1;
}
