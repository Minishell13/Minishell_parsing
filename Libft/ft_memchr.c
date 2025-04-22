/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:18:20 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/16 06:40:09 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		c2;
	size_t				i;
	const unsigned char	*str;

	c2 = (unsigned char)c;
	i = 0;
	str = (const unsigned char *)s;
	while (i < n)
	{
		if (str[i] == c2)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	printf("%s", ft_memchr("hello world",'w',12));
// }