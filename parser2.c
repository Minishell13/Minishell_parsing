/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:44:16 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/18 16:53:31 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*parse_subshell(t_token **tokens)
{
	t_tree	*node;
	t_tree	*inner;

	if (!consume_token_type(tokens, TOKEN_OPARENTHES))
		return (NULL);
	skip_empty_tokens(tokens);
	inner = parse_command_list(tokens);
	if (!inner)
		return (NULL);
	skip_empty_tokens(tokens);
	if (!consume_token_type(tokens, TOKEN_CPARENTHES))
		return (printf("syntax error: expected ')'\n"), NULL);
	node = new_tree_node(GRAM_SUBSHELL);
	if (!node)
		return (NULL);
	tree_add_child(node, inner);
	parse_subshell_redirects(tokens, node);
	return (node);
}

// parse a sequence of IO_REDIRECT → build a REDIRECT_LIST
t_tree	*parse_redirect_list(t_token **tokens)
{
	t_tree	*list;

	list = new_tree_node(GRAM_REDIRECT_LIST);
	if (!list)
		return (NULL);
	while (*tokens && is_redirect_token(*tokens))
	{
		if (!handle_redirection(tokens, list))
			return (NULL);
	}
	if (!list->child)
		return (free(list), NULL);
	return (list);
}

// parse a simple_command : WORD* redirect_list?
t_tree	*parse_simple_command(t_token **tokens)
{
	t_tree	*cmd;
	t_tree	*rlist;
	t_list	*words;
	int		count;

	cmd = new_tree_node(GRAM_SIMPLE_COMMAND);
	if (!cmd)
		return (NULL);
	words = collect_words(tokens);
	count = count_words(words);
	cmd->words = malloc(sizeof(char *) * (count + 1));
	if (!cmd->words || !fill_words_array(cmd->words, words))
		return (NULL);
	rlist = parse_redirect_list(tokens);
	if (rlist)
		tree_add_child(cmd, rlist);
	if (!cmd->words[0])
		return (NULL);
	return (cmd);
}
