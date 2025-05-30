/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:46:40 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/30 17:47:01 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// parse command → subshell | simple_command
t_tree	*parse_command(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if (*tokens && ((*tokens)->type == TOKEN_OPARENTHES
			|| (*tokens)->type == TOKEN_CPARENTHES))
		return (parse_subshell(tokens));
	return (parse_simple_command(tokens));
}

// parse pipeline: command ( '|' command )*
t_tree	*parse_pipe(t_token **tokens)
{
	t_tree	*left;
	t_tree	*right;
	t_tree	*pipe;

	left = parse_command(tokens);
	if (!left)
	{
		if ((*tokens) && ((*tokens)->type == TOKEN_PIPE
			|| (*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
			printf("syntax error near unexpected token `%s'",(*tokens)->value);
		return (NULL);
	}
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		if (is_invalid_pipe_token(*tokens))
		{
			free_tree(left);
			printf("syntax error: unexpected token after '|'");
			return (NULL);
		}
		right = parse_command(tokens);
		if (!right)
		{
			free_tree(right);
			return (NULL);
		}
		pipe = new_tree_node(GRAM_PIPE);
		tree_add_child(pipe, left);
		tree_add_child(pipe, right);
		left = pipe;
	}
	return (left);
}

// parse compound_command: pipeline ( (&& ||) pipeline )*
t_tree	*parse_compound_command(t_token **tokens)
{
	t_tree			*left;
	t_tree			*right;
	t_bool			flag;
	t_token_type	op;

	flag = true;
	left = parse_pipe(tokens);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		op = (*tokens)->type;
		*tokens = (*tokens)->next;
		right = handle_compound_op(tokens, left, op);
		if (!right)
		{
			free_tree(left);
			return (NULL);
		}
		flag = false;
	}
	if (flag == true)
		return (left);
	return (right);
}

// parse command_list: compound_command ( compound_command )*
t_tree	*parse_command_list(t_token **tokens)
{
	t_tree	*head;
	t_tree	*cur;
	t_tree	*next;

	head = parse_compound_command(tokens);
	if (!head)
		return (NULL);
	cur = head;
	while (1)
	{
		while (*tokens && (*tokens)->type == TOKEN_EMPTY)
			*tokens = (*tokens)->next;
		next = parse_compound_command(tokens);
		if (!next)
			break;
		tree_add_sibling(cur, next);
		cur = next;
	}
	return (head);
}

t_tree	*parse_complete_command(t_token **tokens)
{
	t_tree	*cmds;
	t_tree	*root;

	if (is_invalid_start_token(tokens))
		return (NULL);
	cmds = parse_command_list(tokens);
	if (!cmds || has_extra_tokens(tokens))
	{
		free_tree(cmds);
		return (NULL);
	}
	root = new_tree_node(GRAM_COMPLETE_COMMAND);
	if (!root)
	{
		free_tree(cmds);
		return (NULL);
	}
	tree_add_child(root, cmds);
	return (root);
}
