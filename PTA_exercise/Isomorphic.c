#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree() /* details omitted */
{
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    int num=0;
    scanf("%d",&num);
    for (int i=0;i<num;i++)
    {


    }
    return T;
}

/*
算法
① 根节点都为空 同构
② 其中一个根节点为空 非同构
③ 根节点元素不同 非同构
④ 根节点元素相同(好嘞，可以进入正题了
	if 两个根节点的左右子树都为空嘛？（就是当前节点是叶子节点嘛）
	是 同构
	else 
	递归 一的左子树与二的左&&一的右与二的右||一的左与二的右&&一的右与二的左
*/
int Isomorphic( Tree T1, Tree T2 )
{
    if(!T1&&!T2)return 1;
    if(T1==NULL&&T2!=NULL)return 0;
    if(T2==NULL&&T1!=NULL)return 0;
    if(T1->Element!=T2->Element)return 0;
    else
    {
        if((!T1->Left&&!T1->Right)&&(!T2->Left&&!T2->Right))
            return 1;
        else
        {
            return Isomorphic(T1->Left,T2->Right)&&Isomorphic(T1->Right,T2->Left)||Isomorphic(T1->Left,T2->Left)&&Isomorphic(T1->Right,T2->Right);
        }
    }
}

int main()
{
    Tree T1, T2;
    T1 = BuildTree();
    T2 = BuildTree();
    printf("%d\n", Isomorphic(T1, T2));
    return 0;
}

/* Your function will be put here */
