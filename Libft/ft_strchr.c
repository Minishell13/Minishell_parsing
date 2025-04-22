/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:26:05 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 13:58:10 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c2;
	int				i;

	c2 = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c2)
			return ((char *)(&s[i]));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}

// int main()
// {
// 	printf("%s\n", ft_strchr("hello world",'w'));
// }