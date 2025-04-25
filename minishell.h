/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:58:45 by hwahmane          #+#    #+#             */
/*   Updated: 2025/04/25 16:47:26 by hwahmane         ###   ########.fr       */
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
    
    typedef enum s_gram 
    {
        GRAM_COMPLETE_COMMAND,
        GRAM_COMMAND_LIST,
        GRAM_COMPOUND_COMMAND,
        GRAM_PIPELINE,
        GRAM_COMMAND,
        GRAM_SUBSHELL,
        GRAM_SIMPLE_COMMAND,
        GRAM_REDIRECT_LIST,
        GRAM_IO_REDIRECT,
        GRAM_WORD_ARRAY,
        GRAM_OPERATOR_AND,     // &&
        GRAM_OPERATOR_OR,      // ||
        GRAM_OPERATOR_PIPE,    // |
        GRAM_REDIR_IN,         // <
        GRAM_REDIR_OUT,        // >
        GRAM_REDIR_APPEND,     // >>
        GRAM_HEREDOC,          // <<
        GRAM_FILENAME,         // filename after redirection
        GRAM_LINEBREAK
    } t_gram;
    
    
    typedef struct s_token 
    {
        t_token_type type;
        char *value;
        struct s_token *next;
    } t_token;
    

    typedef struct s_list {
        t_token *token;          // Each list node contains a pointer to a t_token
        struct s_list *next;     // Pointer to the next list node
    } t_list;


    typedef struct s_arr {
        int size;
        int used;
        int elem_size;
        void *arr;
    } t_arr;
    
    typedef struct s_tree {
        t_gram        gram;      // grammar node type
        char         *str;       // only non-NULL for WORD / filename leaves
        char        **words;
        struct s_tree *child;
    struct s_tree *sibling;
} t_tree;

// lexer
t_token *lexer(char *line);

// lexer_command
void token_add_back(t_token **head, t_token *new_token);
t_token *create_token(char *value);
void token_add_back(t_token **head, t_token *new_token);


t_tree *parse_complete_command(t_token **tokens);
t_tree *parse_command_list(t_token **tokens);
t_tree *parse_compound_command(t_token **tokens);
t_tree *parse_pipeline(t_token **tokens);
t_tree *parse_command(t_token **tokens);
t_tree *parse_subshell(t_token **tokens);
t_tree *parse_simple_command(t_token **tokens);
t_tree *parse_redirect_list(t_token **tokens);
t_tree *parse_io_redirect(t_token **tokens);
t_tree *parse_word(t_token **tokens);

void tree_add_sibling(t_tree *node, t_tree *sib);
void tree_add_child(t_tree *parent, t_tree *c);
t_tree *new_tree_leaf(t_gram gram, char *s);
t_tree *new_tree_node(t_gram gram);
t_list *create_list_node(char *word);
void append_to_list(t_list **list, t_list *new_node);

#endif