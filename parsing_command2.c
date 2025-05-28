/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:36:09 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/28 16:41:07 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// ------------------- parse_redirect_list functions
void	skip_empty_tokens(t_token **tokens)
{
	while (*tokens && (*tokens)->next && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
}

int	is_redirect_token(t_token *token)
{
	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_HEREDOC);
}

t_tree	*create_redirect_node(t_token_type type, char *file, t_tree *list)
{
	t_tree	*op_node;

	if (!list)
		return (NULL);
	op_node = new_tree_leaf(GRAM_REDIR_IN + (type - TOKEN_REDIR_IN), file);
	// file_node = new_tree_leaf(GRAM_FILENAME, file);
	if (!op_node)
		return (NULL);
	tree_add_child(list, op_node);
	return (list);
}

int	handle_redirection(t_token **tokens, t_tree *list)
{
	t_token_type	type;
	char			*file;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	skip_empty_tokens(tokens);
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		printf("syntax error near unexpected token `newline'");
		return (0);
	}
	file = (*tokens)->value;
	*tokens = (*tokens)->next;
	if (!create_redirect_node(type, file, list))
		return (0);
	return (1);
}
