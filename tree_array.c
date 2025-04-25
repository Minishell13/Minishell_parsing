/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:00:51 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/25 17:18:51 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create an internal node (no string)
t_tree	*new_tree_node(t_gram gram)
{
	t_tree	*n;

	n = malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->gram = gram;
	n->str = NULL;
	n->child = NULL;
	n->sibling = NULL;
	return (n);
}

// create a leaf node (a WORD or filename)
t_tree	*new_tree_leaf(t_gram gram, char *s)
{
	t_tree	*n;

	n = new_tree_node(gram);
	if (!n)
		return (NULL);
	n->str = strdup(s);
	return (n);
}

// append `c` as the last child of `parent`
void	tree_add_child(t_tree *parent, t_tree *c)
{
	t_tree	*it;

	if (!parent || !c)
		return ;
	if (!parent->child)
	{
		parent->child = c;
	}
	else
	{
		it = parent->child;
		while (it->sibling)
			it = it->sibling;
		it->sibling = c;
	}
}

// append `sib` as the last sibling of `node`
void	tree_add_sibling(t_tree *node, t_tree *sib)
{
	if (!node || !sib)
		return ;
	while (node->sibling)
		node = node->sibling;
	node->sibling = sib;
}

// Append a node to the list
void	append_to_list(t_list **list, t_list *new_node)
{
	t_list	*temp;

	if (!*list)
	{
		*list = new_node;
	}
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}
