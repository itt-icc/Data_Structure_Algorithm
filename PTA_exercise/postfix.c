#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix(char *expr);

int main()
{
	ElementType v;
	char expr[Max_Expr];
	gets(expr);
	v = EvalPostfix(expr);
	if (v < Infinity)
		printf("%f\n", v);
	else
		printf("ERROR\n");
	system("pause");
	return 0;
}

ElementType EvalPostfix(char *expr)
{
	/*定义堆栈和栈顶指针*/
	double Stack[30]= { 0 };
	int top = 0;

	/*定义一个字符串数组用于存放操作数*/
	char num[10];

	int i = 0;
	while(expr[i]!='\0')
	{
		/*去除开头的空格*/
		while (expr[i] == ' ')
		{
			i++;
			printf("1 i= %d\n", i);
		}
		
		/*数字字符转换为浮点数，存放在栈顶*/
		int j = 0;
		while ((expr[i] == '.') || (expr[i] <= '9'&&expr[i] >= '0') || (expr[i] == '-' && (expr[i + 1] != ' '&&expr[i + 1] != '\0')))//要考虑到复数
		{
			num[j] = expr[i];
			printf("2 i= %d\n", i);
			j++;
			i++;
		}
		/*      长串数字   | 只有一个数字       */
		if (expr[i] == ' ' || (top == 0 && expr[i + 1] == '\0'))
		{
			Stack[top] = atof(num);
			/*将字符串清零*/
			for (int k = 0; k < sizeof(num) / sizeof(num[0]); k++)
				num[k] = 0;
			i++;
			top++;
			printf("3 i= %d\n", i);
		}

		/*四则运算*/
		else if (expr[i]=='+'|| expr[i] == '-' || expr[i] == '*' || expr[i] == '/')//会多一个运算数(expr[i+1]==' '||expr[i+1]=='\0')
		{
			switch (expr[i])
			{
			case '+':Stack[top - 2] = Stack[top - 2] + Stack[top - 1];break;
			case '-':Stack[top - 2] = Stack[top - 2] - Stack[top - 1];break;
			case '*':Stack[top - 2] = Stack[top - 2] * Stack[top - 1];break;
			case '/':if (Stack[top - 1] == 0)return Infinity;
				Stack[top - 2] = Stack[top - 2] / Stack[top - 1];break;
			default:break;
			}
			printf("result = %.3f \n", Stack[top - 2]);
			i++;
			printf("4 i= %d\n", i);
			top--;
		}
	}
	if (!top) return Infinity;
	return Stack[top-1];
}
