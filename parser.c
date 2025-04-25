/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:46:40 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/25 16:21:37 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*parse_subshell(t_token **tokens)
{
	t_tree	*node;
	t_tree	*inner;
	t_tree	*rlist;

	// 1) Must see '('
	if (!*tokens || (*tokens)->type != TOKEN_OPARENTHES)
		return (NULL);
	*tokens = (*tokens)->next;
	// 2) Skip any EMPTY tokens (linebreaks)
	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
	// 3) Parse the inner command_list
	inner = parse_command_list(tokens);
	if (!inner)
		return (NULL);
	// 4) Skip any trailing EMPTY
	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
		*tokens = (*tokens)->next;
	// 5) Must see ')'
	if (!*tokens || (*tokens)->type != TOKEN_CPARENTHES)
	{
		printf("syntax error: expected ')'\n");
		// TODO: free inner subtree here
		return (NULL);
	}
	*tokens = (*tokens)->next;
	// 6) Build the GRAM_SUBSHELL node and attach the inner CL
	node = new_tree_node(GRAM_SUBSHELL);
	if (!node)
		return (NULL);
	tree_add_child(node, inner);
	// 7) Now zero-or-more redirect_list
	while (1)
	{
		// skip empties
		while (*tokens && (*tokens)->type == TOKEN_EMPTY)
			*tokens = (*tokens)->next;
		rlist = parse_redirect_list(tokens);
		if (!rlist)
			break ;
		tree_add_child(node, rlist);
	}
	return (node);
}

// parse a sequence of IO_REDIRECT → build a REDIRECT_LIST
t_tree	*parse_redirect_list(t_token **tokens)
{
	t_tree			*list;
	t_token_type	tok_type;
	char			*op;
	char			*filename;
	t_tree			*redir;

	list = new_tree_node(GRAM_REDIRECT_LIST);
	if (!list)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_REDIR_IN
			|| (*tokens)->type == TOKEN_REDIR_OUT
			|| (*tokens)->type == TOKEN_REDIR_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC))
	{
		// Save operator token type before consuming
		tok_type = (*tokens)->type;
		// operator string (">", "<", etc.)
		op = (*tokens)->value;
		*tokens = (*tokens)->next;
		// skip empty tokens
		while (*tokens && (*tokens)->type == TOKEN_EMPTY)
			*tokens = (*tokens)->next;
		// next must be a filename
		if (!*tokens || (*tokens)->type != TOKEN_WORD)
		{
			printf("syntax error: expected filename\n");
			// TODO: free `list`
			return (NULL);
		}
		filename = (*tokens)->value;
		*tokens = (*tokens)->next;
		// create IO_REDIRECT node
		redir = new_tree_node(GRAM_IO_REDIRECT);
		if (!redir)
			return (NULL);
		// operator node
		tree_add_child(redir, new_tree_leaf(GRAM_REDIR_IN
				+(tok_type - TOKEN_REDIR_IN), op));
		// filename node
		tree_add_child(redir, new_tree_leaf(GRAM_FILENAME, filename));
		// attach redirect node to the list
		tree_add_child(list, redir);
	}
	if (!list->child)
	{
		free(list);
		return (NULL);
	}
	return (list);
}

// parse a simple_command : WORD* redirect_list?
t_tree *parse_simple_command(t_token **tokens)
{
    t_tree *cmd;
    t_tree *rlist;
    t_list *word_list = NULL;

    cmd = new_tree_node(GRAM_SIMPLE_COMMAND);
    if (!cmd)
        return (NULL);

    // Accumulate WORDs into a linked list
    while (*tokens && (*tokens)->type == TOKEN_WORD)
    {
        t_list *new_word = malloc(sizeof(t_list));
        if (!new_word)
            return NULL;
        new_word->token = *tokens;
        new_word->next = NULL;
        append_to_list(&word_list, new_word);
        *tokens = (*tokens)->next;
    }

    // Convert linked list to array
    int count = 0;
    t_list *tmp = word_list;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    cmd->words = malloc(sizeof(char *) * (count + 1));
    if (!cmd->words)
        return NULL;

    tmp = word_list;
    for (int i = 0; i < count; i++)
    {
        cmd->words[i] = strdup(tmp->token->value);
        tmp = tmp->next;
    }
    cmd->words[count] = NULL; // Null-terminate

    // Optional redirections
    rlist = parse_redirect_list(tokens);
    if (rlist)
        tree_add_child(cmd, rlist);

    if (!cmd->words || !cmd->words[0])
    {
        // TODO: free everything
        return NULL;
    }

    return cmd;
}


// parse command → subshell | simple_command
t_tree	*parse_command(t_token **tokens)
{
	if (*tokens && (*tokens)->type == TOKEN_OPARENTHES)
		return parse_subshell(tokens);
	return parse_simple_command(tokens);
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
		*tokens = (*tokens)->next; // consume '|'
		right = parse_command(tokens);
		if (!right)
		{
			// TODO: free left
			return (NULL);
		}
		// build a new pipeline node
		pipe = new_tree_node(GRAM_PIPELINE);
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
			return (NULL); // TODO: free left if needed
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
	return head;
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
