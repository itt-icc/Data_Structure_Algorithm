#include <stdio.h>
#include <stdlib.h>
#define Max_Num_Vertex 1001 //Max_Num_Vertex
#define Max_Num_Edge 100001 //Max_Num_Edge
#define Infinity 100000000  //Infinity

int G[Max_Num_Vertex][Max_Num_Vertex] = {0}; /*Build adjacency matrix*/
int visit[Max_Num_Vertex] = {0};             /*To record weather the point is visited*/
int distance[Max_Num_Vertex] = {0};          /*To record the distance from current point to start point*/

/*Graph structure initialization*/
void Init_graph()
{
    for (int i = 0; i < Max_Num_Vertex; i++)
        for (int j = 0; j < Max_Num_Vertex; j++)
            G[i][j] = Infinity;
}
/*To solve the problem*/
int Solve(int seq[], int num)
{
    int start = seq[1];   //seq[1] is the start point
    Dijkstra(start, num); //use the Dijkstra to find the shortest path to start point
    /*To judge weather the array 'distance' is nondescending sort*/
    for (int i = 1; i < num; ++i)
        if (distance[seq[i]] > distance[seq[i + 1]]) //if descending sort, not a Dijkstra sequence
            return 0;
    return 1;
}
/*Impliment the Dijkstra*/
void Dijkstra(int start, int num)
{
    /*To record the distance from start to start is 0*/
    for (int i = 0; i <= num; ++i)
        distance[i] = G[i][start];
    distance[start] = 0; //The distance from start to start is 0
    visit[start] = 1;    //We visited the start just now

    int cnt = 1;      //To count the number of Verex
    while (cnt < num) //The loop should find the shortest path from  all the vertex to start point
    {
        cnt++;

        /*Find the smallest unknown distance vertex*/
        int minedge = Infinity; //initialize the minedge
        int vertex = -1;        //initialize the smallest unknown distance vertex
        for (int i = 1; i <= num; ++i)
        {
            if (visit[i] == 0 && distance[i] < minedge)
            {
                vertex = i;
                minedge = distance[i];
            }
        }
        visit[vertex] = 1; //We visited the smallest unknown distance vertex just now

        /*For each unknow vertex adjacent from the smallest unknown distance vertex */
        for (int j = 1; j <= num; ++j)
        {
            if (G[j][vertex] == Infinity) //if the distance is Inf which means that the 2 vertex is not connected
                continue;
            if (visit[j] == 0 && distance[vertex] + G[vertex][j] < distance[j]) //if not visited and new distance is smaller
            {
                distance[j] = distance[vertex] + G[vertex][j]; //update the distance from current distance to start point
            }
        }
    }
}
int main()
{
    Init_graph(); /*Graph structure initialization*/

    int v = 0, e = 0; //Number of Vertex and Edge
    scanf("%d%d", &v, &e);

    for (int i = 0; i < e; i++) /*Build adjacency matrix*/
    {
        int from = 0, to = 0, weight = 0;
        scanf("%d%d%d", &from, &to, &weight);
        G[from][to] = weight; //Undirect Gpaph
        G[to][from] = weight;
    }

    int seq[Max_Num_Vertex] = {0}; /*Initialize the test sequence*/
    int k = 0;
    scanf("%d", &k); //Input the number of test sequence
    for (int i = 0; i < k; i++)
    {
        for (int j = 1; j <= v; j++) /*Input the test sequence*/
            scanf("%d", seq + j);
        if (Solve(seq, v))
            printf("YES\n");
        else
            printf("NO\n");
        for (int i = 0; i < Max_Num_Vertex; ++i) /*refresh visit[] to justfy next seqnuence*/
            visit[i] = 0;
    }
    system("pause");
    return 0;
}
