/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:45:11 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/08 16:33:13 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*ptr;
	size_t		len;

	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s1 && !s2)
		return (ft_strdup(""));
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	ptr = (char *)malloc(len);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len);
	ft_strlcat(ptr, s2, len);
	return (ptr);
}

// int main()
// {
// 	char	s1[] = "hello ";
// 	char	s2[] = "world";

// 	char *ptr = ft_strjoin(NULL, s2);
// 	printf("%s\n", ptr);
// }