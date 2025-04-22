/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:14:26 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/08 17:37:46 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd == -1)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

// int main()
// {
// 	char p[] = "hello world";
// 	char fd = open("hello.txt", O_WRONLY | O_RDONLY | O_CREAT, 0777);
// 	ft_putstr_fd(p, fd);
// }