// binary min-heap.
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct
{
    ElementType *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize(int MaxElements) /* details omitted */
{
    PriorityQueue H;
    H = malloc(sizeof(struct HeapStruct));
    /* Allocate the array plus one extra for sentinel */
    H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData; /* set the sentinel */
    return H;
}


void PercolateUp(int p, PriorityQueue H)
{
    int element_to_up = H->Elements[p];
    while(H->Elements[p/2]>element_to_up)//看父节点是不是比较大
    {
        H->Elements[p]=H->Elements[p/2];
        p/=2;
    }
    H->Elements[p] = element_to_up;
    
    // for (; H->Elements[p / 2] > element_to_up; p /= 2)
    // {
    //     H->Elements[p] = H->Elements[p / 2];
    // }
    
}

void PercolateDown(int p, PriorityQueue H)
{
    int i,Child;
    ElementType element_to_down= H->Elements[p]; /* take first and reset size */

    for (int i = p; i * 2 <= H->Size; i = Child)
    {
        /*begin*/
        Child = i * 2;
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child]) //如果有第二个子节点，就从中找到最小的子节点
            Child++;
        /*end*/
        // to find the large child

        if (element_to_down > H->Elements[Child])
            H->Elements[i] = H->Elements[Child]; //从子节点移动上去
        else if(element_to_down <= H->Elements[Child])//达到了父节点的要求
            break; /* find the proper position */
    }
    H->Elements[i] = element_to_down;
}

void Insert(ElementType X, PriorityQueue H)
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp(p, H);
}
/* H->Element[ 0 ] is a sentinel */
void Insert1(ElementType X, PriorityQueue H)
{
    int i;
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];

    H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H)
{
    ElementType MinElement;
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--]; //移动上去
    PercolateDown(1, H);
    return MinElement;
}
ElementType DeleteMin1(PriorityQueue H)
{
    int i, Child;
    ElementType MinElement, LastElement;
    MinElement = H->Elements[1];          /* save the min element */
    LastElement = H->Elements[H->Size--]; /* take last and reset size */
    for (i = 1; i * 2 <= H->Size; i = Child)
    { /* Find smaller child */
        Child = i * 2;
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            Child++;
        if (LastElement > H->Elements[Child]) /* Percolate one level */
            H->Elements[i] = H->Elements[Child];
        else
            break; /* find the proper position */
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for (i = 1; i <= H->Size; i++)
        printf(" %d", H->Elements[i]);
    system("pause");
    return 0;
}

/* Your function will be put here */
