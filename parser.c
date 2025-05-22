/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:46:40 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/22 18:18:30 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// parse command → subshell | simple_command
t_tree	*parse_command(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if (*tokens && (*tokens)->type == TOKEN_OPARENTHES)
		return (parse_subshell(tokens));
	return (parse_simple_command(tokens));
}

// parse pipeline: command ( '|' command )*
t_tree *parse_pipeline(t_token **tokens)
{
    t_tree *left;
    t_tree *right;
    t_tree *pipe;

    left = parse_command(tokens);
    if (!left)
        return NULL;
    while (*tokens && (*tokens)->type == TOKEN_PIPE)
    {
        *tokens = (*tokens)->next;
        if (!*tokens || (*tokens)->type == TOKEN_CPARENTHES || (*tokens)->type == TOKEN_PIPE
            || (*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR)
        {
            printf("syntax error: unexpected token after '|'\n");
            return NULL;
        }
        right = parse_command(tokens);
        if (!right)
            return NULL;
        pipe = new_tree_node(GRAM_PIPE);
        tree_add_child(pipe, left);
        tree_add_child(pipe, right);
        left = pipe;
    }
    return left;
}

// parse compound_command: pipeline ( (&& ||) pipeline )*
t_tree *parse_compound_command(t_token **tokens)
{
    t_tree *node;
    t_tree *left;
    t_tree *right;
    t_token_type op;

    left = parse_pipeline(tokens);
    if (!left)
        return NULL;
    while (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
    {
        op = (*tokens)->type;
        *tokens = (*tokens)->next;
        if (!*tokens || (*tokens)->type == TOKEN_CPARENTHES || (*tokens)->type == TOKEN_PIPE
            || (*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR)
        {
            printf("syntax error: unexpected token after '%s'\n", op == TOKEN_AND ? "&&" : "||");
            return NULL;
        }
        right = parse_pipeline(tokens);
        if (!right)
            return NULL;
        if (op == TOKEN_AND)
            node = new_tree_node(GRAM_OPERATOR_AND);
        else
            node = new_tree_node(GRAM_OPERATOR_OR);
        tree_add_child(node, left);
        tree_add_child(node, right);
        left = node;
    }
    return left;
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
			break ;
		tree_add_sibling(cur, next);
		cur = next;
	}
	return (head);
}

t_tree	*parse_complete_command(t_token **tokens)
{
	t_tree	*cmds;
	t_tree	*root;

	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == TOKEN_CPARENTHES)
	{
		printf("syntax error: unexpected ')'\n");
		return (NULL);
	}
	cmds = parse_command_list(tokens);
	if (!cmds)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
	if (*tokens)
	{
		if ((*tokens)->type == TOKEN_CPARENTHES)
			printf("syntax error: unexpected ')'\n");
		else
			printf("syntax error: unexpected token after command\n");
		return (NULL);
	}

	root = new_tree_node(GRAM_COMPLETE_COMMAND);
	tree_add_child(root, cmds);
	return (root);
}
