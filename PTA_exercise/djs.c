#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define X 10000     //正无穷
#define VertexNum 7 //顶点
#define EdgeNum 9   //边

int Graph[VertexNum][VertexNum] =
    //0  1  2  3  4  5  6
    {
        X, X, X, X, X, X, X, //0
        X, X, 6, 3, X, X, X, //1
        X, X, X, X, 5, X, X, //2
        X, X, 2, X, 3, 4, X, //3
        X, X, X, X, X, X, 3, //4
        X, X, X, X, 2, X, 5, //5
        X, X, X, X, X, X, X  //6
};

int Visited[VertexNum];  //是否看过
int path[VertexNum];     //路径
int Distance[VertexNum]; //距离

void Dijkstra(int Begin)
{
    Visited[Begin] = 1;
    for (int i = 1; i < VertexNum; i++) //记录到begin的距离
        Distance[i] = Graph[Begin][i];
    Distance[Begin] = 0; //对于自身就是0

    int v = 1; //记录顶点数
    while (v < VertexNum - 1)
    {
        v++;
        /*找到最小的节点V = smallest unknown distance vertex;*/
        int MinEdge = X;
        int Vertex = -1;
        
        for (int j = 1; j < VertexNum; j++)
            if (Visited[j] == 0 && MinEdge > Distance[j])
            {
                Vertex = j;
                MinEdge = Distance[j];
            }

        /*看了这个节点T[ V ].Known = true;*/
        Visited[Vertex] = 1;

        /*each W adjacent to V */
        for (int j = 1; j < VertexNum; j++)
        {
            if (Graph[Vertex][j] == X)//保证是连同的
                continue;

            if (Visited[j] == 0)//抱枕没有访问过
                if (Distance[Vertex] + Graph[Vertex][j] < Distance[j]) //如果没有看过而且距离更小,这里可以直接实现查看距离，因为无穷大不满足小于号
                {
                    Distance[j] = Distance[Vertex] + Graph[Vertex][j]; //当前点的距离
                    path[j] = Vertex;
                }
        }
    }
}

void main()
{

    int i;
    int k;
    // clrscr();
    for (i = 0; i < VertexNum; i++)
    {
        Visited[i] = 0;
        path[i] = 1;
    }
    Dijkstra(1);
    printf("\n\nAll Path-------------------------\n");

    for (i = 2; i < VertexNum; i++) //printf("%5d",Visited[i]);
    {
        printf("[%d] ", Distance[i]);
        k = i;
        do
        {
            printf("%d<--", k);
            k = path[k];
        } while (k != 1);
        printf("1 \n");
    }
    system("pause");
}