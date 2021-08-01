#include<stdio.h>
#include<stdlib.h>
int max = 0, length = 0, num = 0;
int Check(int *seq);
int main()
{
	scanf("%d%d%d", &max, &length, &num);
	int seq[100]={-1};

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < length; j++)
		{
			scanf("%d", &seq[j]);
		}


		int flag = Check(seq);
		if (flag)printf("YES\n");
		else printf("NO\n");
	}


	system("pause");
	return 0;
}

int Check(int seq[])
{

	int flag = 1;
	int list[100]={-1};
	for (int i = 0; i < length; i++)
		list[i] = i + 1;
	int stack[100]={-1};
	int top = 0;
	int j = 0;
	for (int i = 0; i < length; i++)
	{

		while (j<length && list[j] <= seq[i])
		{

			if (top == max) {//超出堆栈范围
				flag = 0;
				break;
			}
			stack[top++] = list[j++];
		}
		if (stack[top-1] != seq[i])//如果堆栈中第一个元素与当前元素对不上
		{
			flag = 0;
			break;
		}

		top--;//pop出一个元素
	}
	return flag;

}