#include <stdio.h>

int find(int x, int S[])
{
    if (S[x] < 0)
        return x;
    else
    {
        S[x] = find(S[x], S);
    }
}
int iter_find(int x, int S[])
{
    int root = x;
    while (S[root] > 0)//沿着节点寻找父节点
        root = S[root];

    int cur = x;
    while (cur != root) //④
    {
        int front = S[cur]; //先记录一下下一个父节点①
        S[cur] = root;      //把当前的处理了②
        cur = front;        //把当前值更新为那个父节点③
    }
    return root;
}
void Union(int S[], int root1, int root2)
{
    if (S[root1] < S[root2])//说明root1比较深
    {
        S[root1] += S[root2];//先把root1的节点数量更新一下
        S[root2] = root1;//把root2指过来
    }
    else
    {
        S[root2] += S[root1];
        S[root1] = root2;
    }
}

int main()
{

    int S[8] = {0, 4, 6, 5, 2, -3, -4, 3};
    int r1 = iter_find(1, S);
    int r2 = find(7, S);
    Union(S, r1, r2);

    system("psuse");
    return 0;
}
