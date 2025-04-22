/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:28:02 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/10 17:28:05 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst && new)
	{
		if (*lst == NULL)
		{
			*lst = new;
			return ;
		}
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

// int main()
// {
// 	t_list *node1 = ft_lstnew(ft_strdup("node1"));
// 	t_list *node2 = ft_lstnew(ft_strdup("node2"));
// 	t_list *node3 = ft_lstnew(ft_strdup("node3"));
// 	t_list *node4 = ft_lstnew(ft_strdup("node4"));
// 	ft_lstadd_back(&node1, node2);
// 	ft_lstadd_back(&node1, node3);
// 	ft_lstadd_back(&node1, node4);
// 	printf("%s\n",node1->content);
// 	printf("%s\n",node1->next->content);
// 	printf("%s\n",node1->next->next->content);
// 	printf("%s\n",node1->next->next->next->content);
// }