#include <stdio.h>
#include <stdlib.h>

typedef struct Node *ptr;
typedef struct Node *Tree;

struct Node
{
    int data;
    ptr left;
    ptr right;
};

struct node_with_level
{
	int level, data;
} level_list[30];

int postorder[30] = {0};
int inorder[30] = {0};
int level[30] = {0};


int number, node_index = 0, max_level = 1;//记录总数，r的下标, 最大层数

/*计算层数*/
void compute_tree_level(Tree p, int temp_level)
{
	if (!p)return;
    compute_tree_level(p->left, temp_level + 1);
	compute_tree_level(p->right, temp_level + 1);
	level_list[node_index].data = p->data;
	level_list[node_index++].level = temp_level;
	if (temp_level > max_level)max_level = temp_level;
}

void printtree()
{
	int temp_level = 1;
	while (temp_level <= max_level)
	{
		if (temp_level % 2 != 0)//如果不是偶数就翻着打印
		{
			for (int j = number; j >= 0; j--)//如果是奇数就反着打印
			{
				if (level_list[j].level == temp_level && temp_level == 1)//针对第一层
				{
					printf("%d", level_list[j].data);
				}
				if (level_list[j].level == temp_level && temp_level != 1)
				{
					printf(" %d", level_list[j].data);
				}
			}
			temp_level++;
		}
        else//如果为偶数就正着打印
        {
			for (int i = 0; i < number; i++)
			{
				if (level_list[i].level == temp_level)
				{
					printf(" %d", level_list[i].data);
				}
			}
			temp_level++;
		}
	}
}


/*递归构建树*/
Tree build(Tree t, int post_left, int post_right, int in_left, int in_right)
{
    if (post_left > post_right)
        return NULL;
    /*找到根节点在中序中的位置*/
    int root_index = 0;
    int node_data = postorder[post_right];
    while (inorder[root_index] != node_data)
        root_index++;
    /*初始化节点*/
    t = (Tree)malloc(sizeof(struct Node));
    t->data = node_data;
    t->right = t->left = NULL;
    t->left = build(t->left, post_left, post_left + root_index - in_left - 1, in_left, root_index - 1);
    t->right = build(t->right, post_left + root_index - in_left, post_right - 1, root_index + 1, in_right);
    return t;
}
/*
Tree CreateTree(int *inorder, int *postorder, int N) //递归建立树
{ 
    int i;
    int mid; //中间数
    if(N <= 0)
    {
        return NULL;
    }
    Tree T = CreateNode();
    for(i = 0; i < N; i++)
    {
        if(inorder[i] == postorder[N-1])
        {
            mid = i;
            break;
        }
    }
    T->Data = postorder[N-1]; //visit(T)，访问树T
    T->Left = CreateTree(inorder, postorder, mid);
    T->Right = CreateTree(inorder+mid+1, postorder+mid, N-mid-1);
    return T;
}
*/
/*先实现层序遍历，再想办法改进*/
void levelsee(Tree T)
{
    /*创建队列*/
    Tree queue[30];
    int in = 0;
    int out = 0;
    int flag = 0;
    if (T)
    {
        queue[in++] = T;
    }
    while (in > out)
    {
        if (queue[out])
        {
            printf("%d  ", queue[out]->data);
            if (flag)
            {
                queue[in++] = queue[out]->right;
                queue[in++] = queue[out]->left;
            }
            else
            {
                queue[in++] = queue[out]->left;
                queue[in++] = queue[out]->right;
            }
        }
        out++;
    }
}

void preorder(Tree t)
{
    if (t != NULL)
    {
        printf("%d  ", t->data);
        preorder(t->left);
        preorder(t->right);
    }
}

int main()
{

    int num = 0;
    scanf("%d", &num);
    number=num;

    /*读入数据*/
    for (int i = 0; i < num; i++)
        scanf("%d", inorder + i);
    for (int i = 0; i < num; i++)
        scanf("%d", postorder + i);

    Tree T = build(T, 0, num - 1, 0, num - 1);


    compute_tree_level(T,1);
    printtree();

    system("pause");

    return 0;
}