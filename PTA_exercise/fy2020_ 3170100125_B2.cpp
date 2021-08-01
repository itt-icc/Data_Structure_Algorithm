/* Author: Zhang Youchao;  ID: 3170100125;  No.02 */
#include <stdio.h>
#include <stdlib.h>
#define MAX 9999

void Swap(int *a, int *b) /*Swap*/
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int cmp(int a, int b) /*compare*/
{
    return a < b;
}

/*Quick sort*/
void Q_sort(int A[], int left, int right)
{
    int i = left;
    int j = right - 1;
    int pivot = right; /* select pivot */
    if (left < right)  /*if left >= right , then  end */
    {
        for (;;)/*the loop to compare and swap*/
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
/*Find the collection and compress the path at the same time*/
int finds(int x, int Root[])
{
    int root, trail, lead;
    for (root = x; Root[root] != root; root = Root[root])
        ;
    for (trail = x; trail != root; trail = lead)
    {
        lead = Root[trail];
        Root[trail] = root;
    }
    return root;
}

void Union(int root1, int root2, int S[])
{
    if (root1 != root2)
        S[root1] = S[root2];
}

int main()
{
    int np = 0;
    scanf("%d", &np);

    int hobby[MAX] = {0}; /*Record hobbies*/
    int root[MAX] = {0};  /*Record what kind of person the subscript is*/
    int cnt_root[MAX] = {0}; /*Record the number of people marked as collections below*/
    for (int i = 0; i < MAX; i++)
        root[i] = i;         /*First become an independent collection*/
    for (int i = 1; i <= np; i++)
    {
        int num = 0;
        scanf("%d:", &num);
        for (int j = 1; j <= num; ++j)
        {
            int h = 0;
            scanf("%d", &h);
            if (hobby[h] == 0)
                hobby[h] = i;      
            int ri = finds(i, root); 
            int rh = finds(hobby[h], root);
            /*Combine the current person with the first person with this current hobby*/
            Union(ri, rh, root);
        }
    }

    for (int i = 1; i <= np; ++i)
        cnt_root[finds(i, root)]++; /*Count the number of root nodes*/
    int cnt_class = 0;
    for (int i = 0; i <= np; ++i)
        if (cnt_root[i])
            cnt_class ++;
    printf("%d\n", cnt_class);
    Q_sort(cnt_root+1,0,np-1);/*Quick sort about the count*/
    for (int i = 1; i < cnt_class; ++i)
        printf("%d ", cnt_root[i]);
    printf("%d", cnt_root[cnt_class]);

    system("pause");
    return 0;
}