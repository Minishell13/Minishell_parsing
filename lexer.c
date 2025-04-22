/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:00:23 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/22 13:18:14 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token_type get_token_type(char *str)
{
    if (str == NULL || *str == '\0')
        return TOKEN_EMPTY;
    if (str[0] == '"')
        return  TOKEN_QUOTES;
    else if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
        return TOKEN_PIPE;
    else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
        return TOKEN_REDIR_OUT;
    else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
        return TOKEN_REDIR_IN;
    else if (ft_strncmp(str, "&&", ft_strlen(str)) == 0)
        return TOKEN_AND;
    else if (ft_strncmp(str, "||", ft_strlen(str)) == 0)
        return TOKEN_OR;
    else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
        return  TOKEN_REDIR_APPEND;
    return TOKEN_COMMAND;
}

t_token *create_token(char *value)
{
    t_token *token;

    if (!value)
        return NULL;
    token = malloc(sizeof(t_token));
    token->value = ft_strdup(value);
    token->type = get_token_type(value);
    token->next = NULL; 
    return (token);
}

void token_add_back(t_token **head, t_token *new_token)
{
    t_token *tmp;

    if (!*head)
    {
        *head = new_token;
        return ;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_token;
}

// t_bool check_str_command(char *str)
// {
//     int i;
//     int type;
//     char **command;

//     i = 0;
//     while (str[i])
//     {
//         if (str[i] == '|' && str[i + 1] != '|' && str[i - 1] != '|')
//             type = 0;
//         if (str[i] == '&' && str[i + 1] == '&' && str[i - 1] != '&')
//             type = 1;
//         if (str[i] == '|' && str[i + 1] == '|' && str[i - 1] != '|')
//             type = 2;
//         if (str[i] == '>' && str[i + 1] == '>' && str[i - 1] != '>')
//             type = 3;
//         if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
//             type = 4;
//         if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
//             type = 5;
//     }
//     command = ft_split(str, '|');
// }

// t_token *tokenize(char *line)
// {
//     t_token *head;
//     char **commands;
//     int i;
//     int j;

//     commands = ft_split(line, ' ');
//     i = 0;
//     head  = NULL;
//     while (commands[i])
//     {
//         j = 0;
//         while (commands[i][j])
//         {
//             if (commands[i][j] == '\n')
//                 commands[i][j] = '\0';
//             j++;
//         }
//         if (check_str_command(commands[i]) == false)
//             token_add_back(&head, create_token(commands[i]));
//         i++;
//     }
//     return head;
// }

int is_operator_char(char c) 
{
    return (c == '|' || c == '&' || c == '<' || c == '>');
}

t_token *lexer(char *line) 
{
    int i;
    char *word;
    int start;
    t_token *head = NULL;

    i = 0;
    while (line[i]) 
    {
        if (line[i] == ' ' || line[i] == '\t') 
        {
            i++;
            continue;
        }

        // Handle operators like &&, ||, >>
        if (is_operator_char(line[i]))
        {
            start = i;
            if (line[i + 1] && line[i + 1] == line[i]) 
            {
                if (line[i + 2] && line[i + 2] == line[i])
                {
                    printf("syntax error: too many '%c'\n", line[i]);
                    return (NULL);
                }
                i++;
            }
            i++;
            word = ft_substr(line, start, i - start);
            if (!word)
                return (NULL);
            token_add_back(&head, create_token(word));
            free(word);
            if (line[i] == '\n')
                line[i] = '\0';
        }
        else if (line[i] == '"')
        {
            // read until you found close quote
            start = i;
            i++;
            while (line[i])
            {
                if (line[i] == '"')
                {
                    i++;
                    break;
                }
                if (line[i + 1] == '\0')
                {
                    printf("syntax error: missing closing quote\n");
                    return (NULL);
                }
                i++;
            }
            word = ft_substr(line, start, i - start);
            if (!word)
                return (NULL);
            token_add_back(&head, create_token(word));
            free(word);
            if (line[i] == '\n')
                line[i] = '\0';
        }
        else
        {
            // Read a word until next space or operator
            start = i;
            while (line[i] && !is_operator_char(line[i]) && line[i] != ' ' && line[i] != '\t' && line[i] != '"')
                i++;
            if (line[i - 1] == '\n')
                line[i - 1] = '\0';
            word = ft_substr(line, start, i - start);
            if (!word)
                return (NULL);
            token_add_back(&head, create_token(word));
            free(word);
        }
    }
    return head;
}
