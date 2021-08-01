#include <stdio.h>
long recursion(int n);
int main()
{
    printf("%ld\n", recursion(4));
}
long recursion(int n)
{
    long temp_result;
    if (n < 0)
    {
        printf("n<0,input error!\n");
    }
    else if (n == 0 || n == 1)
    {
        temp_result = 1;
    }
    else
    {
        temp_result = recursion(n - 1) * n;
    }
    return temp_result;
}
