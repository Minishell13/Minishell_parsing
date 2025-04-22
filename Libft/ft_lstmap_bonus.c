/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:50:22 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/26 21:33:33 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;
	void	*new_coontent;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_coontent = f(lst->content);
		node = ft_lstnew(new_coontent);
		if (!node)
		{
			ft_lstclear(&new_list, del);
			del(new_coontent);
			return (NULL);
		}
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
}

// void *f(void *s)
// {
// 	return (ft_strdup(s));
// }
// void del(void *s)
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
// 	t_list *new = ft_lstmap(list,f,del);
// 	printf("%s\n",new->content);
// 	printf("%s\n",new->next->content);
// 	printf("%s\n",new->next->next->content);
// 	printf("%s\n",new->next->next->next->content);
// }