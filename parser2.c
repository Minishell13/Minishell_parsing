/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:44:16 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/24 19:41:15 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*parse_subshell(t_token **tokens)
{
	t_tree	*node;
	t_tree	*inner;
	t_token *after_paren;

	if (!consume_token_type(tokens, TOKEN_OPARENTHES))
		return (NULL);
	skip_empty_tokens(tokens);
	inner = parse_command_list(tokens);
	if (!inner)
		return (printf("syntax error: empty subshell or invalid content\n"), NULL);
	skip_empty_tokens(tokens);
	if (inner->sibling)
		return (printf("syntax error: multiple commands in subshell without operator\n"), NULL);
	if (!consume_token_type(tokens, TOKEN_CPARENTHES))
		return (printf("syntax error: expected ')'\n"), NULL);
	after_paren = *tokens;
	skip_empty_tokens(&after_paren);
	if (after_paren && after_paren->type == TOKEN_OPARENTHES)
	{
		printf("syntax error: unexpected '('\n");
		return NULL;
	}
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

t_tree *parse_simple_command(t_token **tokens)
{
    t_tree *cmd;
    t_tree *rlist = NULL;
    t_list *words = NULL;
    t_list *last_word = NULL;

    cmd = new_tree_node(GRAM_SIMPLE_COMMAND);
    if (!cmd)
        return NULL;

    while (*tokens && ((*tokens)->type == TOKEN_WORD || is_redirect_token(*tokens)))
    {
        if ((*tokens)->type == TOKEN_WORD)
        {
            t_list *new_word = malloc(sizeof(t_list));
            if (!new_word)
                return NULL;
            new_word->token = *tokens;
            new_word->next = NULL;

            if (!words)
                words = new_word;
            else
                last_word->next = new_word;
            last_word = new_word;

            *tokens = (*tokens)->next;
        }
        else if (is_redirect_token(*tokens))
        {
            if (!rlist)
            {
                rlist = new_tree_node(GRAM_REDIRECT_LIST);
                if (!rlist)
                    return NULL;
            }
            if (!handle_redirection(tokens, rlist))
                return NULL;
        }
    }
    if (!words)
        return NULL;
    int count = count_words(words);
    cmd->words = malloc(sizeof(char *) * (count + 1));
    if (!cmd->words || !fill_words_array(cmd->words, words))
        return NULL;

    if (rlist)
        tree_add_child(cmd, rlist);

    return cmd;
}

