// #include "minishell.h"

// typedef struct s_tree
// {
//     int value;
//     char *name;
//     struct s_tree *right;
//     struct s_tree *left;
// } t_tree;


// t_tree *nood_tree(int value, char *name)
// {
//     t_tree *result;

//     result = malloc(sizeof(t_tree));
//     if (result != NULL)
//     {
//         result->value = value;
//         result->name = name;
//         result->right = NULL;
//         result->left = NULL;
//     }
//     return (result);
// }

// int main()
// {
//     t_tree *node1 = nood_tree(1, "node1");
//     t_tree *node2 = nood_tree(2, "node2");
//     t_tree *node3 = nood_tree(3, "node3");
//     t_tree *node4 = nood_tree(4, "node4");
//     t_tree *node5 = nood_tree(5, "node5");
//     t_tree *node6 = nood_tree(6, "node6");

//     node1->right = node3;
//     node1->left = node2;
//     node2->right = node5;
//     node2->left = node4;
//     node3->right = node6;

//     printf("%s : %d \n", node1->name , node1->value);
//     printf("%s : %d \n", node1->left->name , node1->left->value);
//     printf("%s : %d \n", node1->left->left->name , node1->left->left->value);
// }