/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:25:03 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 09:55:05 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char_in_set(char c, const char *set2)
{
	int	i;

	i = 0;
	while (set2[i])
	{
		if (set2[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		start;
	int		end;
	int		len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && is_char_in_set(s1[start], set))
		start++;
	while (end >= start && is_char_in_set(s1[end], set))
		end--;
	len = end - start + 1;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, &s1[start], len + 1);
	return (ptr);
}

// int main()
// {
// 	printf("%s\n", ft_strtrim("hhhelhlohh","hh"));
// }