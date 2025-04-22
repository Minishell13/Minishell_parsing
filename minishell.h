/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:58:45 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/22 11:49:52 by hwahmane         ###   ########.fr       */
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
    TOKEN_COMMAND,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,    // <
    TOKEN_REDIR_OUT,   // >
    TOKEN_REDIR_APPEND,// >>
    TOKEN_AND,         // &&
    TOKEN_OR,          // ||
    TOKEN_EMPTY,
} t_token_type;

typedef struct s_token 
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

// typedef struct s_ast {
//     t_token_type type;
//     char **cmd;                 // Only used for NODE_COMMAND
//     char *file;                 // Used for redirections
//     struct s_ast *left;
//     struct s_ast *right;
// } t_ast;


t_token *tokenize(char *line);
t_token *lexer(char *line);



#endif