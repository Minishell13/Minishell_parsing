/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:45:57 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/23 16:08:59 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// t_ast *new_ast(t_gram type)
// {
//     t_ast *node = malloc(sizeof(t_ast));
//     if (!node)
//         return NULL;
//     node->value = type;
//     node->array = malloc(sizeof(t_arr));
//     if (!node->array)
//     {
//         free(node);
//         return NULL;
//     }
//     init_arr(node->array, 4, sizeof(t_ast *)); // dynamic array of t_ast*
//     return node;
// }
