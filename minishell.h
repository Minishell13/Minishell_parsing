/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:58:45 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/22 19:12:55 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./get_next_line/get_next_line.h"
# include "./Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum s_bool
{
    false,
    true,
}   t_bool;

typedef enum s_token_type 
{
    TOKEN_WORD,
    TOKEN_PIPE,        // |
    TOKEN_REDIR_IN,    // <
    TOKEN_REDIR_OUT,   // >
    TOKEN_REDIR_APPEND,// >>
    TOKEN_HEREDOC,     // <<
    TOKEN_AND,         // &&
    TOKEN_OR,          // ||
    TOKEN_OPARENTHES,  // (
    TOKEN_CPARENTHES,  // )
    TOKEN_EMPTY,
} t_token_type;

typedef struct s_token 
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

typedef struct s_arr {
    int size;
    int used;
    int elem_size;
    struct s_arr *arr;
} t_arr;

typedef struct s_ast {
    struct s_arr arr;
} t_ast;

// lexer
t_token *lexer(char *line);

// lexer_command
void token_add_back(t_token **head, t_token *new_token);
t_token *create_token(char *value);
void token_add_back(t_token **head, t_token *new_token);




#endif