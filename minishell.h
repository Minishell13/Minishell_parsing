/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:58:45 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/29 14:40:57 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Readline
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_bool
{
	false,
	true,
}					t_bool;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,// |
	TOKEN_REDIR_IN,// <
	TOKEN_REDIR_OUT,// >
	TOKEN_REDIR_APPEND,// >>
	TOKEN_HEREDOC,// <<
	TOKEN_AND,// &&
	TOKEN_OR, // ||
	TOKEN_OPARENTHES,// (
	TOKEN_CPARENTHES,// )
	TOKEN_EMPTY,
}					t_token_type;

typedef enum s_gram
{
	GRAM_COMPLETE_COMMAND,
	GRAM_COMMAND_LIST,
	GRAM_COMPOUND_COMMAND,
	GRAM_PIPE,
	GRAM_COMMAND,
	GRAM_SUBSHELL,
	GRAM_SIMPLE_COMMAND,
	GRAM_WORD_ARRAY,
	GRAM_IO_REDIRECT,
	GRAM_OPERATOR_AND,// &&
	GRAM_OPERATOR_OR,// ||
	GRAM_OPERATOR_PIPE,// |
	GRAM_REDIR_IN,// <
	GRAM_REDIR_OUT,// >
	GRAM_REDIR_APPEND,// >>
	GRAM_HEREDOC,// <<
	GRAM_FILENAME,// filename after redirection
	GRAM_LINEBREAK
}					t_gram;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_list
{
	t_token			*token;// Each list node contains a pointer to a t_token
	struct s_list	*next;// Pointer to the next list node
}					t_list;

typedef struct s_arr
{
	int				size;
	int				used;
	int				elem_size;
	void			*arr;
}					t_arr;


typedef struct	s_redir
{
	char	*file;
	t_bool	expanded;
}				t_redir;

typedef struct s_tree
{
	t_gram			gram;
	union
	{
		char	**args;
		t_redir	redir;
	}	data;
	struct s_tree	*child;
	struct s_tree	*sibling;
}					t_tree;

typedef struct s_parse_data
{
	t_tree *cmd;
	t_tree *rlist;
	t_list *words;
	t_bool flag;
}	t_parse_data;

// lexer
int					is_operator_char(char c);
int					operators(int i, char *line, t_token **head);
int					read_word(int i, char *line, t_token **head);
t_token				*lexer(char *line);

// lexer_command
t_token				*create_token(char *value);
void				token_add_back(t_token **head, t_token *new_token);
t_token_type		get_token_type(char *str);
int					read_quoted_word(int i, char *line);
t_bool				has_unclosed_quotes(char *line);

// lexer_command2
int	read_quoted_if_needed(int i, char *line, char *quot);
int	read_operator_if_needed(int i, char *line, t_token **head);
int	read_word_loop(int i, char *line);
int	handle_quotation_end(int i, char quot, char *line);

// tree_array
t_tree				*new_tree_node(t_gram gram);
t_tree				*new_tree_leaf(t_gram gram, char *s);
void				tree_add_child(t_tree *parent, t_tree *c);
void				tree_add_sibling(t_tree *node, t_tree *sib);
void				append_to_list(t_list **list, t_list *new_node);

// Parser
t_tree				*parse_command(t_token **tokens);
t_tree				*parse_pipe(t_token **tokens);
t_tree				*parse_compound_command(t_token **tokens);
t_tree				*parse_command_list(t_token **tokens);
t_tree				*parse_complete_command(t_token **tokens);

// Parser2
t_tree				*parse_subshell(t_token **tokens);
t_tree				*parse_redirect_list(t_token **tokens);
t_tree				*parse_simple_command(t_token **tokens);

// parsing_command
int					count_words(t_list *word_list);
int					fill_words_array(char **arr, t_list *word_list);
t_list				*collect_words(t_token **tokens);
t_bool				fill_args(t_tree *cmd, t_list *words);
t_bool				has_subshell_error(t_token **tokens);

// parsing_command2
void				skip_empty_tokens(t_token **tokens);
int					is_redirect_token(t_token *token);
t_tree				*create_redirect_node(t_token_type type,
						char *file, t_tree *list);
int					handle_redirection(t_token **tokens, t_tree *list);
t_tree				*handle_compound_op(t_token **tokens, t_tree *left, t_token_type op);

// parsing_command3
int	consume_token_type(t_token **tokens, t_token_type type);
t_bool	check_subshell_errors(t_tree *inner, t_token **tokens, t_token **after_paren);
t_bool	is_invalid_start_token(t_token **tokens);
t_bool	has_extra_tokens(t_token **tokens);
t_bool	is_invalid_pipe_token(t_token *token);

#endif