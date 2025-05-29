/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:39:01 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/29 14:39:33 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	read_quoted_if_needed(int i, char *line, char *quot)
{
	if (line[i] == '\'' || line[i] == '"')
	{
		*quot = line[i];
		read_quoted_word(i, line);
	}
	return (i);
}

int	read_operator_if_needed(int i, char *line, t_token **head)
{
	if (line[i] == '&' && line[i + 1] == line[i])
	{
		i = operators(i, line, head);
		return (i);
	}
	return (-1);
}

int	read_word_loop(int i, char *line)
{
	while (line[i] && !is_operator_char(line[i]) && (line[i] != 32
			&& (line[i] < 9 || line[i] > 13)))
	{
		if (line[i] == '&' && line[i + 1] == '&')
			break ;
		i++;
	}
	return (i);
}

int	handle_quotation_end(int i, char quot, char *line)
{
	if (quot && line[i--] != quot)
	{
		while (line[i] && line[i] != quot)
			i++;
		if (line[i] == quot)
			i++;
	}
	return (i);
}
