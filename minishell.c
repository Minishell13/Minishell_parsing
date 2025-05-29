/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:45:00 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/29 18:10:22 by hwahmane         ###   ########.fr       */
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

    if (node->gram == GRAM_SIMPLE_COMMAND && node->u_data.args)
    {
        char **words = node->u_data.args;
        printf(": [");
        for (int i = 0; words[i]; i++)
        {
            printf(" %s ", words[i]);
            if (words[i + 1])
                printf(", ");
        }
        printf("]");
    }
    else if (node->gram == GRAM_HEREDOC || node->gram == GRAM_REDIR_IN || node->gram == GRAM_REDIR_OUT || node->gram == GRAM_REDIR_APPEND)
        printf(": \"%s\" , %u", node->u_data.redir.file, node->u_data.redir.expanded);
        

    printf("\n");

    print_tree(node->child, indent + 1);
    print_tree(node->sibling, indent);
}

void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

void free_list(t_list *list)
{
    t_list *tmp;

    while (list)
    {
        tmp = list->next;
        free(list);  // only free the list node itself
        list = tmp;
    }
}

void	free_tree(t_tree *node)
{
	t_tree	*next;

	while (node)
	{
		next = node->sibling;

		// Free args for SIMPLE_COMMAND
		if (node->gram == GRAM_SIMPLE_COMMAND && node->u_data.args)
			free_string_array(node->u_data.args);

		// Free file for any redirection node
		else if ((node->gram == GRAM_IO_REDIRECT
				|| node->gram == GRAM_REDIR_IN
				|| node->gram == GRAM_REDIR_OUT
				|| node->gram == GRAM_REDIR_APPEND
				|| node->gram == GRAM_HEREDOC)
				&& node->u_data.redir.file)
			free(node->u_data.redir.file);

		// Recurse on children (command_list inside subshell, etc.)
		if (node->child)
			free_tree(node->child);

		free(node);
		node = next;
	}
}


void	free_all(t_token *token, t_tree *tree)
{
	free_tokens(token);
	free_tree(tree);
}


void print_tokens(t_token *head)
{
    if (!head)
    {
        printf("NULL");
        return;
    }
    while (head)
    {
        printf("TOKEN: %s\n", head->value);
        head = head->next;
    }
}
int	main(int ac, char **av, char **ev)
{
    t_token *head;
    t_token *head_root;
    t_tree *tree;
    char *line;

    (void)ac;
    (void)av;
    (void)ev;
	head = NULL;
	head_root = NULL;
    tree = NULL;
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

        // Free previous allocations before new ones
        free_all(head_root, tree);
        head = NULL;
        tree = NULL;

        head = lexer(line);
        if (!head)
        {
            free(line);
            continue; // or handle lexer failure
        }
        head_root = head;
        tree = parse_complete_command(&head);
        if (tree)
        {
            print_tree(tree, 0);
        }
        else
        {
            printf("\n");
        }
        free(line);
    }
    rl_clear_history();
    free_all(head_root, tree);
	return (EXIT_SUCCESS);
}


