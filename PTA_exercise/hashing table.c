#include <stdio.h>
#define maxn 65535
int main() {
    int n;
    scanf("%d", &n);
    int i, j, num, min, k = 0, cmp;
    int data[maxn], degree[maxn], cmpdegree[maxn], a[maxn];
    for (i = 0; i < n; i++) {
    //读入输入数据并计算优先级
        scanf("%d", &num);
        data[i] = num;
        degree[i] = (i - num % n + n) % n;
        if (num < 0)
            degree[i] = -1;
        cmpdegree[i] = degree[i];
    }
    while (k < n) {
        min = -1;//最终仍为-1则表示表中除了空位都已经被输出了
        for (i = 0; i < n; i++)
            if (degree[i] == 0)//0表示可以输出了，同时过滤了不能被输出的和已经输出过的数据
                if (min == -1 || data[i] < min)//寻找其中的最小值
                    min = data[i];
        for (i = 0; i < n; i++) //寻找此最小值所在的位置，其实可以在上个循环中新声明一个变量记录i
            if (data[i] == min)
                break;
        for (j = 0; j < n; j++) {
            cmp = (j - i + n) % n;
            if (degree[j] >= 0 && cmp <= cmpdegree[j])//处理优先级
                degree[j]--;
        }
        a[k] = min;//将结果放入数组中最后一起输出
        k++;//k可以同时充当一个标记的作用
    }
    for (k = 0; k < n; k++) {
        if (a[k] == -1)
            break;//读到-1表示后面对应的都是哈希表中的空位
        if (k != 0)
            printf(" ");
        printf("%d", a[k]);
    }
    return 0;
}
