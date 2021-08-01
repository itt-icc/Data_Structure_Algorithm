#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass(ElementType list[], ElementType sorted[], int N, int length);
void merge_pass1(ElementType list[], ElementType sorted[], int N, int length)
{
    for (int i = 0; i < N; i += length * 2)
    {
        int a = i, b = i + length, j = 0;
        int aa = i + length, bb = i + length * 2;
        if (aa > N)
            aa = N;
        if (bb > N)
            bb = N;
        while (a < aa && b < bb)
        {
            if (list[a] < list[b])
            {
                sorted[i + j++] = list[a++];
            }
            else
                sorted[i + j++] = list[b++];
        }
        while (a < aa)
        {
            sorted[i + j++] = list[a++];
        }
        while (b < bb)
        {
            sorted[i + j++] = list[b++];
        }
    }
}

void output(ElementType list[], int N)
{
    int i;
    for (i = 0; i < N; i++)
        printf("%d ", list[i]);
    printf("\n");
}

void merge_sort(ElementType list[], int N)
{
    ElementType extra[MAXN]; /* the extra space required */
    int length = 1;          /* current length of sublist being merged */
    while (length < N)
    {
        merge_pass(list, extra, N, length); /* merge list into extra */
        output(extra, N);
        length *= 2;
        merge_pass(extra, list, N, length); /* merge extra back to list */
        output(list, N);
        length *= 2;
    }
}

int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);
    system("pause");

    return 0;
}

/* Your function will be put here */
void merge_pass(ElementType list[], ElementType sorted[], int N, int length)
{
    for (int i = 0; i < N; i += 2 * length)
    {
        int sub1l = i, sub1r = i + length;
        int sub2l = i + length, sub2r = i + 2 * length;
        int idx = 0;
        if (sub1r >= N)
            sub1r = N;
        if (sub2r >= N)
            sub2r = N;
        while (sub1l < sub1r && sub2l < sub2r)
        {
            if (list[sub1l] < list[sub2l])
            {
                sorted[i + idx] = list[sub1l];
                idx++;
                sub1l++;
            }
            else
            {
                sorted[i + idx] = list[sub2l];
                idx++;
                sub2l++;
            }
        }
        while (sub1l < sub1r)
        {
            sorted[i + idx] = list[sub1l];
            idx++;
            sub1l++;
        }
        while (sub2l < sub2r)
        {
            sorted[i + idx] = list[sub2l];
            idx++;
            sub2l++;
        }
    }
}