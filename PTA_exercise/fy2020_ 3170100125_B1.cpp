/* Author: Zhang Youchao;  ID: 3170100125;  No.01 */

#include <stdio.h>
#define MAX 99999 /*Use to malloc a large array*/

typedef struct node Link;
typedef Link *P;
struct node
{
    int address;
    int data;
    int next;
} Place[MAX];

int main()
{
    int head1, head2 = 0;
    int num = 0;
    /*to input data*/
    scanf("%d %d %d", &head1, &head2, &num);
    for (int i = 0; i < num; ++i)
    {
        int address, data, next = 0;
        scanf("%d %d %d", &address, &data, &next);
        Place[address].address = address;
        Place[address].data = data;
        Place[address].next = next;
    }
    Link l1[MAX]; /*this should be more large to load more data*/
    Link l2[MAX];
    int cnt1 = 0;
    int cnt2 = 0;
    /*Initialize two lists*/
    /*Connect the two lists in the order that they first meet, so there is no need to sort them*/
    for (; head1 != -1;)
    {
        l1[cnt1].address = Place[head1].address;
        l1[cnt1].data = Place[head1].data;
        l1[cnt1].next = Place[head1].next;
        head1 = Place[head1].next;
        cnt1++;
    }
    for (; head2 != -1;)
    {
        l2[cnt2].address = Place[head2].address;
        l2[cnt2].data = Place[head2].data;
        l2[cnt2].next = Place[head2].next;
        head2 = Place[head2].next;
        cnt2++;
    }
    /*The main difficulty is how to intersperse output*/
    /*Inorder to avoid to swap 2 large array just campare the length,the small will be reversed*/
    if (cnt2-- < cnt1--)
    {
        printf("%05d %d", l1[0].address, l1[0].data); /*Output the address and data of the current element*/
        for (int i = 1; i <= cnt1; ++i)
        {
            printf(" %05d\n", l1[i].address);             /*Output the address of the next element*/
            printf("%05d %d", l1[i].address, l1[i].data); /*Output the address and data of the current element*/
            /*Output small elements in reverse order*/
            if (!((i + 1) % 2) && cnt2 >= 0)
            {
                printf(" %05d\n", l2[cnt2].address);                /*Output the address of the next element*/
                printf("%05d %d", l2[cnt2].address, l2[cnt2].data); /*Output the address and data of the current element*/
                cnt2--;
            }
        }
        printf(" -1"); /*Mark of the end of the address*/
    }
    else
    {
        printf("%05d %d", l2[0].address, l2[0].data);
        for (int i = 1; i <= cnt2; ++i)
        {
            printf(" %05d\n%05d %d", l2[i].address, l2[i].address, l2[i].data);
            if (!((i + 1) % 2) && cnt1 >= 0)
            {
                printf(" %05d\n%05d %d", l1[cnt1].address, l1[cnt1].address, l1[cnt1].data);
                cnt1--;
            }
        }
        printf(" -1");
    }

    return 0;
}