/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:11:38 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/08 17:36:16 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putnbr_fd(int n, int fd)
{
	if (fd == -1)
		return ;
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = n * -1;
		}
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
		}
		ft_putchar_fd((n % 10) + '0', fd);
	}
}

// int main()
// {
// 	char fd = open("nber.txt",O_WRONLY | O_RDONLY | O_CREAT , 0777);
// 	ft_putnbr_fd(123456,fd);
// }