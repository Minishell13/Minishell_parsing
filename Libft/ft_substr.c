/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:03:17 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/06 16:36:07 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			src_len;
	size_t			substr_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len)
		return (ft_strdup(""));
	substr_len = src_len - start;
	if (substr_len > len)
		substr_len = len;
	ptr = (char *) malloc(substr_len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, &s[start], substr_len + 1);
	return ((char *)ptr);
}

// int main()
// {
// 	char s[] = "hello world";
// 	char *newS = ft_substr(s, 0 , 5);
// 	int i = 0;
// 	while (newS[i])
// 		printf("%c", newS[i++]);
// }