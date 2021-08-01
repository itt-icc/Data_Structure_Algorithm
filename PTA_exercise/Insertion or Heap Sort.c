#include <stdio.h>
#define maxn 200
int insertseq[maxn] = {0};
int heapseq[maxn] = {0};
int testseq[maxn] = {0};
void print(int a[], int num)
{
    for (int i = 0; i < num - 1; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("%d", a[num - 1]);
}

int compareInsert(int num)
{
    for (int i = 0; i < num; i++)
    {
        if (insertseq[i] != testseq[i])
            return 0;
    }
    return 1;
}

int compareHeap(int num)
{
    for (int i = 0; i < num; i++)
    {
        if (heapseq[i] != testseq[i])
            return 0;
    }
    return 1;
}

int insertsort(int num)
{
    int i, j;
    int flag = 0;
    for (i = 1; i < num; ++i)
    {
        int cur = insertseq[i];
        for (j = i - 1; j >= 0 && insertseq[j] > cur; j--)
            insertseq[j + 1] = insertseq[j];
        insertseq[j + 1] = cur;
        if (compareInsert(num))
        {
            flag = 1;
            continue;
        }
        if (flag)
        {
            printf("Insertion Sort\n");
            print(insertseq, num);
            return 1;
        }
    }
    return 0;
}

void PercDown(int heap[], int p, int num)
{
    int parent, child;
    int X;
    X = heap[p];
    for (parent = p; (parent * 2 + 1) < num; parent = child)
    {
        child = parent * 2 + 1;
        if (child != num - 1 && heap[child] < heap[child + 1])
            child++;         /*找到最大的子节点*/
        if (X < heap[child]) /*大的子节点上浮*/
            heap[parent] = heap[child];/*父节点的位置放较大的子节点*/
        else
            break;/*父节点比子节点大就不再进行，所以一定要从最后一个父节点开始做*/
    }
    heap[parent] = X;
}
void Swap(int *x, int *y)
{
    /*直接从地址开始处理*/
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int Heap_Sort(int heap[], int num)
{
    int flag = 0;
    /*从最后一个元素的父节点，开始percdown,建立最大堆啊*/
    for (int i = num / 2 - 1; i >= 0; i--)
        PercDown(heap, i, num);
    for (int i = num - 1; i > 0; i--) /*从堆顶部开始，逐渐缩小下确界*/
    {
        Swap(heap, heap + i); /*把跟部heap[0],和最后一个元素交换，删除最大值*/
        PercDown(heap, 0, i); //最后一个元素的位置作为下确界，继续调整为最大堆
        if (compareHeap(num))
        {
            flag = 1;
            continue;
        }
        if (flag)
        {
            printf("Heap Sort\n");
            print(heapseq, num);
            return 0;
        }
    }
}

int main()
{
    int num = 0;
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d", insertseq + i);
        heapseq[i] = insertseq[i];
    }
    for (int i = 0; i < num; i++)
        scanf("%d", testseq + i);
    if (!insertsort(num))
        Heap_Sort(heapseq, num);
    system("pause");
    return 0;
}