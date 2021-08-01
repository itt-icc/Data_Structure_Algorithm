#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    false,
    true
} bool;

#define MaxVertexNum 10 /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; //邻接节点指针
struct AdjVNode
{                       //邻接节点结构
    Vertex AdjV;        //int 节点
    PtrToAdjVNode Next; //下一个指向
};

typedef struct Vnode
{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum]; //

typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;
LGraph ReadG(); /* details omitted */
bool IsTopSeq(LGraph Graph, Vertex Seq[]);
int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < G->Nv; j++)
            scanf("%d", &Seq[j]);
        if (IsTopSeq(G, Seq) == true)
            printf("yes\n");
        else
            printf("no\n");
    }
    system("pause");

    return 0;
}

/* Your function will be put here */
LGraph ReadG()
{
    LGraph Gragh = (PtrToGNode)malloc(sizeof(struct GNode));
    int v = 0, e = 0;
    scanf("%d%d", &v, &e);
    Gragh->Ne = e;
    Gragh->Nv = v;
    for (int j = 0; j < MaxVertexNum; j++) //初始化
    {
        Gragh->G[j].FirstEdge = NULL;
    }

    for (int i = 0; i < e; i++)
    {
        int from = 0, to = 0;
        scanf("%d%d", &from, &to);
        from--;
        to--;
        PtrToAdjVNode adj = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode)); //创建节点
        adj->AdjV = to;
        adj->Next = NULL;

        if (Gragh->G[from].FirstEdge)
        {
            adj->Next = Gragh->G[from].FirstEdge;
            Gragh->G[from].FirstEdge = adj;
        }
        else
        {
            Gragh->G[from].FirstEdge = adj;
        }
    }
    return Gragh;
}
/* Your function will be put here */
bool IsTopSeq(LGraph Graph, Vertex Seq[])
{
    Vertex Q[MaxVertexNum] = {0}, tail = -1, head = -1;
    int Inorder[MaxVertexNum] = {0};
    /*计算每一个节点的入度*/
    for (int i = 0; i < Graph->Nv; i++)
    {
        PtrToAdjVNode temp = Graph->G[i].FirstEdge;
        while (temp)
        {
            Inorder[temp->AdjV]++;
            temp = temp->Next;
        }
    }
    /*依次加入队列中*/
    for (int i = 0; i < Graph->Nv; i++)
    {
        Q[++head] = Seq[i] - 1; //入队列
    }
    
    /*队列中元素不为空时*/
    while (head != tail)
    {
        Vertex outv = Q[++tail];
        /*节点的入度必须为0*/
        if (Inorder[outv]!=0)
            return false;
        /*这个节点的下一个节点入度-1*/
        PtrToAdjVNode temp = Graph->G[outv].FirstEdge;
        while(temp)
        {
            Inorder[temp->AdjV]--;
            temp=temp->Next;
        }
    }

    return true;
}







/*
bool IsTopSeq(LGraph Graph, Vertex Seq[])
{
    int Queue[MaxVertexNum], tail = -1, head = -1, OutElement;
    int In_Degree[MaxVertexNum] = {0};
    //先算每一个的入度
    for (int i = 0; i < Graph->Nv; i++)
    {
        PtrToAdjVNode temp = Graph->G[i].FirstEdge;
        for (; temp != NULL; temp = temp->Next)
        {
            In_Degree[temp->AdjV]++;
        }
    }
    //先依次入队
    for (int i = 0; i < Graph->Nv; i++)
    {
        Queue[++head] = Seq[i] - 1; //顶点从0开始存放，需要 -1
    }

    while (tail != head) //当队列非空
    {
        OutElement = Queue[++tail];
        if (In_Degree[OutElement]) //非零
        {
            return false;
        }
        PtrToAdjVNode temp = Graph->G[OutElement].FirstEdge;
        for (; temp != NULL; temp = temp->Next)
        {
            In_Degree[temp->AdjV]--;
            // if (In_Degree[temp->AdjV] < 0)
            // {
            //     return false;
            // }
        }
    }
    return true;
}
*/