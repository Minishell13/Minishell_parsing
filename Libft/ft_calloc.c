/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 08:27:13 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/09 19:13:21 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	sz;
	void	*ptr;

	if (size != 0 && (count > ((size_t)-1 / size)))
		return (NULL);
	sz = count * size;
	ptr = malloc(sz);
	if (!ptr)
		return (NULL);
	ft_memset (ptr, 0, sz);
	return (ptr);
}

// int main()
// {
// 	char *ptr = (char *)ft_calloc(5,sizeof(char));
// 	int i = 0;
// 	while (i < 5)
// 	{
// 		if (ptr[i] == '\0')
// 			printf("%c",'0');
// 		i++;
// 	}
// } 