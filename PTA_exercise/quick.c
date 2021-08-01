/*https://blog.csdn.net/zhuiyisinian/article/details/105902862?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2.control*/

#include <stdio.h>
typedef int rank;

void Partition(int A[], int low, int high);


/*Swap*/
void Swap(rank *a, rank *b)
{
    rank temp = *a;
    *a = *b;
    *b = temp;
}

/*Quick sort*/
void Q_sort(rank A[], int left, int right)
{
    int i = left;
    int j = right - 1;
    rank pivot = A[right]; /* select pivot */
    if (left < right)      /*if left >= right , then  end */
    {
        while (i <= j)
        {
            if (A[i]>= pivot && A[j] <= pivot)
            Swap(&A[i], &A[j]); /* adjust partition */
            // {
            //     rank temp = A[i];
            //     A[i] = A[j];
            //     A[j] = temp;
            // }

            while (A[i] < pivot)
                i++; /* scan from left */
            while (A[j] > pivot)
                j--; /* scan from right */
        }
        Swap(&A[i], &A[right]);  /* restore pivot */
        // rank temp = A[i];
        // A[i] = pivot;
        // A[right] = temp;
        Q_sort(A, left, i - 1);  /* recursively sort left part */
        Q_sort(A, i + 1, right); /* recursively sort right part */
    }
}
int main()
{
	int i;
	int a[21] = {20, 19, 18, 17, 16, 8, 1, 11, 12, 4, 13, 15, 9, 0, 14, 3, 10, 5, 2, 7, 6};
	Q_sort(a, 0, 20);
	for(i=0; i<21; i++)
		printf("%d ", a[i]);
    system("pause");
	return 0;
} 

void Partition(int A[], int low, int high)
{
    int i = low;
    int j = high-1;
    int pivot = A[high];

    if(low < high)
    {
	    while(i <= j)
	    {
	        if(A[i] >= pivot && A[j] <= pivot)
	        {
	        	int temp;
	        	temp = A[i];
	        	A[i] = A[j];
	        	A[j] = temp;
	        }

	        while(A[i] < pivot)
	            i++;
	        while(A[j] > pivot)
	            j--;
	
	    }
	    int temp;
	    temp = A[i];
	    A[i] = pivot;
	    A[high] = temp;
	    
	    Partition(A, low, i-1);
	    Partition(A, i+1, high);    	
    }
}


