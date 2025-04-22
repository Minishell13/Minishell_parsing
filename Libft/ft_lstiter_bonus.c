/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:17:20 by hwahmane          #+#    #+#             */
/*   Updated: 2024/11/09 19:07:25 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}

// void f(void *s)
// {
// 	ft_strlcpy(s, "hello", sizeof(s));
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
// 	ft_lstiter(list, f);
// 	printf("%s\n",node1->content);
// 	printf("%s\n",node2->content);
// 	printf("%s\n",node3->content);
// 	printf("%s\n",node4->content);
// }