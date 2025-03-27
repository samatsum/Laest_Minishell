/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:31:57 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 00:35:10 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "minishell.h"
#include <stdio.h>

void		unclose_error(const char *location, char **rest, char *line, \
	t_context *ctx);
void		tokenize_error(const char *location, char **rest, t_token *tok, \
	t_context *ctx);
void		parse_error(const char *location, t_token **rest, t_token *tok, \
	t_context *ctx);
static void	print_syntax_error(const char *location, t_token *tok);
static void	process(char **rest, char *line);

/* ************************************************************************** */
void	unclose_error(const char *location, char **rest, char *line, \
	t_context *ctx)
{
	ctx->syntax_error = true;
	perror_prefix();
	ft_dprintf(STDERR_FILENO,
		"syntax error near unexpected token `%s' in %s\n", line, location);
	process(rest, line);
}

/* ************************************************************************** */
void	tokenize_error(const char *location, char **rest, t_token *tok, \
	t_context *ctx)
{
	ctx->syntax_error = true;
	perror_prefix();
	print_syntax_error(location, tok);
	process(rest, *rest);
}

/* ************************************************************************** */
void	parse_error(const char *location, t_token **rest, t_token *tok, \
	t_context *ctx)
{
	if (tok->next && tok->next->kind == TOKEN_PIPE)
		tok = tok->next;
	ctx->syntax_error = true;
	perror_prefix();
	print_syntax_error(location, tok);
	while (tok && !at_eof(tok))
		tok = tok->next;
	*rest = tok;
}

/* ************************************************************************** */
static void	print_syntax_error(const char *location, t_token *tok)
{
	if (tok->kind == TOKEN_PIPE)
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token `|' in %s\n", location);
	else if (ft_strcmp(tok->word, ">>") == 0 && tok->next \
				&& ft_strcmp(tok->next->word, ">") == 0)
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token `>' in %s\n", location);
	else if (tok->kind == TOKEN_REDIR_OUT)
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token `>(newline)' in %s\n", location);
	else if (tok->kind == TOKEN_REDIR_IN)
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token `<(newline)' in %s\n", location);
	else if (tok->kind == TOKEN_REDIR_APPEND)
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token `>>(newline)' \
				in %s\n", location);
	else if (tok->kind == TOKEN_REDIR_HEREDOC)
		ft_dprintf(STDERR_FILENO, "syntax error near unexpected token `<<(newline)' \
			in %s\n", location);
	else
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token `%s' \
				in %s\n", tok->word, location);
}

/* ************************************************************************** */
static void	process(char **rest, char *line)
{
	while (*line)
		line++;
	*rest = line;
}

	// else if (tok->kind== TOKEN_SEMICOLON)
	// 	ft_dprintf(STDERR_FILENO,
	// 		"syntax error near unexpected token `;'\n");
	// else if (tok->kind== TOKEN_AND)
	// 	ft_dprintf(STDERR_FILENO,
	// 		"syntax error near unexpected token `&&'\n");
	// else if (tok->kind== TOKEN_OR)
	// 	ft_dprintf(STDERR_FILENO,
	// 		"syntax error near unexpected token `||'\n");
	// else if (tok->kind== TOKEN_REDIR)
	// 	ft_dprintf(STDERR_FILENO,
	// 		"syntax error near unexpected token `newline'\n");
	// else if (tok->kind== TOKEN_REDIR_ARG)
	// 	ft_dprintf(STDERR_FILENO,
	// 		"syntax error near unexpected token `newline'\n");