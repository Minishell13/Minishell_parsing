/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:06:47 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 17:47:12 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_num(unsigned int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	int_cpy(char *ptr, int len, int sign, int num)
{
	int	i;

	i = len + sign - 1;
	while (num >= 10)
	{
		ptr[i] = (num % 10) + '0';
		i--;
		num /= 10;
	}
	ptr[i] = (num % 10) + '0';
}

char	*ft_itoa(int n)
{
	int				len;
	int				sign;
	char			*ptr;
	unsigned int	num;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num = n;
	sign = 0;
	if (n < 0)
	{
		num = n * -1;
		sign = 1;
	}
	len = len_num(num);
	if (n == 0)
		len = 1;
	ptr = malloc(len + sign + 1);
	if (!ptr)
		return (NULL);
	ptr[len + sign] = '\0';
	if (sign)
		ptr[0] = '-';
	int_cpy(ptr, len, sign, num);
	return (ptr);
}

// int main()
// {
// 	printf("%s\n", ft_itoa(123456789));
// }