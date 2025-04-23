/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:46:40 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/23 16:29:03 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast *parse_redirect_list(t_token **tokens)
{
    t_ast *list_node = new_ast(GRAM_REDIRECT_LIST);
    if (!list_node) return NULL;

    while (*tokens && (
        (*tokens)->type == TOKEN_REDIR_IN ||
        (*tokens)->type == TOKEN_REDIR_OUT ||
        (*tokens)->type == TOKEN_REDIR_APPEND ||
        (*tokens)->type == TOKEN_HEREDOC))
    {
        // t_token_type redir_type = (*tokens)->type;
        char *redir_op = (*tokens)->value;
        *tokens = (*tokens)->next;

        if (!*tokens || (*tokens)->type != TOKEN_WORD) {
            free_ast(list_node);
            return NULL;
        }

        char *filename = (*tokens)->value;
        *tokens = (*tokens)->next;

        t_ast *redir_node = new_ast(GRAM_IO_REDIRECT);
        if (!redir_node) {
            free_ast(list_node);
            return NULL;
        }

        insert_arr(redir_node->array, &redir_op);  // redirection operator
        insert_arr(redir_node->array, &filename);  // target file

        insert_arr(list_node->array, &redir_node); // attach to redirect list
    }

    if (list_node->array->used == 0) {
        free_ast(list_node);
        return NULL;
    }

    return list_node;
}



t_ast *parse_subshell(t_token **tokens)
{
    // Ensure we have an opening parenthesis
    if (!tokens || !*tokens || (*tokens)->type != TOKEN_OPARENTHES)
        return NULL;

    // Consume the opening parenthesis
    *tokens = (*tokens)->next;

    // Parse the command list inside the parentheses
    t_ast *command_list_node = parse_command_list(tokens);
    if (!command_list_node)
        return NULL;

    // Ensure we have a closing parenthesis
    if (!*tokens || (*tokens)->type != TOKEN_CPARENTHES)
        return NULL;

    // Consume the closing parenthesis
    *tokens = (*tokens)->next;

    // Handle optional redirections
    t_ast *redirect_node = parse_redirect_list(tokens);
    if (redirect_node)
    {
        // If there is redirection, you can add it as a child node of the subshell
        command_list_node->array = merge_arrays(command_list_node->array, redirect_node->array);
    }

    // Return the parsed subshell node
    return command_list_node;
}

t_ast *parse_simple_command(t_token **tokens)
{
    t_ast *node = new_ast(GRAM_SIMPLE_COMMAND);
    if (!node) return NULL;

    while (*tokens)
    {
        if ((*tokens)->type == TOKEN_WORD) {
            char *word = (*tokens)->value;
            insert_arr(node->array, &word);
            *tokens = (*tokens)->next;
        }
        else if ((*tokens)->type == TOKEN_REDIR_IN ||
                 (*tokens)->type == TOKEN_REDIR_OUT ||
                 (*tokens)->type == TOKEN_REDIR_APPEND ||
                 (*tokens)->type == TOKEN_HEREDOC)
        {
            t_ast *redir = parse_redirect_list(tokens);
            if (!redir) {
                free_ast(node);
                return NULL;
            }
            insert_arr(node->array, &redir);
        }
        else break;
    }

    if (node->array->used == 0) {
        free_ast(node);
        return NULL;
    }

    return node;
}
    
t_ast *parse_command(t_token **tokens)
{
    t_ast *node = parse_subshell(tokens);
    if (node)
        return node;

    return parse_simple_command(tokens);
}

t_ast *parse_pipeline(t_token **tokens)
{
    t_ast *left = parse_command(tokens);
    if (!left)
        return NULL;

    // Skip linebreaks (TOKEN_EMPTY)
    while (*tokens && (*tokens)->type == TOKEN_EMPTY)
        *tokens = (*tokens)->next;

    if (*tokens && (*tokens)->type == TOKEN_PIPE)
    {
        *tokens = (*tokens)->next;

        // Skip linebreaks again
        while (*tokens && (*tokens)->type == TOKEN_EMPTY)
            *tokens = (*tokens)->next;

        t_ast *right = parse_pipeline(tokens);
        if (!right)
        {
            free_ast(left);
            return NULL;
        }

        t_ast *node = new_ast(GRAM_PIPELINE);
        if (!node)
        {
            free_ast(left);
            free_ast(right);
            return NULL;
        }

        insert_arr(node->array, &left);
        insert_arr(node->array, &right);
        return node;
    }

    return left;
}


t_ast *parse_compound_command(t_token **tokens)
{
    t_ast *left = parse_pipeline(tokens);
    if (!left)
        return NULL;

    // Skip linebreaks (TOKEN_EMPTY)
    while (*tokens && (*tokens)->type == TOKEN_EMPTY)
        *tokens = (*tokens)->next;

    if (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
    {
        t_token_type op_type = (*tokens)->type;
        *tokens = (*tokens)->next;

        // Skip linebreaks again
        while (*tokens && (*tokens)->type == TOKEN_EMPTY)
            *tokens = (*tokens)->next;

        t_ast *right = parse_compound_command(tokens);
        if (!right)
        {
            free_ast(left); // Handle memory cleanup
            return NULL;
        }

        t_ast *node = new_ast(GRAM_COMPOUND_COMMAND);
        if (!node)
        {
            free_ast(left);
            free_ast(right);
            return NULL;
        }

        insert_arr(node->array, &left);
        insert_arr(node->array, &right);
        node->value = (op_type == TOKEN_AND) ? GRAM_OPERATOR_AND : GRAM_OPERATOR_OR;
        return node;
    }

    return left;
}

t_ast *parse_command_list(t_token **tokens)
{
    t_ast *node = new_ast(GRAM_COMMAND_LIST);
    if (!node)
        return NULL;

    t_ast *compound = parse_compound_command(tokens);
    if (!compound)
    {
        free(node); // free the array inside as well if needed
        return NULL;
    }
    insert_arr(node->array, &compound);

    // Skip linebreaks (TOKEN_EMPTY)
    while (*tokens && (*tokens)->type == TOKEN_EMPTY)
        *tokens = (*tokens)->next;

    // Try to parse another command_list recursively
    t_ast *next = parse_command_list(tokens);
    if (next)
        insert_arr(node->array, &next);

    return node;
}

t_ast *parse_complete_command(t_token **tokens)
{
    t_ast *node = new_ast(GRAM_COMPLETE_COMMAND);
    if (!node)
        return NULL;

    // Skip any linebreaks (TOKEN_EMPTY if you're using it that way)
    while (*tokens && (*tokens)->type == TOKEN_EMPTY)
        *tokens = (*tokens)->next;

    t_ast *command_list = parse_command_list(tokens);
    if (!command_list)
    {
        free(node); // Also free array
        return NULL;
    }

    insert_arr(node->array, &command_list);

    // Again skip linebreaks if any
    while (*tokens && (*tokens)->type == TOKEN_EMPTY)
        *tokens = (*tokens)->next;

    return node;
}
