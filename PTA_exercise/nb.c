
/*给出一个序列，从小到大排序就是树的中序遍历，不妨中序遍历走一遍把各个结点放在各自的位置。
由于是完全二叉树，可以用数组按顺序来存，完事输出数组就是层序遍历。*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int n, l[2000], tr[2000], c = 0;

void inorder(int k)//如何理解这个递归程序呢
{
    if (k > n)
        return;
    inorder(k * 2);
    tr[k] = l[c++];//等式左边相当于访问，就是放进去，等式右边如何理解可以理解为找到节点
    //中序遍历得到的是顺序的访问，所以只需要按照顺序就可以找到
    inorder(k * 2 + 1);
}

void levelprint()
{
    for (int i = 1; i <= n; i++)
    {
        if (i == 1)
            printf("%d", tr[i]);
        else
            printf(" %d", tr[i]);
    }
}
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
int main()
{
    scanf("%d", &n);
    c=n;
    for (int i = 0; i < n; i++)
        scanf("%d", &l[i]);
    qsort(l, n, sizeof(l[0]), cmp);

    inorder(1);
    levelprint();
    system("pause");
    return 0;
}