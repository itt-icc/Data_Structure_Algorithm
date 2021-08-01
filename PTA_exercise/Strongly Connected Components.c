#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10 /* maximum number of vertices */
typedef int Vertex;    /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode
{
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode
{
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG()
{ /* details omitted */
    int a, b;
    Graph G = (Graph)malloc(sizeof(struct GNode));
    scanf("%d%d", &G->NumOfVertices, &G->NumOfEdges);
    G->Array = (PtrToVNode *)malloc(sizeof(PtrToVNode) * G->NumOfVertices);
    
    for (int i = 0; i < G->NumOfVertices; i++)
    {
        G->Array[i] = NULL;
    }
    for (int i = 0; i < G->NumOfEdges; i++)
    {
        scanf("%d%d", &a, &b);
        PtrToVNode p = (PtrToVNode)malloc(sizeof(struct VNode));
        p->Vert = b;
        p->Next = G->Array[a];
        G->Array[a] = p;
    }
    return G;
}

void PrintV(Vertex V)
{
    printf("%d ", V);
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V));

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents(G, PrintV);
    system("pause");
    return 0;
}

/* Your function will be put here */

/*
找图的强连通分量，题目中的建图的函数没给出定义，实际使用邻接表。
由于边数很少可以考虑先求所有边可达矩阵，mp[i][j]为1，
表示存在i到j的路径，可以用邻接矩阵的n次方求得。然后排着判断即可，
一个强连通分量里的点必定都是相互可达的。
*/

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V))
{
    int aj_matrix[MaxVertices][MaxVertices] = {0}; //ajacent matrix
    int vertex_number = G->NumOfVertices;
    int visited[MaxVertices] = {0};
    int connect = 1;

    /*build ajacent matrix*/
    for (int i = 0; i < vertex_number; ++i)
        for (PtrToVNode ptr = G->Array[i]; ptr != NULL; ptr = ptr->Next)
            aj_matrix[i][ptr->Vert] = connect;

    /*connect all the vertex*/
    for (int i = 0; i < vertex_number; ++i)
        for (int j = 0; j < vertex_number; ++j)
            for (int k = 0; k < vertex_number; ++k)
                if (aj_matrix[i][k] * aj_matrix[k][j] == connect)
                    aj_matrix[i][j] = connect;

    /*print all the strongly connect*/
    for (int i = 0; i < vertex_number; ++i)
        if (!visited[i])//very critical
        {
            visit(i);
            visited[i] = 1;
            for (int j = 0; j < vertex_number; ++j)
                if (aj_matrix[i][j] * aj_matrix[j][i] == connect&&!visited[j])
                {
                    visited[j] = 1;
                    visit(j);
                }
            printf("\n");
        }
}