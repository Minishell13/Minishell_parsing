/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahmane <wahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:00:23 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/30 17:27:29 by wahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '(' || c == ')');
}

// Handle operators like &&, ||, >>
int	operators(int i, char *line, t_token **head)
{
	int		start;
	char	*word;

	if (line[i] == '\0')
		return (i);
	start = i;
	if (line[i + 1] && line[i + 1] == line[i] && (line[i] != '('
			|| line[i] != ')'))
		i++;
	i++;
	word = ft_substr(line, start, i - start);
	if (!word)
		return (-1);
	token_add_back(head, create_token(word));
	free(word);
	if (line[i] == '\n')
		line[i] = '\0';
	return (i);
}

// Read a word until next space or operator
int	read_word(int i, char *line, t_token **head)
{
	int		start;
	char	*word;

	if (line[i] == '&' && line[i + 1] == line[i])
	{
		i = operators(i, line, head);
		return (i);
	}
	start = i;
	while (line[i] && !is_operator_char(line[i]) && (line[i] != 32
			&& (line[i] < 9 || line[i] > 13)))
	{
		if ((line[i] == '&' && line[i + 1] == '&'))
			break ;
		i++;
	}
	if (line[i] == '\n')
		line[i] = '\0';
	word = ft_substr(line, start, i - start);
	if (!word)
		return (-1);
	token_add_back(head, create_token(word));
	free(word);
	return (i);
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*head;

	head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (is_operator_char(line[i]))
			i = operators(i, line, &head);
		else
		{
			if (line[i] != '\0')
				i = read_word(i, line, &head);
		}
		if (i == -1)
			return (NULL);
	}
	return (head);
}
