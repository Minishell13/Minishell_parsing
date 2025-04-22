/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:05 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/08 17:30:37 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd != -1)
		write(fd, &c, 1);
}

// int main()
// {
// 	char fd = open("end.txt", O_WRONLY | O_RDONLY | O_CREAT, 0777);
// 	ft_putchar_fd('d', fd);
// }