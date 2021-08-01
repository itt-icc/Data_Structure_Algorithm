#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	false,
	true
} bool;

#define MAXN 1002
#define INF 999999999

typedef int Vertex;		//顶点
typedef char name[4];	//名称
typedef int WeightType; //权重

typedef struct AdjVNode
{ //第二个node
	Vertex V;
	WeightType Capicity;
	struct AdjVNode *NextEdge; //下一个边
} AdjVNode;

typedef struct VNode
{ //第一个node
	name Name;
	AdjVNode *FirstEdge;
} VNode;

typedef struct Graph
{
	VNode site[MAXN]; //总线
	int Nv;			  //节点的数量
	int Ne;			  //边地数量
} graph;

const Vertex startpoint = 0; //起试顶点
const Vertex endpoint = 1;	 //结束顶点
// 通过名字获得顶点编号

Vertex getVertex(graph *G, const char *name)
{
	// 顺序遍历，找到就返回
	for (Vertex i = 0; i < G->Nv; i++) //对于所有地顶点
		if (!strcmp(G->site[i].Name, name))
			return i;
	// 未找到则添加
	strcpy(G->site[G->Nv].Name, name);
	// *(G->site[G->Nv].Name)=name;
	return G->Nv++; //注意此时返回最后一个，同时点的数量需要扩充一个
}

// 通过顶点编号找对应的边
AdjVNode *getEdge(graph *G, Vertex v, Vertex w)
{
	AdjVNode *p = NULL;
	for (p = G->site[v].FirstEdge; p != NULL; p = p->NextEdge)
		if (p->V == w)
			break;
	return p;
}

// 初始化图
graph *initGraph()
{
	graph *G = (graph *)malloc(sizeof(graph));

	G->Nv = 2;
	for (int i = 0; i < MAXN; i++)
	{
		G->site[i].Name[0] = '\0';
		G->site[i].FirstEdge = NULL;
	}
	return G;
}

// 插入边
void insertEdge(graph *G, Vertex v1, Vertex v2, WeightType capicity)
{
	// 分配边的内存并赋值
	AdjVNode *p = (AdjVNode *)malloc(sizeof(AdjVNode)); //先初始化一个新的邻接点
	p->V = v2;
	p->Capicity = capicity;
	// 头插法插入表中
	p->NextEdge = G->site[v1].FirstEdge;
	G->site[v1].FirstEdge = p;
}

// BFS寻找路径
bool searchPath(graph *G, Vertex path[])
{
	Vertex Queue[MAXN]; //创建队列

	int front = 0, rear = 0;
	bool *visited = (bool *)calloc(G->Nv, sizeof(bool));

	Queue[rear++] = startpoint; //把起始点放入队列中
	visited[startpoint] = true; //七十点当作已经访问过

	while (front != rear) //如果队列不为空
	{
		Vertex v = Queue[front++]; //从头部拿出一个节点

		if (v == endpoint) //如果找到了最后的节点
			return true;

		for (AdjVNode *p = G->site[v].FirstEdge; p != NULL; p = p->NextEdge) //访问所有邻接的点
			if (!visited[p->V] && p->Capicity > 0)							 //如果没有被访问过，而且权重大于0
			{
				path[p->V] = v;		  //当前节点的上一个
				visited[p->V] = true; //已经访问过
				Queue[rear++] = p->V; //当前节点放到队列中去
			}
	}
	return false; //当前路径找不到
}

int main()
{
	Vertex path[MAXN];		//创建路径
	graph *G = initGraph(); //初始化图
	// 读入并建图
	scanf("%s %s %d", G->site[0].Name, G->site[1].Name, &G->Ne);

	for (int i = 0; i < G->Ne; i++)
	{
		name source, destination; //出发地，目的地
		int capacity;			  //权重

		scanf("%s %s %d", source, destination, &capacity);

		insertEdge(G, getVertex(G, source), getVertex(G, destination), capacity); //插入新的边
	}

	// Edmonds_Karp最大流算法
	int maxflow = 0;
	// 寻找增广路径
	while (searchPath(G, path)) //此处已经添加了路径  直到找不到路径
	{
		int flow = INF;
		// 求路径流量

		for (Vertex v = endpoint; v != startpoint; v = path[v])//从后往前,必须要这样
		{
			AdjVNode *p = getEdge(G, path[v], v);
			if (flow > p->Capicity)
				flow = p->Capicity;
		}

		maxflow += flow;

		// 残留图
		for (Vertex v = endpoint; v != startpoint; v = path[v])
		{
			AdjVNode *p = getEdge(G, path[v], v);
			p->Capicity -= flow;
			// 添加回边
			if (p->Capicity < 0)
			{
				AdjVNode *q = getEdge(G, v, path[v]);
				if (q == NULL)
					insertEdge(G, v, path[v], -p->Capicity);
				else//说明是有一条边的
					q->Capicity -= p->Capicity;
				p->Capicity = 0;
			}
		}
	}

	printf("%d", maxflow);

	system("pause");
	return 0;
}
