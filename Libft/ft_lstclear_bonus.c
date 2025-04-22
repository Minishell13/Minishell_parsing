/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:27:37 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/23 07:02:34 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;

	if (lst)
	{
		while (*lst)
		{
			node = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = node;
		}
	}
}

// void f(void *s)
// {
// 	printf("Freeing content: %s\n", (char *)s);
// 	free(s);
// }
// int main()
// {
// 	t_list *node1 = ft_lstnew(ft_strdup("node1"));
// 	t_list *node2 = ft_lstnew(ft_strdup("node2"));
// 	t_list *node3 = ft_lstnew(ft_strdup("node3"));
// 	t_list *node4 = ft_lstnew(ft_strdup("node4"));
// 	ft_lstadd_back(&node1,node2);
// 	ft_lstadd_back(&node1,node3);
// 	ft_lstadd_back(&node1,node4);
// 	ft_lstclear(&node1, f);
// }