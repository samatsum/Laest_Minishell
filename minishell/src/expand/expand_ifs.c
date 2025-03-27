/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ifs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:35:24 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 14:06:44 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		trim_ifs(char **rest, char *p, t_context *ctx);
static bool	consume_default_ifs(char **rest, char *p);
static bool	is_ifs(char c, t_context *ctx);
static bool	is_default_ifs(char c);
bool		consume_ifs(char **rest, char *line, t_context *ctx);

/* ************************************************************************** */
void	trim_ifs(char **rest, char *word, t_context *ctx)
{
	char	*last;

	consume_default_ifs(&word, word);
	*rest = word;
	last = NULL;
	while (*word)
	{
		last = word;
		if (consume_default_ifs(&word, word))
			;
		else
			word++;
	}
	if (last && is_ifs(*last, ctx) && is_default_ifs(*last))
		*last = '\0';
}

/* ************************************************************************** */
static bool	consume_default_ifs(char **rest, char *p)
{
	bool	consumed;

	consumed = false;
	while (*p && is_default_ifs(*p))
	{
		consumed = true;
		p++;
	}
	*rest = p;
	return (consumed);
}

/* ************************************************************************** */
static bool	is_ifs(char c, t_context *ctx)
{
	char	*ifs;

	ifs = xgetenv("IFS", ctx);
	if (ifs == NULL)
		return (is_default_ifs(c));
	if (c == '\0')
		return (false);
	return (ft_strchr(ifs, c) != NULL);
}

/* ************************************************************************** */
static bool	is_default_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/* ************************************************************************** */
bool	consume_ifs(char **rest, char *line, t_context *ctx)
{
	if (is_ifs(*line, ctx))
	{
		consume_default_ifs(&line, line);
		if (is_ifs(*line, ctx))
			line++;
		consume_default_ifs(rest, line);
		return (true);
	}
	*rest = line;
	return (false);
}
