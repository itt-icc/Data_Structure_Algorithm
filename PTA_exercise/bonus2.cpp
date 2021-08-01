#include <stdio.h>
#include <stdlib.h>
#define MAN 1001
int Root[MAN] = {0};
int isRoot[MAN] = {0};
int Hobby[MAN] = {0};
int findRoot(int x)
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

    int
    findRoot1(int x) //寻找集合根节点
{
    if (Root[x] == x)
        return x;
    else
        return Root[x] = findRoot(Root[x]);
}

void Union(int a, int b) //合并操作
{
    Root[a] = b;
}

void pop_sort(int n, int a[]) //冒泡排序
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] < a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n, num, temp;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        Root[i] = i; //初始化成为自己
    for (int i = 1; i <= n; i++)
    {
        scanf("%d:", &num);
        for (int j = 0; j < num; j++)
        {
            scanf("%d", &temp);
            if (Hobby[temp] == 0) //当前的Hobby 没人喜欢
                Hobby[temp] = i;  //那就记录第一个喜欢的人

            int faA = findRoot(i);
            int faB = findRoot(Hobby[temp]);
            if (faA != faB)
                Union(i, Hobby[temp]); //把当前的和第一个喜欢这个爱好的人合并，那么每个人可以分为好几个
        }
    }

    for (int i = 1; i <= n; i++)
    {
        isRoot[findRoot(i)]++; //根节点计数
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (isRoot[i] != 0)
            ans++;
    printf("%d\n", ans);
    pop_sort(ans, isRoot + 1);
    for (int i = 1; i <= ans; i++)
    {
        printf("%d", isRoot[i]);
        if (i < ans)
            printf(" ");
    }
    system("pause");
    return 0;
}