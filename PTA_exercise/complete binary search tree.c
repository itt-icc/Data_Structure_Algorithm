#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define max 1000
int seq[max] = {-1};
int compare_func(const void*a,const void* b)
{
	return *(int*)a-*(int*)b;
}
//递归建立中序的树
void creat_CBST(int *cbst,int left,int right,int root)
{
    if(left==right+1)return;
    int l=findleft(right-left+1);//计算个数
    cbst[root]=seq[l+left];//注意为什么加上left，因为left为整个的基准
    creat_CBST(cbst,left,left+l-1,root*2);//左节点乘以二
    creat_CBST(cbst,left+l+1,right,root*2+1);//右节点乘以二再加一
}

int findleft(int N)//利用满二叉树的性质
{
    int h = (int)(log2(N + 1));
    return N > 3 * pow(2, h - 1) -1? pow(2, h) -1: N - pow(2, h - 1);
}
int main()
{
    int num = 0;
    scanf("%d", &num);
    for (int i = 1; i <= num; i++)
    {
        scanf("%d", seq + i);
    }
    qsort(seq+1,num,sizeof(int),compare_func);
    int cbst[max]={-1};
    creat_CBST(cbst,1,num,1);
    for (int i = 1; i < num; i++)
    {
        printf("%d ", cbst[i]);
    }
    printf("%d", cbst[num]);

    system("pause");
    return 0;
}