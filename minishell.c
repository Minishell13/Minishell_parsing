/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:45:00 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/22 12:44:09 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
    t_token *head;
    char *line;

    (void)ac;
    (void)av;
    (void)env;
    line = get_next_line(0);
    while (line)
    {
        head = lexer(line);
        while (head)
        {
            printf("( %s ) --> %d \n", head->value, head->type);
            head = head->next; 
        }
        line = get_next_line(0);
    }
}