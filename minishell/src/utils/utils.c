/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 01:05:34 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include "minishell.h"

bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	at_eof(t_token *tok);
t_token	*new_token(char *word, t_token_kind kind);
bool	startswith(const char *s, const char *keyword);
//const char	*token_kind_to_string(t_token_kind kind);

/* ************************************************************************** */
bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

/* ************************************************************************** */
bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}

/* ************************************************************************** */
bool	at_eof(t_token *tok)
{
	return (tok->kind == TOKEN_NULL);
}

/* ************************************************************************** */
t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = xcalloc(1, sizeof(*tok));
	tok->word = word;
	tok->kind = kind;
	if (tok->word)
	{
		if (!ft_strncmp(tok->word, "export", 7) && ft_strlen(tok->word) == 6)
			tok->export_flag = 1;
	}
	else
		tok->export_flag = 0;
	return (tok);
}

/* ************************************************************************** */
bool	startswith(const char *s, const char *keyword)
{
	return (ft_memcmp(s, keyword, ft_strlen(keyword)) == 0);
}

// // //以下はデバッグ用//////////////////////////////////////////////////////////////
// const char *token_kind_to_string(t_token_kind kind)
// {
// 	switch (kind)
// 	{
// 		case TOKEN_WORD:
// 			return "Word";
// 		case TOKEN_NULL:
// 			return "NULL";
// 		default:
// 			return "Operator";
// 	}
// }
// // トークンリストの先頭から末尾まで内容を表示する関数
// void print_token_list(t_token *head)
// {
// 	int i = 0;
// 	t_token *current = head;
// 	while (current != NULL)
// 	{
// 		i++;
// 		// wordがNULLの場合にも対応するためのチェック
// 		printf("%d Token: word = \x1b[41m %s \x1b[0m , kind = %s, 
//				non_double_quote_valuable = %s\n",
// 				i,
// 			   current->word,
// 			   token_kind_to_string(current->kind),
// 			   current->non_double_quote_valuable ? "true" : "false");
// 		printf("Export_Flag = %d\n", current->export_flag);
// 		current = current->next;
// 	}
// }
// // ノードの種類を文字列に変換するヘルパー関数
// const char *node_kind_to_string(t_node_kind kind)
// {
// 	switch (kind)
// 	{
// 		case NODE_PIPELINE:
// 			return "PIPELINE";
// 		case NODE_SIMPLE_CMD:
// 			return "SIMPLE_CMD";
// 		case NODE_REDIR_OUT:
// 			return "REDIR_OUT";
// 		case NODE_REDIR_IN:
// 			return "REDIR_IN";
// 		case NODE_REDIR_APPEND:
// 			return "REDIR_APPEND";
// 		case NODE_REDIR_HEREDOC:
// 			return "REDIR_HEREDOC";
// 		default:
// 			return "UNKNOWN";
// 	}
// }
// // 単一のノードの内容を表示する関数
// void print_node(t_node *node, int index)
// {
// 	if (!node)
// 		return;
// 	printf("%d Node (%p):\n",index, (void*)node);
// 	printf("kind =  \x1b[41m %s \x1b[0m  \n", node_kind_to_string(node->kind));
// 	printf("  targetfd = %d\n", node->targetfd);
// 	printf("  filefd = %d\n", node->filefd);
// 	printf("  stashed_targetfd = %d\n", node->stashed_targetfd);
// 	// args_token の表示
// 	if (node->args_token) {
// 		printf("  args_token:\n");
// 		print_token_list(node->args_token);
// 	} else {
// 		printf("  args_token: NULL\n");
// 	}
// 	// filename_token の表示
// 	if (node->filename_token) {
// 		printf("  filename_token:\n");
// 		print_token_list(node->filename_token);
// 	} else {
// 		printf("  filename_token: NULL\n");
// 	}
// 	// delimiter_token の表示
// 	if (node->delimiter_token) {
// 		printf("  delimiter_token:\n");
// 		print_token_list(node->delimiter_token);
// 	} else {
// 		printf("  delimiter_token: NULL\n");
// 	}
// 	printf("  is_delim_unquoted = %s\n",
//		node->is_delim_unquoted ? "true" : "false");
// 	// redirects_node の表示（再帰的にノードリストとして表示）
// 	if (node->redirects_node) {
// 		printf("  redirects_node:\n");
// 		// 再帰呼び出し
// 		print_node_list(node->redirects_node);
// 	} else {
// 		printf("  redirects_node: NULL\n");
// 	}

// 	// cmd_node の表示（再帰的にノードリストとして表示）
// 	if (node->cmd_node) {
// 		printf("  cmd_node:\n");
// 		// 再帰呼び出し
// 		print_node_list(node->cmd_node);
// 	} else {
// 		printf("  cmd_node: NULL\n");
// 	}
// }
// // ノードリストの先頭から末尾までを表示する関数
// void print_node_list(t_node *head)
// {
// 	int index=1;
// 	t_node *current = head;
// 	while (current != NULL)
// 	{
// 		print_node(current, index);
// 		current = current->next;
// 		printf("\x1b[41m Next Node \x1b[0m\n");
// 		index++;
// 	}
// }
