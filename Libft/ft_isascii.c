/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:13:06 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 18:13:45 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return ((c >= 0 && c <= 127));
}

// int	main()
// {
// 	printf("%d\n",ft_isascii('@'));
// 	printf("%d\n",ft_isascii('a'));
// 	printf("%d\n",ft_isascii(255));
// }