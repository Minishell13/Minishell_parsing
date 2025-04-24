/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:46:40 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/24 19:05:48 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree *parse_redirect_list(t_token **tokens)
{
    t_tree *list_node = new_ast(GRAM_REDIRECT_LIST);
    if (!list_node) return NULL;

    while (*tokens && (
        (*tokens)->type == TOKEN_REDIR_IN ||
        (*tokens)->type == TOKEN_REDIR_OUT ||
        (*tokens)->type == TOKEN_REDIR_APPEND ||
        (*tokens)->type == TOKEN_HEREDOC))
    {
        char *redir_op = (*tokens)->value;  // Redirection operator
        *tokens = (*tokens)->next; // Move past the operator token

        if (!redir_op || redir_op[0] == '\0') {
            // If redirection operator is invalid or empty, return error
            printf("Error: Redirection operator is NULL or empty.\n");
            free_ast(list_node);
            return NULL;
        }

        // Skip any empty tokens (e.g., line breaks or extra spaces)
        while (*tokens && (*tokens)->type == TOKEN_EMPTY)
            *tokens = (*tokens)->next;

        // Check for a valid token after the operator (should be a filename)
        if (!*tokens || (*tokens)->type != TOKEN_WORD || !(*tokens)->value || (*tokens)->value[0] == '\0') {
            // If no filename or invalid filename, return error
            printf("Error: Expected filename after redirection operator.\n");
            free_ast(list_node);
            return NULL;
        }

        char *filename = (*tokens)->value;  // Filename after the redirection operator
        *tokens = (*tokens)->next; // Move past the filename token

        // Create a new redirection node
        t_tree *redir_node = new_ast(GRAM_IO_REDIRECT);
        if (!redir_node) {
            free_ast(list_node);
            return NULL;
        }

        // Insert the redirection operator and filename into the redirection node
        insert_arr(redir_node->array, &redir_op);  // Insert operator (e.g., '>', '<', etc.)
        insert_arr(redir_node->array, &filename);  // Insert filename (e.g., 'file.txt')

        // Insert the redirection node into the list node's array
        insert_arr(list_node->array, &redir_node);
    }

    // If no redirections were found, free the list node and return NULL
    if (list_node->array->used == 0) {
        free_ast(list_node);
        return NULL;
    }

    return list_node;
}





t_tree *parse_subshell(t_token **tokens)
{
    // Ensure we have an opening parenthesis
    if (!tokens || !*tokens || (*tokens)->type != TOKEN_OPARENTHES)
        return NULL;

    // Consume the opening parenthesis
    *tokens = (*tokens)->next;

    // Parse the command list inside the parentheses
    t_tree *command_list_node = parse_command_list(tokens);
    if (!command_list_node)
        return NULL;

    // Ensure we have a closing parenthesis
    if (!*tokens || (*tokens)->type != TOKEN_CPARENTHES)
        return NULL;

    // Consume the closing parenthesis
    *tokens = (*tokens)->next;

    // Handle optional redirections
    t_tree *redirect_node = parse_redirect_list(tokens);
    if (redirect_node)
    {
        // If there is redirection, you can add it as a child node of the subshell
        command_list_node->array = merge_arrays(command_list_node->array, redirect_node->array);
    }

    // Return the parsed subshell node
    return command_list_node;
}

t_tree *parse_simple_command(t_token **tokens)
{
    t_tree *node = new_ast(GRAM_SIMPLE_COMMAND);
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
            t_tree *redir = parse_redirect_list(tokens);
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
    
t_tree *parse_command(t_token **tokens)
{
    t_tree *node = parse_subshell(tokens);
    if (node)
        return node;

    return parse_simple_command(tokens);
}

t_tree *parse_pipeline(t_token **tokens)
{
    t_tree *left = parse_command(tokens);
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

        t_tree *right = parse_pipeline(tokens);
        if (!right)
        {
            free_ast(left);
            return NULL;
        }

        t_tree *node = new_ast(GRAM_PIPELINE);
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


t_tree *parse_compound_command(t_token **tokens)
{
    t_tree *left = parse_pipeline(tokens);
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

        t_tree *right = parse_compound_command(tokens);
        if (!right)
        {
            free_ast(left); // Handle memory cleanup
            return NULL;
        }

        t_tree *node = new_ast(GRAM_COMPOUND_COMMAND);
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

t_tree *parse_command_list(t_token **tokens)
{
    t_tree *node = new_ast(GRAM_COMMAND_LIST);
    if (!node)
        return NULL;

    t_tree *compound = parse_compound_command(tokens);
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
    t_tree *next = parse_command_list(tokens);
    if (next)
        insert_arr(node->array, &next);

    return node;
}

t_tree *parse_complete_command(t_token **tokens)
{
    t_tree *node = new_ast(GRAM_COMPLETE_COMMAND);
    if (!node)
        return NULL;

    // Skip any linebreaks (TOKEN_EMPTY if you're using it that way)
    while (*tokens && (*tokens)->type == TOKEN_EMPTY)
        *tokens = (*tokens)->next;

    t_tree *command_list = parse_command_list(tokens);
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
