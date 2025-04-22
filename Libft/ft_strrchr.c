/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:01:34 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 10:11:32 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	c2;
	int				slen;

	slen = ft_strlen(s);
	c2 = c;
	while (slen >= 0)
	{
		if (s[slen] == c2)
			return ((char *)&s[slen]);
		slen--;
	}
	return (NULL);
}

// int main()
// {
// 	printf("%s",ft_strrchr("hello",'e'));
// }