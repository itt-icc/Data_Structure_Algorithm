#include <stdio.h>
#include <string.h>
#define Maxnum 1000000

typedef char name[9];
typedef struct person *rank;
struct person /*the struct to store a person*/
{
    int age;
    name Name;
    int worth;
};
rank Rank[Maxnum];            //to make a array to store the address of people
struct person Person[Maxnum]; /*to store people*/

void Swap(rank *a, rank *b)/*Swap*/
{
    rank temp = *a;
    *a = *b;
    *b = temp;
}

int cmp(rank a, rank b)/*compare by worth -> age->Name*/
{
    if (a->worth != b->worth)
        return a->worth > b->worth;/*bigger net worth*/
    else if (a->age != b->age)
        return a->age < b->age;    /*small age is bigger*/
    return strcmp(a->Name, b->Name) < 0;/*small name is bigger*/
}

/*Quick sort*/
void Q_sort(rank A[], int left, int right)
{
    int i = left;
    int j = right - 1;
    int pivot = right; /* select pivot */
    if (left < right)  /*if left >= right , then  end */
    {
        for(;;)
        {
            while (i <= right - 1 && !cmp(A[i], A[pivot]))
                i++; /* scan from left */
            while (j >= left && cmp(A[j], A[pivot]))      
                j--; /* scan from right */

            if (i < j)
                Swap(&A[i], &A[j]); /* adjust partition */
            else
                break;
        }
        Swap(&A[i], &A[right]);  /* restore pivot */
        Q_sort(A, left, i - 1);  /* recursively sort left part */
        Q_sort(A, i + 1, right); /* recursively sort right part */
    }
}
int main()
{
    int numPerson = 0; //number of people
    int numCase = 0;   //number of cases
    scanf("%d %d", &numPerson, &numCase);
    for (int i = 0; i < numPerson; ++i) //to read data & combine rank to person
    {
        scanf("%s %d %d", Person[i].Name, &Person[i].age, &Person[i].worth);
        Rank[i] = Person + i; //store the address
    }
    Q_sort(Rank, 0, numPerson - 1); //sort the Rank by net worth
    /*cases*/
    for (int i = 1; i <= numCase; ++i)
    {
        int num, lower, upper, cnt = 0;
        scanf("%d %d %d", &num, &lower, &upper);
        printf("Case #:%d\n", i);
        for (int k = numPerson - 1; k >= 0 && cnt < num; --k) /*from biggest to smallest*/
        {
            if (Rank[k]->age >= lower && Rank[k]->age <= upper)
            {
                ++cnt;
                printf("%s %d %d\n", Rank[k]->Name, Rank[k]->age, Rank[k]->worth);
            }
        }
        if (!cnt)
            printf("None\n");
    }
    system("pause");
    return 0;
}