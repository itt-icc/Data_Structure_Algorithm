#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;
typedef int item;

typedef struct
{
    int max;
    int top;
    int *data;
} stack;

stack creatc_stack(int max_size)
{
    stack s;
    s.max = max_size;
    s.top = 0;
    return s;
}

bool is_full(stack *s, int max_size)
{
    return s->max - 1 == s->top;
}

void push(stack *s, int item)
{
    s->data[++s->top] = item;
}

bool is_empty(stack *s)
{
    return s->top==0;
}

int pop(stack s)
{
    return s.data[s.top--];
}

int main()
{
    return 0;
}
