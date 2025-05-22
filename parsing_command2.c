/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:36:09 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/22 18:28:19 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// ------------------- parse_redirect_list functions
void	skip_empty_tokens(t_token **tokens)
{
	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
}

int	is_redirect_token(t_token *token)
{
	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_HEREDOC);
}

t_tree	*create_redirect_node(t_token_type type, char *op, char *file)
{
	t_tree	*redir;
	t_tree	*op_node;
	t_tree	*file_node;

	redir = new_tree_node(GRAM_IO_REDIRECT);
	if (!redir)
		return (NULL);
	op_node = new_tree_leaf(GRAM_REDIR_IN + (type - TOKEN_REDIR_IN), op);
	file_node = new_tree_leaf(GRAM_FILENAME, file);
	if (!op_node || !file_node)
		return (NULL);
	tree_add_child(redir, op_node);
	tree_add_child(redir, file_node);
	return (redir);
}

int	handle_redirection(t_token **tokens, t_tree *list)
{
	t_token_type	type;
	char			*op;
	char			*file;
	t_tree			*redir;

	type = (*tokens)->type;
	op = (*tokens)->value;
	*tokens = (*tokens)->next;
	skip_empty_tokens(tokens);
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (0);
	file = (*tokens)->value;
	*tokens = (*tokens)->next;
	redir = create_redirect_node(type, op, file);
	if (!redir)
		return (0);
	tree_add_child(list, redir);
	return (1);
}
