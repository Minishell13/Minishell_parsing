/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:34:58 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/23 15:35:24 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void    *new;
    size_t    size_to_copy;

    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    new = malloc(new_size);
    if (!new)
        return (NULL);
    if (ptr && old_size > 0)
    {
        if (old_size < new_size)
            size_to_copy = old_size;
        else
            size_to_copy = new_size;
        ft_memcpy(new, ptr, size_to_copy);
        free(ptr);
    }
    else
        free(ptr);
    return (new);
}
