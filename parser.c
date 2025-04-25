/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:46:40 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/25 17:56:23 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// parse command → subshell | simple_command
t_tree	*parse_command(t_token **tokens)
{
	if (*tokens && (*tokens)->type == TOKEN_OPARENTHES)
		return (parse_subshell(tokens));
	return (parse_simple_command(tokens));
}

// parse pipeline: command ( '|' command )*
t_tree	*parse_pipeline(t_token **tokens)
{
	t_tree	*left;
	t_tree	*right;
	t_tree	*pipe;

	left = parse_command(tokens);
	if (!left)
		return (NULL);
	// while we see pipe, build a PIPELINE node
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;// consume '|'
		right = parse_command(tokens);
		if (!right)
		{
			// TODO: free left
			return (NULL);
		}
		pipe = new_tree_node(GRAM_PIPELINE);// build a new pipeline node
		tree_add_child(pipe, left);
		tree_add_child(pipe, right);
		left = pipe;
	}
	return (left);
}

// parse compound_command: pipeline ( (&&|||) pipeline )*
t_tree	*parse_compound_command(t_token **tokens)
{
	t_tree			*node;
	t_tree			*left;
	t_tree			*right;
	t_token_type	op;

	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		op = (*tokens)->type;
		*tokens = (*tokens)->next;
		right = parse_pipeline(tokens);
		if (!right)
			return (NULL);// TODO: free left if needed
		if (op == TOKEN_AND)
			node = new_tree_node(GRAM_OPERATOR_AND);
		else
			node = new_tree_node(GRAM_OPERATOR_OR);
		tree_add_child(node, left);
		tree_add_child(node, right);
		left = node;
	}
	return (left);
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
		// skip linebreaks
		while (*tokens && (*tokens)->type == TOKEN_EMPTY)
			*tokens = (*tokens)->next;
		// peek next compound_command
		next = parse_compound_command(tokens);
		if (!next)
			break ;
		tree_add_sibling(cur, next);
		cur = next;
	}
	return (head);
}

// parse complete_command: command_list
t_tree	*parse_complete_command(t_token **tokens)
{
	t_tree	*cmds;
	t_tree	*root;

	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
	cmds = parse_command_list(tokens);
	if (!cmds)
		return (NULL);
	root = new_tree_node(GRAM_COMPLETE_COMMAND);
	tree_add_child(root, cmds);
	return (root);
}
