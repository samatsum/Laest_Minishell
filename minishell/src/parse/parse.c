/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:54:56 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 18:25:31 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node			*parse_commands(t_token **rest, t_token *tok, t_context *ctx);
static t_node	*simple_cmd(t_token **rest, t_token *tok, t_context *ctx);
static void		append_cmd_element(t_node *cmd, t_token **rest, t_token *tok, \
	t_context *ctx);
static void		append_node(t_node **node, t_node *elm);
static bool		is_control_operator(t_token *tok);

/* ************************************************************************** */
t_node	*parse_commands(t_token **rest, t_token *tok, t_context *ctx)
{
	t_node	*node;

	node = new_node(NODE_PIPELINE);
	node->inter_process_pipe[0] = STDIN_FILENO;
	node->inter_process_pipe[1] = STDOUT_FILENO;
	node->input_fd = STDIN_FILENO;
	node->cmd_node = simple_cmd(&tok, tok, ctx);
	if (equal_op(tok, "|"))
		node->next = parse_commands(&tok, tok->next, ctx);
	*rest = tok;
	return (node);
}

/* ************************************************************************** */
static t_node	*simple_cmd(t_token **rest, t_token *tok, t_context *ctx)
{
	t_node	*node;

	node = new_node(NODE_SIMPLE_CMD);
	append_cmd_element(node, &tok, tok, ctx);
	while (tok && !at_eof(tok) && !is_control_operator(tok))
		append_cmd_element(node, &tok, tok, ctx);
	if (node->args_token == NULL && node->redirects_node != NULL \
		&& node->redirects_node->kind == NODE_REDIR_HEREDOC)
		node->args_token = new_token(xstrdup("cat"), TOKEN_WORD);
	*rest = tok;
	return (node);
}

/* ************************************************************************** */
static void	append_cmd_element(t_node *cmd, t_token **rest, t_token *tok, \
	t_context *ctx)
{
	if (tok->kind == TOKEN_WORD)
	{
		append_tok(&cmd->args_token, tokdup(tok));
		tok = tok->next;
	}
	else if (equal_op(tok, ">") && tok->next->kind == TOKEN_WORD)
		append_node(&cmd->redirects_node, redirect_out(&tok, tok));
	else if (equal_op(tok, "<") && tok->next->kind == TOKEN_WORD)
		append_node(&cmd->redirects_node, redirect_in(&tok, tok));
	else if (equal_op(tok, ">>") && tok->next->kind == TOKEN_WORD)
		append_node(&cmd->redirects_node, redirect_append(&tok, tok));
	else if (equal_op(tok, "<<") && tok->next->kind == TOKEN_WORD)
		append_node(&cmd->redirects_node, redirect_heredoc(&tok, tok));
	else
		parse_error("append_command_element", &tok, tok, ctx);
	*rest = tok;
}

/* ************************************************************************** */
static void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}

/* ************************************************************************** */
static bool	is_control_operator(t_token *tok)
{
	static char *const	operators[] = {"|", "\n"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(tok->word, operators[i]))
			return (true);
		i++;
	}
	return (false);
}
