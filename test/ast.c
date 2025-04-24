/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:45:57 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/24 19:05:48 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// t_tree *new_ast(t_gram type)
// {
//     t_tree *node = malloc(sizeof(t_tree));
//     if (!node)
//         return NULL;
//     node->value = type;
//     node->array = malloc(sizeof(t_arr));
//     if (!node->array)
//     {
//         free(node);
//         return NULL;
//     }
//     init_arr(node->array, 4, sizeof(t_tree *)); // dynamic array of t_tree*
//     return node;
// }
