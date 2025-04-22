/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:00:55 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 17:57:10 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

// int	main()
// {
// 	printf("%d\n",ft_isalnum('@'));
// 	printf("%d\n",ft_isalnum('a'));
// 	printf("%d\n",ft_isalnum('6'));
// }