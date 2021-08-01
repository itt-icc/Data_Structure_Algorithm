#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max_num_edge 1000000
struct VVE
{
    int from;
    int to;
    int weight;
    int used;
};

struct VVE Edge[max_num_edge];  //创建所有的边
int father[max_num_edge] = {0}; //保平村父节点
int unique = 1;
int MSF = 1;

int cmp(const void *x, const void *y)
{
    struct VVE xx = *(struct VVE *)x;
    struct VVE yy = *(struct VVE *)y;
    return xx.weight - yy.weight;
}

/*寻找集合，同时压缩路径*/
int finds(int x, int root[])
{
    if (root[x] == x)
        return x;
    else
        return root[x] = finds(root[x], root);
}

void Union(int root1, int root2, int S[])
{
    S[root1] = S[root2];
}

int Kruskal(int num_v, int num_e)
{
    int num = 0;
    int result = 0;
    int i = 0;
    for (i = 0; i < num_e && num < num_v; ++i)
    {
        int root1 = finds(Edge[i].from, father);
        int root2 = finds(Edge[i].to, father);
        if (root1 != root2)
        {
            Union(root1, root2, father);
            result += Edge[i].weight;
            num++;
        }
    }
    ;
    /*完整的连通图*/
    if (num == num_v - 1)
        return result;

    //没有完整的连通图
    MSF = 0;
    for (; i < num_e; ++i)
    {
        int root1 = finds(Edge[i].from, father);
        int root2 = finds(Edge[i].to, father);
        if (root1 != root2)
        {
            Union(root1, root2, father);
        }
    }

    /*求联通分量,根据所有的父节点*/
    int N[1000000] = {0};
    for (int i = 1; i <= num_v; ++i)
    {
        N[father[i]]++; //父节点出现的次数
    }
    int cnt = 0;
    for (int i = 0; i <= num_v; ++i)
        if (N[i] > 0)
            cnt++;

    return cnt;
}

int main()
{
    int num_v, num_e;
    scanf("%d%d", &num_v, &num_e);
    for (int i = 1; i <= num_e; ++i)
    {
        scanf("%d%d%d", &Edge[i].from, &Edge[i].to, &Edge[i].weight);
        Edge[i].used = 0;
    }
    qsort(Edge + 1, num_e, sizeof(Edge[1]), cmp);
    for (int i = 1; i <= num_v; ++i)
        father[i] = i;
    int sum = Kruskal(num_v, num_e);

    if (MSF)
    {
        printf("%d\n", sum);
        printf("Yes");
    }
    else
    {
        printf("No MST\n");
        printf("%d",sum);

    }
    system("pause");
    return 0;
}
//0  2 4 5 7