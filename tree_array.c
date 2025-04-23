/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:00:51 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/23 15:21:37 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    init_arr(t_arr *a, size_t init_size, size_t elem_size)
{
    a->arr = malloc(init_size * elem_size);
    if (!a->arr)
        return ;
    a->size = init_size;
    a->used = 0;
    a->elem_size = elem_size;
}

void    insert_arr(t_arr *a, void *element)
{
    size_t    old_size;
    void    *target;

    if (!element || !a)
        return ;
    if (a->size == a->used)
    {
        old_size = a->size * a->elem_size;
        a->size *= 2;
        a->arr = ft_realloc(a->arr, old_size, a->size * a->elem_size);
    }
    target = (char*)a->arr + (a->used * a->elem_size);
    ft_memcpy(target, element, a->elem_size);
    a->used++;
}

void    free_arr(t_arr *a)
{
    free(a->arr);
    a->arr = NULL;
    a->size = 0;
    a->used = 0;
    a->elem_size = 0;
}
