#include <stdio.h>
#define MAX 10000
int S[MAX] = {-1};

void check(int n){
    int count = 0;
	for (int i = 1; i <= n; i++)
		if (S[i] < 0)
			count++;
	if (count == 1)
		printf("The network is connected.");
	else if (count > 1)
		printf("There are %d components.", count);
}

int find(int x, int S[])
{
    if (S[x] < 0)
        return x;
    else
        return S[x] = find(S[x], S);
}
// int find1(int x, int s[])
// {
// 	int root, trail, lead;
// 	for (root = x; s[root] > 0; root = s[root])
// 		;
// 	for (trail = x; trail != root; trail = lead)
// 	{
// 		lead = s[trail];
// 		s[trail] = root;
// 	}
// 	return root;
// }
void Union(int S[], int root1, int root2)
{
    if (S[root1] < S[root2])
    {
        S[root1] += S[root2];
        S[root2] = root1;
    }
    else
    {
        S[root2] += S[root1];
        S[root1] = root2;
    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    for(int i=1;i<=n;i++)
    {
        S[i]=-1;
    }
    getchar();

    char op;
    int a, b = 0;
    scanf("%c", &op);
    while (op != 'S')
    {
        scanf("%d%d", &a, &b);
        if (op == 'I')
        {
            // printf("op=%c a=%d b=%d\n", op, a, b);
            Union(S, find(a, S), find(b, S));
        }
        else
        {
            // printf("op=%c a=%d b=%d\n", op, a, b);
            if (find(a, S) == find(b, S))
                printf("yes\n");
            else
                printf("no\n");
        }
        getchar();
        scanf("%c", &op);
    }
    check(n);
    system("pause");
    return 0;
}
