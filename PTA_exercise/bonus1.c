#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max 100
int compare_func(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
// qsort(seq+1,num,sizeof(int),compare_func);

void pop_sort(int n, int a[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int find1(int x, int s[])
{
    int root, trail, lead;
    for (root = x; s[root] > 0; root = s[root])
        ;
    for (trail = x; trail != root; trail = lead)
    {
        lead = s[trail];
        s[trail] = root;
    }
    return root;
}

void Union(int S[], int root1, int root2)
{
    if (S[root1] < S[root2])
    {
        S[root1] += S[root2];
        S[root2] = root1;
    }
    else
    {
        S[root2] += S[root1];
        S[root1] = root2;
    }
}
int resemble(int num1, int a[], int num2, int b[])
{
    if (a[num1] < b[1] || b[num2] < a[1])
        return 0;
    if (num1 < num2)
        for (int i = 1; i <= num1; ++i)
        {
            if (binsearch(b + 1, a[i], num2))
                return 1;
        }
    else
        for (int i = 1; i <= num2; ++i)
        {
            if (binsearch(a + 1, b[i], num1))
                return 1;
        }

    return 0;
}
int binsearch(int a[], int X, int num)
{
    int left = 0;
    int right = num - 1;
    int mid;
    while (left <= right)
    {
        mid = (right + left) / 2;
        if (a[mid] < X)
        {
            left = mid + 1;
        }
        else if (a[mid] > X)
        {
            right = mid - 1;
        }
        else
        {
            return 1;
        }
        return 0;
    }
}

void check(int n, int S[])
{
    int count = 0;
    int a[max];
    for (int i = 1; i <= n; i++)
        if (S[i] < 0)
        {
            count++;
        }
    printf("%d\n", count);
    pop_sort(n, S + 1);
    int flag = 1;
    for (int i = 1; i <= n&&S[i]<0; ++i)
    {
        if (flag)
        {
            flag=0;
            printf("%d", -1*S[i]);
        }
        else
            printf(" %d", -1*S[i]);
    }
}

int main()
{
    int p[max][max];
    for (int i = 0; i < max; i++)
        for (int j = 0; j < max; j++)
            p[i][j] = -1;
    int num = 0;
    scanf("%d", &num);
    for (int i = 1; i <= num; i++)
    {
        int num_h = 0;
        scanf("%d: ", &num_h);
        p[i][0] = num_h;
        for (int j = 1; j <= num_h; j++)
        {
            int k = 0;
            scanf("%d", &k);
            p[i][j] = k;
        }
        qsort(p[i]+1,num_h,sizeof(int),compare_func);
        // pop_sort(num_h, p[i] + 1);
    }
    int S[max];
    for (int i = 0; i < max; ++i)
        S[i] = -1;

    for (int i = num; i >= 1; --i)
    {
        for (int j = 1; j <= num; ++j)
        {
            int root1 = find1(i, S);
            int root2 = find1(j, S);
            if (root1 != root2 && resemble(p[i][0], p[i], p[j][0], p[j]))
            {
                Union(S, root1, root2);
                break;
            }
        }
    }

    check(num, S);

    // for (int i = 1; i <= num; i++)
    // {
    //     printf("%d\n", S[i]);
    // }

    system("pause");

    return 0;
}
