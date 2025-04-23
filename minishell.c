/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:45:00 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/23 16:46:52 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const char *get_node_type_name(int type)
{
    switch (type)
    {
        case GRAM_COMPLETE_COMMAND: return "COMPLETE_COMMAND";
        case GRAM_COMMAND_LIST: return "COMMAND_LIST";
        case GRAM_COMPOUND_COMMAND: return "COMPOUND_COMMAND";
        case GRAM_PIPELINE: return "PIPELINE";
        case GRAM_SIMPLE_COMMAND: return "SIMPLE_COMMAND";
        case GRAM_REDIRECT_LIST: return "REDIRECT_LIST";
        case GRAM_OPERATOR_AND: return "AND";
        case GRAM_OPERATOR_OR: return "OR";
        // Add more as needed
        default: return "UNKNOWN";
    }
}

void print_ast_tree(t_ast *node, int indent)
{
    if (!node || !node->array)
        return;

    for (int i = 0; i < indent; i++)
        printf("  ");
    printf("Node type: %s\n", get_node_type_name(node->value));

    for (int i = 0; i < node->array->used; i++)
    {
        void *item = *(void **)((char *)node->array->arr + i * node->array->elem_size);
        if (!item)
            continue;

        if (node->value == GRAM_SIMPLE_COMMAND || node->value == GRAM_REDIRECT_LIST)
        {
            char *maybe_str = (char *)item;
            if (maybe_str)
            {
                for (int j = 0; j < indent + 1; j++)
                    printf("  ");
                printf("Value: %s\n", maybe_str);
                continue;
            }
        }

        // Otherwise, treat it as a child node
        print_ast_tree((t_ast *)item, indent + 1);
    }
}





int main(int ac, char **av, char **env)
{
    t_token *head;
    t_ast *ast_root;
    char *line;

    (void)ac;
    (void)av;
    (void)env;
    
    line = get_next_line(0);  // Reading input line by line
    
    while (line)
    {
        // Tokenize the input line
        head = lexer(line);
                
        // Parse the tokens into an AST (assuming `parse_complete_command` is the main entry point)
        ast_root = parse_complete_command(&head);  // head now points to the list of tokens
        
        // Optionally, process the AST or print it out (depends on your use case)
        if (ast_root)
        {
            print_ast_tree(ast_root, 0);
        }
        else
        {
            printf("Error parsing tokens\n");
        }
        
        // Free the allocated memory for the tokens and AST
        free_ast(ast_root); // Implement a function to free the AST
        
        // Read the next line
        line = get_next_line(0);
    }
    
    return 0;
}
