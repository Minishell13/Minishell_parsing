/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:28:52 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/22 17:29:00 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// ------------------- parse_simple_command functions
int	count_words(t_list *word_list)
{
	int	count;

	count = 0;
	while (word_list)
	{
		count++;
		word_list = word_list->next;
	}
	return (count);
}

int	fill_words_array(char **arr, t_list *word_list)
{
	int	i;

	i = 0;
	while (word_list)
	{
		arr[i] = strdup(word_list->token->value);
		if (!arr[i])
			return (0);
		i++;
		word_list = word_list->next;
	}
	arr[i] = NULL;
	return (1);
}

t_list	*collect_words(t_token **tokens)
{
	t_list	*list;
	t_list	*new;

	list = NULL;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		new = malloc(sizeof(t_list));
		if (!new)
			return (NULL);
		new->token = *tokens;
		new->next = NULL;
		append_to_list(&list, new);
		*tokens = (*tokens)->next;
	}
	return (list);
}

// ------------------- parse_subshell functions
int	consume_token_type(t_token **tokens, t_token_type type)
{
	if (!*tokens || (*tokens)->type != type)
		return (0);
	*tokens = (*tokens)->next;
	return (1);
}

void	parse_subshell_redirects(t_token **tokens, t_tree *node)
{
	t_tree	*rlist;

	while (1)
	{
		skip_empty_tokens(tokens);
		rlist = parse_redirect_list(tokens);
		if (!rlist)
			break ;
		tree_add_child(node, rlist);
	}
}
