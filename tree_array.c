/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:00:51 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/24 19:05:48 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree *new_ast(t_gram value)
{
    t_tree *node = malloc(sizeof(t_tree));
    if (!node)
        return NULL;
    node->value = value;
    node->array = init_arr();
    return node;
}

t_arr *merge_arrays(t_arr *arr1, t_arr *arr2)
{
    t_arr *merged = init_arr();
    // Insert elements of arr1
    for (int i = 0; i < arr1->used; i++)
        insert_arr(merged, ((char *)arr1->arr + i * arr1->elem_size));

    // Insert elements of arr2
    for (int i = 0; i < arr2->used; i++)
        insert_arr(merged, ((char *)arr2->arr + i * arr2->elem_size));

    return merged;
}

t_tree *create_ast_node(t_gram value)
{
    t_tree *node = malloc(sizeof(t_tree));
    if (!node)
        return NULL;
    node->value = value;
    node->array = init_arr();
    return node;
}

void insert_arr(t_arr *arr, void *elem)
{
    if (arr->used == arr->size)
    {
        arr->size *= 2;
        arr->arr = realloc(arr->arr, arr->size * arr->elem_size);
    }
    memcpy((char *)arr->arr + arr->used * arr->elem_size, elem, arr->elem_size);
    arr->used++;
}

void free_ast(t_tree *node)
{
    if (node)
    {
        // Free the elements inside the array
        if (node->array)
        {
            for (int i = 0; i < node->array->used; i++)
            {
                // Add custom logic if the array stores more than simple pointers
            }
            free(node->array->arr); // Free the dynamic array
            free(node->array);      // Free the array structure
        }
        free(node);  // Free the AST node itself
    }
}


t_arr *init_arr(void)
{
    t_arr *arr = malloc(sizeof(t_arr));
    arr->size = 10; 
    arr->used = 0;
    arr->elem_size = sizeof(void *);  // Adjust this based on the data type you store
    arr->arr = malloc(arr->size * arr->elem_size);
    return arr;
}
