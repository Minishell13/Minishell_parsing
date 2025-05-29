/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:49:57 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/29 14:05:11 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// t_tree *parse_simple_command(t_token **tokens)
// {
//     t_bool flag;
//     t_tree *cmd;
//     t_tree *rlist;
//     t_list *words;
//     t_list *last_word;
//     t_list *new_word;
//     int count;
//     t_token *cursor;
//     t_bool found_word;

//     words = NULL;
//     cursor = *tokens;
//     found_word = false;
//     rlist = NULL;
//     last_word = NULL;
//     flag = true;
//     cmd = NULL;
//     while (cursor)
//     {
//         if (is_redirect_token(cursor))
//         {
//             cursor = cursor->next;
//             if (cursor && cursor->type == TOKEN_WORD)
//                 cursor = cursor->next;
//         }
//         else if (cursor->type == TOKEN_WORD)
//         {
//             found_word = true;
//             break;
//         }
//         else
//             break;
//     }
//     if (found_word)
//         cmd = new_tree_node(GRAM_SIMPLE_COMMAND);
//     else if (is_redirect_token((*tokens)))
//     {
//         cmd = new_tree_node(GRAM_IO_REDIRECT);
//         flag = false;
//     }
//     if (!cmd)
//         return NULL;
//     while (*tokens && ((*tokens)->type == TOKEN_WORD || is_redirect_token(*tokens)))
//     {
//         if ((*tokens)->type == TOKEN_WORD)
//         {
//             new_word = malloc(sizeof(t_list));
//             if (!new_word)
//                 return NULL;
//             new_word->token = *tokens;
//             new_word->next = NULL;

//             if (!words)
//                 words = new_word;
//             else
//                 last_word->next = new_word;
//             last_word = new_word;

//             *tokens = (*tokens)->next;
//         }
//         else if (is_redirect_token(*tokens))
//         {
//             if (flag && !rlist)
//             {
//                 rlist = new_tree_node(GRAM_IO_REDIRECT);
//                 if (!rlist)
//                     return NULL;
//             }
//             if (flag)
//             {
//                 if (!handle_redirection(tokens, rlist))
//                     return NULL;
//             }
//             else
//                 if (!handle_redirection(tokens, cmd))
//                 return NULL;
//         }
//     }
//     if (cmd && *tokens && ((*tokens)->type == TOKEN_OPARENTHES))
//     {
//         skip_empty_tokens(tokens);
//         if ((*tokens)->next)
//             printf("syntax error: near unexpected token `%s'",(*tokens)->next->value);
//         else
//             parse_subshell(tokens);
//         return NULL;
//     }
//     if (flag)
//     {
//         if (!words)
//             return NULL;
//         count = count_words(words);
//         cmd->data.args = malloc(sizeof(char *) * (count + 1));
//         if (!cmd->data.args || !fill_words_array(cmd->data.args, words))
//             return NULL;
//     }
//     if (flag)
//         tree_add_child(cmd, rlist);
//     return cmd;
// }

// ------------------------------

// t_tree	*parse_subshell(t_token **tokens)
// {
// 	t_tree	*node;
// 	t_tree	*inner;
// 	t_token	*after_paren;

// 	if (!consume_token_type(tokens, TOKEN_OPARENTHES))
// 		return (NULL);
// 	skip_empty_tokens(tokens);
// 	inner = parse_command_list(tokens);
// 	if (!inner)
// 		return (printf("syntax error: empty subshell or invalid content\n"),
// 				NULL);
// 	skip_empty_tokens(tokens);
// 	if (inner->sibling)
// 		return (printf("syntax error: multiple commands in subshell without operator\n"),
// 				NULL);
// 	if (!consume_token_type(tokens, TOKEN_CPARENTHES))
// 		return (printf("syntax error: expected ')'\n"), NULL);
// 	after_paren = *tokens;
// 	skip_empty_tokens(&after_paren);
// 	if (after_paren && after_paren->type == TOKEN_OPARENTHES)
// 	{
// 		printf("syntax error: unexpected '('\n");
// 		return (NULL);
// 	}
// 	node = new_tree_node(GRAM_SUBSHELL);
// 	if (!node)
// 		return (NULL);
// 	tree_add_child(node, inner);
// 	return (node);
// }

// ------------------------------

// t_tree *parse_compound_command(t_token **tokens)
// {
//     t_tree *node;
//     t_tree *left;
//     t_tree *right;
//     t_token_type op;

//     left = parse_pipeline(tokens);
//     if (!left)
//         return NULL;
//     while (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
//     {
//         op = (*tokens)->type;
//         *tokens = (*tokens)->next;
//         if (!*tokens || (*tokens)->type == TOKEN_CPARENTHES || (*tokens)->type == TOKEN_PIPE
//             || (*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR)
//         {
//             printf("syntax error: unexpected token after '%s'\n", op == TOKEN_AND ? "&&" : "||");
//             return NULL;
//         }
//         right = parse_pipeline(tokens);
//         if (!right)
//             return NULL;
//         if (op == TOKEN_AND)
//             node = new_tree_node(GRAM_OPERATOR_AND);
//         else
//             node = new_tree_node(GRAM_OPERATOR_OR);
//         tree_add_child(node, left);
//         tree_add_child(node, right);
//         left = node;
//     }
//     return left;
// }

// ------------------------------

// t_tree	*parse_complete_command(t_token **tokens)
// {
// 	t_tree	*cmds;
// 	t_tree	*root;

// 	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
// 		*tokens = (*tokens)->next;
// 	if (*tokens && (*tokens)->type == TOKEN_CPARENTHES)
// 	{
// 		printf("syntax error: unexpected ')'\n");
// 		return (NULL);
// 	}
// 	cmds = parse_command_list(tokens);
// 	if (!cmds)
// 		return (NULL);
// 	while (*tokens && (*tokens)->type == TOKEN_EMPTY)
// 		*tokens = (*tokens)->next;
// 	if (*tokens)
// 	{
// 		if ((*tokens)->type == TOKEN_CPARENTHES)
// 			printf("syntax error: unexpected ')'\n");
// 		else
// 			printf("syntax error: unexpected token after command\n");
// 		return (NULL);
// 	}
// 	root = new_tree_node(GRAM_COMPLETE_COMMAND);
// 	tree_add_child(root, cmds);
// 	return (root);
// }