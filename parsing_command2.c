/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:36:09 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/30 17:12:38 by hwahmane         ###   ########.fr       */
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

// ------------------- parse_compound_command
t_tree	*handle_compound_op(t_token **tokens, t_tree *left, t_token_type op)
{
	t_tree	*node;
	t_tree	*right;
	t_gram	gram_type;

	if (!*tokens || (*tokens)->type == TOKEN_CPARENTHES
		|| (*tokens)->type == TOKEN_PIPE || (*tokens)->type == TOKEN_AND
		|| (*tokens)->type == TOKEN_OR)
	{
		printf("syntax error: unexpected token\n");
		return (NULL);
	}
	right = parse_pipe(tokens);
	if (!right)
		return (NULL);
	if (op == TOKEN_AND)
		gram_type = GRAM_OPERATOR_AND;
	else
		gram_type = GRAM_OPERATOR_OR;
	node = new_tree_node(gram_type);
	if (!node)
		return (NULL);
	tree_add_child(node, left);
	tree_add_child(node, right);
	return (node);
}
