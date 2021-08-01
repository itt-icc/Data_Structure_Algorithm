#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
int N, CopyA[105], B[105], IsInsertion = 0;
int IsIdentical(int arr[])
{ //判别改变后的数组是否与B数组相同
    for (int i = 0; i < N; i++)
        if (arr[i] != B[i])
            return 0;
    return 1;
}
void Insertion_Sort(int A[])
{
    int Tmp, P, i, flag = 0;
    for (P = 1; P < N; P++)
    {
        Tmp = A[P];
        for (i = P; i > 0 && A[i - 1] > Tmp; i--) //i--别写成i++; 因为是从后往前比较（错误原因）
            A[i] = A[i - 1];
        A[i] = Tmp;
        //如果相同，说明是插入排序，再做一个迭代就退出
        if (IsIdentical(A))
        {
            printf("Insertion Sort\n");
            IsInsertion = 1; //如果不是，就转去判别是否是归并
            flag = 1;
            continue;
        }
        if (flag)
            break; //再做一次迭代就退出
    }
}
void PercDown(ElementType A[], int p, int N)
{
    //将N个元素的数组中以A[p]为根的子堆调整为最大堆
    int Parent, Child;
    ElementType X;
    X = A[p]; //取出根结点存放的值
    //(Parent * 2 + 1) < N 检测Parent有没有孩子
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
    {
        Child = Parent * 2 + 1;
        if (Child != N - 1 && A[Child] < A[Child + 1])
            Child++; //Child指向左右子结点较大者
        if (X >= A[Child])
            break;
        else //下滤
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}
void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void Heap_Sort(ElementType A[], int N)
{
    int i, flag = 0;
    //建立最大堆，由于下标从0开始，最后一个元素的父结点是 N / 2 - 1
    for (i = N / 2 - 1; i >= 0; i--)
        PercDown(A, i, N);
    //删除堆顶
    for (i = N - 1; i > 0; i--)
    {
        Swap(&A[0], &A[i]);
        PercDown(A, 0, i);
        //判别
        if (IsIdentical(CopyA))
        {
            printf("Heap Sort\n");
            flag = 1;
            continue;
        }
        if (flag)
            break;
    }
}
int main()
{
    int A[105];
    scanf("%d", &N);
    //read
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
        CopyA[i] = A[i];
    }
    for (int i = 0; i < N; i++)
        scanf("%d", &B[i]);
    //judge
    Insertion_Sort(A);
    if (IsInsertion)
    {
        printf("%d", A[0]);
        for (int i = 1; i < N; i++)
            printf(" %d", A[i]);
    }
    else
    {
        Heap_Sort(CopyA, N);
        printf("%d", CopyA[0]);
        for (int i = 1; i < N; i++)
            printf(" %d", CopyA[i]);
    }
    system("pause");
    return 0;
}