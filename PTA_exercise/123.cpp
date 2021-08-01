// #include <bits/stdc++.h>
// using namespace std;
// typedef struct
// {
//     int u, v, w;
//     bool isTreeEdge = false;
// } Edge;
// vector<Edge> edges;
// int n, m, father[505];
// int findfather(int x)
// {
//     if (x == father[x])
//         return x;
//     int a = findfather(father[x]);
//     father[x] = a;
//     return a;
// }
// int main()
// {
//     scanf("%d %d", &n, &m);
//     edges.resize(m);
//     for (int i = 0; i < m; ++i)
//         scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
//     sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.w < b.w; });
//     iota(father, father + n + 1, 0);
//     int sum = 0, num = 0, j = 0;
//     bool flag = true;
//     for (int i = 0; i < edges.size(); i = j)
//     {
//         for (j = i; j < edges.size() && edges[j].w == edges[i].w; ++j)
//             if (findfather(edges[j].u) != findfather(edges[j].v))
//                 edges[j].isTreeEdge = true;
//         for (int k = i; k < j; ++k)
//         {
//             int ua = findfather(edges[k].u), ub = findfather(edges[k].v);
//             if (ua != ub)
//             {
//                 sum += edges[k].w;
//                 father[ua] = ub;
//                 ++num;
//             }
//             else if (edges[k].isTreeEdge)
//                 flag = false;
//         }
//     }
//     if (num == n - 1)
//         printf("%d\n%s", sum, flag ? "Yes" : "No");
//     else
//         printf("No MST\n%d", n - num);
// }