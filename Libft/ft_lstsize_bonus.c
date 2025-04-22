/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:52:54 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 17:00:55 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*nx;
	int		count;

	count = 0;
	nx = lst;
	while (nx)
	{
		nx = nx->next;
		count++;
	}
	return (count);
}

// int main()
// {
// 	t_list *list = NULL;

// 	t_list *node1 = ft_lstnew(ft_strdup("node1"));
// 	t_list *node2 = ft_lstnew(ft_strdup("node2"));
// 	t_list *node3 = ft_lstnew(ft_strdup("node3"));
// 	t_list *node4 = ft_lstnew(ft_strdup("node4"));

// 	ft_lstadd_back(&list,node1);
// 	ft_lstadd_back(&list,node2);
// 	ft_lstadd_back(&list,node3);
// 	ft_lstadd_back(&list,node4);

// 	printf("%d",ft_lstsize(list));
// }