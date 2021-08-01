#include <stdio.h>
#include <stdlib.h>
#define maxitem 301
#define inf 100000000

int G[maxitem][maxitem] = {0};
int visit[maxitem] = {0};
int distance[maxitem] = {0};

/*图结构初始化*/
void init()
{
    for (int i = 0; i < maxitem; i++)
        for (int j = 0; j < maxitem; j++)
            G[i][j] = inf;
}

/*to solve the problem*/
int solve(int seq[], int num)
{

    int start = seq[1];
    Dijkstra(start, num);

    for (int i = 1; i < num; ++i)
        if (distance[seq[i]] > distance[seq[i + 1]])
            return 0;

    return 1;
}

void Dijkstra(int start, int num)
{
    /*记录point到所有点的距离*/
    for (int i = 0; i < maxitem; ++i)
        distance[i] = G[i][start];
    distance[start] = 0;

    /*第一个点已经看到过*/
    visit[start] = 1;

    /*搜索路径*/
    int cnt = 1;
    while (cnt < num)
    {
        cnt++;

        /*找到距离最近的点*/
        int minedge = inf;
        int vertex = -1;
        for (int i = 1; i <= num; ++i)
        {
            if (visit[i] == 0 && distance[i] < minedge)
            {
                vertex = i;
                minedge = distance[i];
            }
        }

        /*当前点已经看到过了*/
        visit[vertex] = 1;

        /*对于所有的*/
        for (int j = 1; j <= num; ++j)
        {
            /*如果没有邻接就跳过*/
            if (G[j][vertex] == inf)
                continue;
            /*没有看到过同时距离较小*/
            if (visit[j] == 0 && distance[vertex] + G[vertex][j] < distance[j])
            {
                distance[j] = distance[vertex] + G[vertex][j]; //更新点的距离
            }
        }
    }
}

int main()
{
    init();
    int v = 0, e = 0;
    scanf("%d%d", &v, &e);

    
    /*建立邻接矩阵*/
    for (int i = 0; i < e; i++)
    {
        int from = 0, to = 0, weight = 0;
        scanf("%d%d%d", &from, &to, &weight);
        G[from][to] = weight;
        G[to][from] = weight;
    }


    /*初始化序列*/
    int seq[300] = {0};
    int k = 0;
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        /*load seq*/
        for (int j = 1; j <= v; j++)
            scanf("%d", seq + j);

        if (solve(seq, v))
            printf("YES\n");
        else
            printf("NO\n");

        /*refresh visit[]*/
        for (int i = 0; i < maxitem; ++i)
            visit[i] = 0;
    }
    system("pause");
    return 0;
}
