#include <stdio.h>
#include <stdlib.h>
#define MAXN 100

int HashTable[MAXN];   /* 用来读取已经建立好的散列表 */
int reHashTable[MAXN]; /* reHashTable数组用来模拟建立散列表过程 */

int Find(cell, N)
{ /* 找到cell应该插到哪里 */
    int pos;
    pos = cell % N;

    while (reHashTable[pos] != -1)
    { /* 只要这个位置不空就往下走 */
        ++pos;
        if (pos >= N)
            pos = pos % N; /* 超出表的长度，就回头从0开始 */
    }
    return pos; /* pos一定是个空位置 */
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int N, i, cell, positiveN = 0;
    scanf("%d\n", &N);

    int position[100]; /* position数组用来存储某个数字在表中的位置 */

    for (i = 0; i != N; ++i)
    { /* 初始化position和reHashtable数组 */
        position[i] = -1;
        reHashTable[i] = -1;
    }

    for (i = 0; i != N; ++i)
    {
        scanf("%d", &HashTable[i]); /* 读入表 */
        if (HashTable[i] >= 0)
        {
            position[HashTable[i]] = i;
            ++positiveN;
        }
    }

    qsort(HashTable, N, sizeof(int), compare); /* 对表中的数字从小到大排序 */
    int pos, num = 0;
    int Inserted[MAXN] = {0}; /* 用来表示某个数字数字是否已经被插入新的散列表里了 */
    while (num < positiveN)
    { /* 重新建表 */
        for (i = 0; i != N; ++i)
        {
            if (HashTable[i] >= 0 && !Inserted[i])/*必须得是正数*/
            {                                /* HashTable[i]大于0而且没有被插入过 */
                pos = Find(HashTable[i], N); /* 找到HashTable[i]应该插到哪里 */
                if (pos == position[HashTable[i]])/*这个位置应该等于最终的位置*/
                {
                    ++num;
                    reHashTable[pos] = HashTable[i]; /* 把这个数字插入 */
                    Inserted[i] = 1;    

                    printf("%d", HashTable[i]);

                    /*控制输出空格*/
                    if (num <= positiveN - 1)
                        printf(" ");
                    break;
                }
            }
        }
    }
    return 0;
}
