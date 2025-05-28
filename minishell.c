/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:45:00 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/28 18:10:04 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const char *get_node_type_name(int type)
{
    switch (type)
    {
        case GRAM_COMPLETE_COMMAND: return "COMPLETE_COMMAND";
        case GRAM_COMMAND_LIST:     return "COMMAND_LIST";
        case GRAM_IO_REDIRECT:      return "IO_REDIRECT";
        case GRAM_COMPOUND_COMMAND: return "COMPOUND_COMMAND";
        case GRAM_PIPE:             return "PIPE";
        case GRAM_SIMPLE_COMMAND:   return "SIMPLE_COMMAND";
        case GRAM_OPERATOR_AND:     return "AND";
        case GRAM_OPERATOR_OR:      return "OR";
        case GRAM_REDIR_IN:         return "REDIR_IN";
        case GRAM_REDIR_OUT:        return "REDIR_OUT";
        case GRAM_REDIR_APPEND:     return "REDIR_APPEND";
        case GRAM_HEREDOC:          return "HEREDOC";
        case GRAM_FILENAME:         return "FILENAME";
        case GRAM_WORD_ARRAY:       return "WORD_ARRAY";
        case GRAM_SUBSHELL:         return "SUBSHELL";
        default:                    return "UNKNOWN";
    }
}
void print_tree(t_tree *node, int indent)
{
    if (!node)
        return;

    printf("%*s%s", indent * 2, "", get_node_type_name(node->gram));

    if (node->gram == GRAM_SIMPLE_COMMAND && node->data.args)
    {
        char **words = node->data.args;
        printf(": [");
        for (int i = 0; words[i]; i++)
        {
            printf("\"%s\"", words[i]);
            if (words[i + 1])
                printf(", ");
        }
        printf("]");
    }
    else if (node->gram == GRAM_HEREDOC || node->gram == GRAM_REDIR_IN || node->gram == GRAM_REDIR_OUT || node->gram == GRAM_REDIR_APPEND)
        printf(": \"%s\" , %u", node->data.redir.file, node->data.redir.expanded);
        

    printf("\n");

    print_tree(node->child, indent + 1);
    print_tree(node->sibling, indent);
}


// int main(int ac, char **av, char **env)
// {
//     t_token *head;
//     t_tree *tree;
//     char *line;

//     (void)ac;
//     (void)av;
//     (void)env;
    
//     line = get_next_line(0);
//     while (line)
//     {
//         head = lexer(line);
//         tree = parse_complete_command(&head);
//         if (tree)
//         {
//             print_tree(tree, 0);
//         }
//         else
//         {
//             printf("\n");
//         }
//         line = get_next_line(0);
//     }
    
//     return 0;
// }



int	main(int ac, char **av, char **ev)
{
    t_token *head;
    t_tree *tree;
    char *line;

    (void)ac;
    (void)av;
    (void)ev;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
        if (*line)
	 		add_history(line);

        // TODO: Put the parser logic here, [Just get the line from readline (like get_next_line)]
        head = lexer(line);
        tree = parse_complete_command(&head);
        if (tree)
        {
            print_tree(tree, 0);
        }
        else
        {
            printf("\n");
        }
        
		// printf("line: %s\n", line);
		free(line);
	}
    rl_clear_history();

	return (EXIT_SUCCESS);
}


