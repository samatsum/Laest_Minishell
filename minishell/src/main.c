/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:21:33 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 21:02:15 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "get_next_line.h"

int			main(void);
static void	interpret(char *line, t_context *ctx);

volatile sig_atomic_t	g_signal_received = 0;

/* ************************************************************************** */
int	main(void)
{
	char		*line;
	t_context	ctx;

	ft_memset(&ctx, 0, sizeof(t_context));
	initenv(&ctx);
	setup_signal();
	ctx.last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			if (g_signal_received == SIGINT)
			{
				g_signal_received = 0;
				continue ;
			}
			break ;
		}
		if (*line)
			add_history(line);
		interpret(line, &ctx);
	}
	exit(ctx.last_status);
}

/* ************************************************************************** */
static void	interpret(char *line, t_context *ctx)
{
	t_token	*tok;
	t_token	*tok_head;
	t_node	*node;

	tok = tokenize(line, ctx);
	free(line);
	line = NULL;
	tok_head = tok;
	if (at_eof(tok))
		return ((void)free_tok(tok_head));
	if (ctx->syntax_error)
	{
		ctx->last_status = ERROR_TOKENIZE;
		return ((void)free_tok(tok_head));
	}
	node = parse_commands(&tok, tok, ctx);
	if (ctx->syntax_error)
		ctx->last_status = ERROR_PARSE;
	else
	{
		expand(node, ctx);
		ctx->last_status = exec(node, ctx);
	}
	free_node(node);
	free_tok(tok_head);
}
