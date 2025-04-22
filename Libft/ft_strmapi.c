/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:09:05 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 13:36:46 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				len;
	char			*ptr;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// char	f(unsigned int i, char c)
// {
// 	if(i % 2)
// 		return (ft_toupper(c));
// 	return (c);
// }

// int main()
// {
// 	char	s[] = "hello";
// 	char	*p = ft_strmapi(s,f);
// 	printf("%s\n",p);
// 	free(p);
// }