/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:54:05 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/07 17:03:47 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// void f(void *s)
// {
// 	free(s);
// }
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
// 	ft_lstdelone(node4, f);
// 	printf("%s\n",node1->content);
// 	printf("%s\n",node2->content);
// 	printf("%s\n",node3->content);
// 	printf("%s\n",node4->content);
// }