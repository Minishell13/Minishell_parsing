/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:44:16 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/28 17:27:42 by hwahmane         ###   ########.fr       */
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
	return (node);
}


t_tree *parse_simple_command(t_token **tokens)
{
    t_bool flag;
    t_tree *cmd;
    t_tree *rlist;
    t_list *words;
    t_list *last_word;
    int count;

    words = NULL;
    rlist = NULL;
    last_word = NULL;
    flag = true;
    cmd = NULL;
    if ((*tokens)->type == TOKEN_WORD)
        cmd = new_tree_node(GRAM_SIMPLE_COMMAND);
    else if ((*tokens)->type == TOKEN_REDIR_IN || (*tokens)->type == TOKEN_REDIR_OUT || (*tokens)->type == TOKEN_HEREDOC || (*tokens)->type == TOKEN_REDIR_APPEND)
    {
        cmd = new_tree_node(GRAM_IO_REDIRECT);
        flag = false;
    }
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
            if (flag && !rlist)
            {
                rlist = new_tree_node(GRAM_IO_REDIRECT);
                if (!rlist)
                    return NULL;
            }
            if (flag)
            {
                if (!handle_redirection(tokens, rlist))
                    return NULL;
            }
            else
                if (!handle_redirection(tokens, cmd))
                return NULL;
        }
    }
    if (cmd && *tokens && ((*tokens)->type == TOKEN_OPARENTHES))
    {
        skip_empty_tokens(tokens);
        if ((*tokens)->next)
            printf("syntax error: near unexpected token `%s'",(*tokens)->next->value);
        else
            parse_subshell(tokens);
        return NULL;
    }
    if (flag)
    {
        if (!words)
            return NULL;
        count = count_words(words);
        cmd->data.args = malloc(sizeof(char *) * (count + 1));
        if (!cmd->data.args || !fill_words_array(cmd->data.args, words))
            return NULL;
    }
    if (flag)
        tree_add_child(cmd, rlist);
    return cmd;
}

