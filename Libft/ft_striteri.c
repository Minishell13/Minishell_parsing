/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:05:04 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 13:51:27 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s && f)
	{
		i = 0;
		while (s[i])
		{
			f(i, &s[i]);
			i++;
		}
	}
}

// void	f(unsigned int i, char *c)
// {
// 	if (i % 2)
// 		*c = ft_toupper(*c);
// }

// int main()
// {
// 	char s[] = "hello";
// 	ft_striteri(s, f);
// 	printf("%s\n", s);
// }