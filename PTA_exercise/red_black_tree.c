#include <stdio.h>
#include <stdlib.h>

/*define the node*/
typedef struct Node *tree;
typedef tree ptr;
struct Node
{
    int Element;
    ptr Left;
    ptr Right;
};

/*calculate the absolute value */
int abs(int a)
{
    if (a < 0)
        a = -1 * a;
    return a;
}

/*to build the tree*/
tree Insert(int X, tree T)
{
    if (T == NULL)
    { /* Create and return a one-node tree */
        T = malloc(sizeof(struct Node));
        if (T == NULL)
            printf("Out of space!!!\n");
        else
        {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    }    /* End creating a one-node tree */
    else /* If there is a tree */
    {
        if (abs(X) < abs(T->Element))
        {
            T->Left = Insert(X, T->Left);
        }
        else if (abs(X) > abs(T->Element))
        {
            T->Right = Insert(X, T->Right);
        }
    }
    /* Else X is in the tree already; we'll do nothing */
    return T;
}

/* to check the tree is built right */
void preorder(tree T)
{
    if (T)
    {
        printf("%d  ", T->Element);

        preorder(T->Left);

        preorder(T->Right);
    }
}

/*free tree by postorder*/
void FreeTree(tree T)
{
    if (T)
    {
        FreeTree(T->Left);

        FreeTree(T->Right);

        free(T);

        T = NULL;
    }
}

/*If a node is red, then both its children must be black.*/
int red_with_2black(tree T)
{

    if (!T)
        return 1;
    if (T && T->Element < 0)
    {
        if ((T->Left && T->Left->Element < 0) || (T->Right && T->Right->Element < 0))
            return 0;
    }
    return red_with_2black(T->Left) && red_with_2black(T->Right);
}

int left_equ_right(tree T)
{
    if (NULL == T)
    {
        return 1;
    }
    int l = left_equ_right(T->Left);
    int r = left_equ_right(T->Right);
    if (l == r && l!=-1)
        return T->Element > 0 ? l + 1 : l;
    return -1;
}

/*Calclulate the biggest number of black node that the temp node on the path to leaf node*/
int calculate_black(tree T)
{
    if (!T)
        return 0;
    int left_black = calculate_black(T->Left);

    int right_black = calculate_black(T->Right);

    if (T->Element > 0) /*Black Node*/
    {
        if (left_black > right_black) /*Find the most Black node*/
        {
            return left_black + 1; /* the temp node is black, we need to record it */
        }
        else
        {
            return right_black + 1;
        }
    }
    else /*red node*/
    {
        if (left_black > right_black)
        {
            return left_black;
        }
        else
        {
            return right_black;
        }
    }
}

/*For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.*/
int equal_black(tree T)
{
    if (!T)
        return 1;

    int left_black = calculate_black(T->Left);

    int right_black = calculate_black(T->Right);

    if (left_black == right_black)
        return 1;
    else
        return 0;

    if (T->Left)
        return equal_black(T->Left);
    if (T->Right)
        return equal_black(T->Right);
}

/* to judge the tree */
int judge(tree T)
{
    if (T->Element > 0 && red_with_2black(T)&&left_equ_right(T)!=-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int num = 0;
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        tree T = NULL;
        int number_of_node = 0;
        scanf("%d", &number_of_node);
        for (int j = 0; j < number_of_node; j++)
        {
            int data = 0;
            scanf("%d", &data);
            T = Insert(data, T);
        }
        if (judge(T))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
        FreeTree(T);
    }
    system("pause");
    return 0;
}