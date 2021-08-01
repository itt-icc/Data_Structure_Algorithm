#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max_num_vertex 1002
#define INF 100000

int num_vertex = 2;
int num_edge = 0;
int Graph[max_num_vertex][max_num_vertex] = {0};
const int start_point = 0;
const int end_point = 1;

typedef char name[4]; //名称
struct name_vertex
{
    int vertex;
    name Name;
};
struct name_vertex map[max_num_vertex];

void init()
{
    for (int i = 0; i < max_num_vertex; ++i)
        for (int j = 0; j < max_num_vertex; ++j)
            Graph[i][j] = INF;

    for (int i = 0; i < max_num_vertex; ++i)
        map[i].vertex = i;
}

/*找到字符串对应的顶点*/
int find_vertex(char *name)
{
    for (int i = 0; i < num_vertex; ++i)
        if (strcmp(map[i].Name, name) == 0) //找到了节点
            return i;
    strcpy(map[num_vertex].Name, name);
    return num_vertex++;
}
int BFS(int path[])
{
    /*创建队列*/
    int Queue[max_num_vertex] = {0};
    /*访问标记*/
    int visit[max_num_vertex] = {0};

    int front = 0, rear = 0;
    Queue[rear++] = start_point;
    visit[start_point] = 1;
    while (front != rear)
    {
        int current_v = Queue[front++]; //取出一个节点

        if (current_v == end_point)
            return 1; //如果找到了最后的节点

        /*遍历当前节点的所有节点*/
        for (int i = 0; i < num_vertex; ++i)
        {
            // if (Graph[current_v][i] == INF) //说明没连同
            //     continue;
            printf("G[%d][%d]=%d\n",current_v,i,Graph[current_v][i]);
            if (visit[i] == 0&&Graph[current_v][i]!=INF)
            {
                path[i] = current_v;
                visit[i] = 1;
                Queue[rear++] = i;
            }
        }
    }
    return 0;
}

int main()
{
    init();
    /*读入*/
    scanf("%s %s %d", map[start_point].Name, map[end_point].Name, &num_edge);
    for (int i = 0; i < num_edge; ++i)
    {
        name from, to;
        int weight = 0;
        scanf("%s %s %d", from, to, &weight);
        /*插入边*/
        int v1 = find_vertex(from);
        int v2 = find_vertex(to);
        Graph[v1][v2] = weight;
    }
    /*创建搜索路径*/
    int path[max_num_vertex] = {0};
    //Edmonds_Karp最大流算法
    int maxflows = 0;
    while (BFS(path))
    {
        int flow = INF;
        for (int v = end_point; v != start_point; v = path[v])
        {
            if (flow > Graph[path[v]][v]) //注意 from to
                flow = Graph[path[v]][v];
        }
        maxflows += flow;
        //处理残留图
        for (int v = end_point; v != start_point; v = path[v])
        {
            Graph[path[v]][v] -= flow;
            if (Graph[path[v]][v] <= 0)
            {
                int abs = -Graph[path[v]][v];
                if (Graph[v][path[v]] == INF) //说明没有联通
                    Graph[v][path[v]] = abs;
                else
                    Graph[v][path[v]] += abs; //反向加上去
                Graph[path[v]][v] = INF;//断开操作
            }
        }
    }
    printf("%d", maxflows);
    system("pause");
    return 0;
}
