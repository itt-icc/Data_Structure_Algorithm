/*
1.对图中的每一条边，扫描其他边，如果存在相同权值的边，则对此边做标记。
2.然后使用Kruskal（或者prim）算法求出最小生成树。
3.如果这时候的最小生成树没有包含未被标记的边，即可判定最小生成树唯一。
如果包含了标记的边，那么依次去掉这些边，再求最小生成树，如果求得的最小
生成树的权值和原来的最小生成树的权值相同，即可判断最小生成树不唯一。
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max_num_edge 1000

struct VVE
{
    int from;
    int to;
    int weight;
    int used;
    int equal;
    int del;
};

struct VVE Edge[max_num_edge];  //创建所有的边
int father[max_num_edge] = {0}; //保村父节点
int select[max_num_edge] = {0}; 
int unique = 1;
int MSF = 1;
int NUMber = 0;

int cmp(const void *x, const void *y)
{
    return ((struct VVE *)x)->weight-((struct VVE *)y)->weight;
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

int Kruskal(int num_v, int num_e)//O( |E| log |E| )
{
    int num = 0;
    int result = 0;
    int i = 1;
    for (i = 1; i <= num_e && num < num_v; ++i)
    {
        int root1 = finds(Edge[i].from, father);
        int root2 = finds(Edge[i].to, father);
        if (root1 != root2)
        {
            Union(root1, root2, father);
            result += Edge[i].weight;
            if (Edge[i].equal == 1 && Edge[i].used == 0) //访问相同权重的边
            {
                Edge[i].used = 1;
            }
            select[num] = i; //记录用到的所有的边
            num++;
        }
    }


    NUMber = num;
    /*完整的连通图*/
    if (num == num_v - 1)
        return result;

    //没有完整的连通图
    MSF = 0;
    for (; i <= num_e; ++i)
    {
        int root1 = finds(Edge[i].from, father);
        int root2 = finds(Edge[i].to, father);
        if (root1 != root2)
        {
            Union(root1, root2, father);
        }
    }
    /*求联通分量,根据所有的父节点*/
    int N[max_num_edge] = {0};
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

int Kruskal1(int num_v, int num_e)
{
    int num = 0;
    int result = 0;
    int i = 1;
    for (i = 1; i <= num_e && num < num_v; ++i)
    {

        if (Edge[i].del == 1) //跳过删除的边
        {
            continue;
        }

        int root1 = finds(Edge[i].from, father);
        int root2 = finds(Edge[i].to, father);
        if (root1 != root2)
        {
            Union(root1, root2, father);
            result += Edge[i].weight;
            num++;
        }
    }
    return result;
}

int main()
{
    int num_v, num_e;
    scanf("%d%d", &num_v, &num_e);
    for (int i = 1; i <= num_e; ++i)
    {
        scanf("%d%d%d", &Edge[i].from, &Edge[i].to, &Edge[i].weight);
        Edge[i].used = 0;
        Edge[i].equal = 0;
        Edge[i].del = 0;
    }
    qsort(Edge + 1, num_e, sizeof(Edge[1]), cmp);

    /*统计相同边出现的次数*/
    int equal[max_num_edge] = {0};
    for (int i = 1; i <= num_e; ++i)
        equal[Edge[i].weight]++;

    /*标记有相同权重的边*/
    for (int i = 1; i <= num_e; ++i)
        if (equal[Edge[i].weight] > 1)
            Edge[i].equal = 1;

    /*父节点初始化*/
    for (int i = 1; i <= num_v; ++i)
        father[i] = i;
    int sum = Kruskal(num_v, num_e);


    if (MSF) //如果存在最小树
    {
        for (int i = 0; select[i] < NUMber; ++i)
        {
            if (Edge[select[i]].equal == 1) //有相同权重的边
                unique = 0;                //说明不一定
        }
        printf("%d\n", sum);
        if (unique == 1) //一定是唯一的
            printf("Yes");
        else
        {
            int flag = 1;//这个用来判断不充分的条件下是不是唯一
            for (int j = 1; j <= num_e; j++)
            {
                if (Edge[j].used && Edge[j].equal) //在第一次MST中包含该边，并且该边具有权值相同的边
                {
                    Edge[j].del = 1; //删除掉该边，进行第二次MST

                    for (int i = 1; i <= num_v; ++i)//父节点再重新复位
                        father[i] = i;
                    
                    int counts2 = Kruskal1(num_v, num_e); 
                    if (counts2 == sum)
                    {
                        flag = 0;
                        printf("No");
                        break;
                    }
                    Edge[j].del = 0; //恢复被删掉的边
                }
            }
            if (flag)
                printf("Yes");
        }
    }
    else
    {
        printf("No MST\n");
        printf("%d", sum);
    }
    system("pause");
    return 0;
}
