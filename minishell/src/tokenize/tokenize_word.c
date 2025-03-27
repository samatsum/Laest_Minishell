/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:12:31 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 13:54:21 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include "minishell.h"

t_token		*word(char **rest, char *line, t_context *ctx);
static void	check_single_quote(char **rest, char *line, t_context *ctx);
static void	check_double_quote(char **rest, char *line, t_context *ctx);

/* ************************************************************************** */
t_token	*word(char **rest, char *line, t_context *ctx)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
			check_single_quote(&line, line, ctx);
		else if (*line == DOUBLE_QUOTE_CHAR)
			check_double_quote(&line, line, ctx);
		else
			line++;
	}
	word = xstrndup(start, line - start);
	*rest = line;
	return (new_token(word, TOKEN_WORD));
}

/* ************************************************************************** */
static void	check_single_quote(char **rest, char *line, t_context *ctx)
{
	line++;
	while (*line && *line != SINGLE_QUOTE_CHAR)
		line++;
	if (*line == '\0')
		unclose_error("Unclosed single quote", &line, line, ctx);
	else
		line++;
	*rest = line;
}

/* ************************************************************************** */
static void	check_double_quote(char **rest, char *line, t_context *ctx)
{
	line++;
	while (*line && *line != DOUBLE_QUOTE_CHAR)
		line++;
	if (*line == '\0')
		unclose_error("Unclosed double quote", &line, line, ctx);
	else
		line++;
	*rest = line;
}
