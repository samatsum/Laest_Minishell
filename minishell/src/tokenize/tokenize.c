/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:11:33 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 18:43:27 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include "minishell.h"

t_token			*tokenize(char *line, t_context *ctx);
static bool		consume_blank(char **next_line, char *line);
bool			is_metacharacter(char c);
static t_token	*operator(char **rest, char *line);
static int		set_operator_token(char *op);

/* ************************************************************************** */
t_token	*tokenize(char *line, t_context *ctx)
{
	t_token	head;
	t_token	*tok;

	ctx->syntax_error = false;
	head.next = NULL;
	tok = &head;
	tok->kind = 0;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		if (*line && is_metacharacter(*line))
			tok->next = operator(&line, line);
		else if (*line && !is_metacharacter(*line))
			tok->next = word(&line, line, ctx);
		tok = tok->next;
	}
	if ((&head)->next && (&head)->next->kind != TOKEN_WORD \
			&& (&head)->next->kind != TOKEN_REDIR_HEREDOC)
		tokenize_error("Unexpected Token", &line, (&head)->next, ctx);
	else if (tok->kind != TOKEN_WORD)
		tokenize_error("Unexpected Token", &line, tok, ctx);
	tok->next = new_token(NULL, TOKEN_NULL);
	return (head.next);
}

/* ************************************************************************** */
static bool	consume_blank(char **next_line, char *line)
{
	while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
		line++;
	*next_line = line;
	return (*line == '\0');
}

/* ************************************************************************** */
bool	is_metacharacter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	return (c && ft_strchr("|<>\n", c));
}

/* ************************************************************************** */
static t_token	*operator(char **rest, char *line)
{
	static char *const	operators[] = {">>", "<<", "<", ">", "|", "\n"};
	size_t				i;				
	char				*op;
	int					op_token_kind;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = xstrdup(operators[i]);
			*rest = line + ft_strlen(op);
			op_token_kind = set_operator_token(op);
			return (new_token(op, op_token_kind));
		}
		i++;
	}
	assert_error("Unexpected operator");
}

/* ************************************************************************** */
static int	set_operator_token(char *op)
{
	if (ft_strncmp(op, "|", 2) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(op, ">", 2) == 0)
		return (TOKEN_REDIR_OUT);
	else if (ft_strncmp(op, "<", 2) == 0)
		return (TOKEN_REDIR_IN);
	else if (ft_strncmp(op, ">>", 3) == 0)
		return (TOKEN_REDIR_APPEND);
	else if (ft_strncmp(op, "<<", 3) == 0)
		return (TOKEN_REDIR_HEREDOC);
	else if (ft_strncmp(op, "\n", 2) == 0)
		return (TOKEN_NEWLINE);
	return (TOKEN_UNKNOWN);
}
