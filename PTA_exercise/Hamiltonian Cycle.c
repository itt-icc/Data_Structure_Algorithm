#include <stdio.h>
#include <stdlib.h>
#define maxitem 201
int G[maxitem][maxitem] = {0};
int visit[maxitem] = {0};

int solve(int seq[], int n, int v)
{
    /*长度必须一致，首位必须成环*/
    if (n != v + 1 || seq[1] != seq[n])
        return 0;
    for (int i = 1; i < n; i++)
    {
        /*是否重复访问*/
        if (visit[seq[i]])
            return 0;
        visit[seq[i]] = 1;
        /*路径是否是相通的*/
        if (G[seq[i]][seq[i + 1]] + G[seq[i + 1]][seq[i]] == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int v = 0, e = 0;
    scanf("%d%d", &v, &e);
    /*建立邻接矩阵*/
    for (int i = 0; i < e; i++)
    {
        int from = 0, to = 0;
        scanf("%d%d", &from, &to);
        G[from][to] = 1;
    }
    /*初始化序列*/
    int seq[40000] = {0};
    int k = 0;
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        int n = 0;
        scanf("%d", &n);
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", seq + j);
        }
        if (solve(seq, n, v))
            printf("YES\n");
        else
            printf("NO\n");
        /*初始化入度*/
        for (int i = 0; i < maxitem; ++i)
            visit[i] = 0;
    }
    system("pause");
    return 0;
}
