#include <stdio.h>
#define maxitem 1024
int Ht[maxitem] = {0};
int rHt[maxitem] = {0};
int Inserted[maxitem] = {0};

void init()
{
    for (int i = 0; i < maxitem; ++i)
    {
        Ht[i] = rHt[i] = Inserted[i] = -1;
    }
}

int findpos1(item, N)
{
    int positon = item % N;    /*初始的位置*/
    while (rHt[positon] != -1) /*找到空位置*/
    {
        positon++;
        if (positon >= N) /*表格溢出，循环开始*/
            positon = positon % N;
    }
    return positon;
}
int findpos(cell, N)
{ /* 找到cell应该插到哪里 */
    int pos;
    pos = cell % N;

    while (rHt[pos] != -1)
    { /* 只要这个位置不空就往下走 */
        ++pos;
        if (pos >= N)
            pos = pos % N; /* 超出表的长度，就回头从0开始 */
    }
    return pos; /* pos一定是个空位置 */
}
void Swap(int *a, int *b) /*Swap*/
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int cmp(int a, int b) /*compare by worth -> age->Name*/
{
    return a > b;
}

/*Quick sort*/
void Q_sort(int A[], int left, int right)
{
    int i = left;
    int j = right - 1;
    int pivot = right; /* select pivot */
    if (left < right)  /*if left >= right , then  end */
    {
        for (;;)
        {
            while (i <= right - 1 && !cmp(A[i], A[pivot]))
                i++; /* scan from left */
            while (j >= left && cmp(A[j], A[pivot]))
                j--; /* scan from right */

            if (i < j)
                Swap(&A[i], &A[j]); /* adjust partition */
            else
                break;
        }
        Swap(&A[i], &A[right]);  /* restore pivot */
        Q_sort(A, left, i - 1);  /* recursively sort left part */
        Q_sort(A, i + 1, right); /* recursively sort right part */
    }
}

void Print(int address[], int N, int cntPsitive)
{
    int cnt = 0;
    while (cnt < cntPsitive)
    {
        for (int i = 0; i < N; ++i)
        {
            if (Ht[i] < 0 || Inserted[i] > 0) /*positive && not inserted*/
                continue;
            int p = findpos(Ht[i], N);
            if (p != address[Ht[i]]) /*if not final position*/
                continue;
            else
            {
                cnt++;
                rHt[p] = Ht[i]; /*insert*/
                Inserted[i] = 1;

                /*first insert is the right input order so we output*/
                if (cnt < cntPsitive)
                    printf("%d ", Ht[i]);
                else
                    printf("%d", Ht[i]);
                break;
            }
        }
    }
}

int main()
{
    init();
    int N = 0;
    int address[100000] = {0};
    scanf("%d", &N);
    /*read*/
    int cntPsitive = 0;
    for (int i = 0; i < N; ++i)
    {
        scanf("%d", Ht + i);
        if (Ht[i] >= 0)
        {
            address[Ht[i]] = i;
            cntPsitive++;
        }
    }
    Q_sort(Ht, 0, N-1); /*Whenever there are multiple choices, the smallest number is always taken.*/
    Print(address,N,cntPsitive);
    system("pause");
    return 0;
}