
#include <iostream>
#include <vector>
using namespace std;
int const maxn = 100010;
struct node
{
    int first;
    int data ;
    int next;
} Node[maxn];
int main()
{
    int h1, h2, n, num, a, d, b;
    vector<node> v1, v2;
    cin >> h1 >> h2 >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        Node[num].first = num;
        cin >> Node[num].data >> Node[num].next;
    }
    while (h1 != -1)
    {
        v1.push_back(Node[h1]);
        h1 = Node[h1].next;
    }
    while (h2 != -1)
    {
        v2.push_back(Node[h2]);
        h2 = Node[h2].next;
    }
    if (v1.size() < v2.size())
        swap(v1, v2);
    int cnt = v2.size() - 1;
    printf("%05d %d", v1[0].first, v1[0].data);
    for (int i = 1; i < v1.size(); i++)
    {
        printf(" %05d\n%05d %d", v1[i].first, v1[i].first, v1[i].data);
        if (i % 2 == 1 && cnt >= 0)
        {
            printf(" %05d\n%05d %d", v2[cnt].first, v2[cnt].first, v2[cnt].data);
            cnt--;
        }
    }
    printf(" -1");
    return 0;
}
