#include <stdio.h>
#include <stdlib.h>

/*define the node*/
typedef struct Node *tree;//define the tree
typedef tree ptr;         //define the pointer
struct Node               //define the node
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

/* to check the whether the tree is built right */
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
        T = NULL;//let the pointer point to NULL
    }
}

/*
******************************************************
************Use 2,4,5 to check the tree***************
****************************************************** 
*/
/*According to 3 The root should be black node.*/
int checkroot(tree T)
{
    if (!T)//black node
        return 1;
    else if (T->Element > 0)//black node
        return 1;
    else//red node
        return 0;
}
/*
According to 4 : If a node is red, then both its children must be black.
*/
int red_with_2black(tree T)
{
    if (T)
    {
        if (T->Element < 0)//red node
        {
            if (T->Left)
            {
                if (T->Left->Element < 0)//red node
                    return 0;
            }
            if (T->Right)
            {
                if (T->Right->Element < 0)//red node
                    return 0;
            }
        }
        return red_with_2black(T->Left);
        return red_with_2black(T->Right);
    }
    else//NULL black node
        return 1;
}

/*According to 5 :For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.
So a red black tree can make the black node balanced, the leftchild and the rightchild must have the same depth(we just care about the black node)*/
int equal_black(tree T)
{
    if (!T)
        return 1;

    /*find the leftchild and rightchild black node depth*/
    int left_black = find_blackNode_depth(T->Left);
    int right_black = find_blackNode_depth(T->Right);
    /*the black node depth must equal to each other*/
    if (left_black == right_black)
        return 1;
    else
        return 0;

    /*Recursion*/
    if (T->Left)
        return equal_black(T->Left);
    if (T->Right)
        return equal_black(T->Right);
}
/*Find the deepth of node T to the leaf And the deepth is calculate by the black node.
Post-order traversal, find the black node height of the current tree.*/
int find_blackNode_depth(tree T)
{
    if (!T)
        return 0;
    int left_black = find_blackNode_depth(T->Left);
    int right_black = find_blackNode_depth(T->Right);

    if (T->Element > 0) /*Black Node*/
    {
        if (left_black > right_black) /*The bigger number is the depth,rather than the smaller,so we should return the bigger one*/
        {
            return left_black + 1;//add 1
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
/*
******************************************************
************************END***************************
****************************************************** 
*/


/* to judge the tree */
int judge(tree T)
{
    if (checkroot(T) && red_with_2black(T) && equal_black(T))
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
    int num = 0;//The number of testing tree
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
        if (judge(T))//To judge the temp tree
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
        FreeTree(T); //To free the memory
    }
    system("pause");
    return 0;
}