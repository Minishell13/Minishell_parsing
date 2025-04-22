/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:04:40 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/24 21:00:04 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;
	int		len;
	int		i;

	len = ft_lstsize(lst);
	i = 0;
	last = lst;
	while (i < len - 1)
	{
		last = last->next;
		i++;
	}
	return (last);
}

// int main()
// {
// 	t_list *list = NULL;
// 	t_list *node1 = ft_lstnew(ft_strdup("node1"));
	// t_list *node2 = ft_lstnew(ft_strdup("node2"));
	// t_list *node3 = ft_lstnew(ft_strdup("node3"));
// 	t_list *node4 = ft_lstnew(ft_strdup("node4"));
// 	ft_lstadd_back(&list,node1);
// 	ft_lstadd_back(&list,node2);
// 	ft_lstadd_back(&list,node3);
// 	ft_lstadd_back(&list,node4);
// 	printf("%s",ft_lstlast(list)->content);
// }