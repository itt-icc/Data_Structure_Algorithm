#include <stdio.h>
#include <stdlib.h>
#define maxn 10000
struct data
{
    int x;
    int y;
    int w;
} sides[maxn + 1];
int set[110];
bool flag[maxn + 1];
int cmp(const void *a, const void *b)
{
    return ((data *)a)->w - ((data *)b)->w;
}
int find(int x) //寻找根节点；
{
    if (set[x] == x)
        return x;
    set[x] = find(set[x]); //寻找的过程中，更新set[x]的值，路径压缩；
    return set[x];
}
int main()
{
    int k, n, i, j, ans, t, ans1, rx, ry, before, m;
    bool bo; //标志是否找到答案；
    scanf("%d", &k);
    while (k--)
    {
        scanf("%d%d", &n, &m);
        bo = 0;
        for (i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &sides[i].x, &sides[i].y, &sides[i].w);
        }
        qsort(&sides[1], m, sizeof(sides[0]), cmp); //贪心，排序，按权值；
        for (i = 1; i <= n; i++)
            set[i] = i; //并查集初始化；
        for (i = 1; i <= m; i++)
            flag[i] = 0;
        ans = 0;
        i = 0;
        j = 0;
        while (i < n - 1) //求最小生成树
        {
            j++;
            rx = find(sides[j].x); //寻找根节点
            ry = find(sides[j].y);
            if (rx != ry)
            {
                i++;
                ans += sides[j].w;
                set[rx] = set[ry]; //合并集合 ；
                flag[j] = 1;
            }
        }
        if (m == n - 1)
        {
            printf("%d\n", ans);
            continue;
        } //如果最小生成树的边数等于n-1;那只有一种，就是所求的
        before = 1;
        flag[before] = 0;            //先才能够flag[1]的边开始删
        for (t = 1; t <= n - 1; t++) //进行n-1次删边的操作。。
        {
            for (i = 1; i <= n; i++)
                set[i] = i; //并查集初始化；
            i = 0;
            j = 0;
            ans1 = 0;
            while (i < n - 1) //同样的操作，求次最小生成树。。
            {
                j++;
                if (j != before) //每次删除一条边。。
                {
                    rx = find(sides[j].x);
                    ry = find(sides[j].y);
                    if (rx != ry)
                    {
                        i++;
                        ans1 += sides[j].w;
                        set[rx] = set[ry];
                    }
                }
            }
            if (ans1 == ans)
            {
                bo = 1;
                break;
            }                                 //如果次最小生成树的总权值等于最小生成树，则不唯一
            for (i = before + 1; i <= m; i++) //寻找一条边，赋值before，给下次删除用的。。
                if (flag[i])
                {
                    before = i;
                    flag[before] = 0;
                    break;
                }
        }
        if (bo)
            printf("Not Unique\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}