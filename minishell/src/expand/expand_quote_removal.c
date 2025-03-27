/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:45:39 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 20:56:59 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "xlib.h"
#include "minishell.h"

void		expand_quote_removal(t_node *node);
static void	remove_quote(t_token *tok);
static void	remove_single_quote(char **dst, char **rest, char *p);
static void	remove_double_quote(char **dst, char **rest, char *p);

/* ************************************************************************** */
void	expand_quote_removal(t_node *node)
{
	if (node == NULL)
		return ;
	remove_quote(node->args_token);
	remove_quote(node->filename_token);
	remove_quote(node->delimiter_token);
	expand_quote_removal(node->redirects_node);
	expand_quote_removal(node->cmd_node);
	expand_quote_removal(node->next);
}

/* ************************************************************************** */
static void	remove_quote(t_token *tok)
{
	char	*new_word;
	char	*p;

	if (tok == NULL || tok->kind != TOKEN_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = xcalloc(1, sizeof(char));
	while (*p)
	{
		if (*p == SINGLE_QUOTE_CHAR)
			remove_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			remove_double_quote(&new_word, &p, p);
		else
			append_char(&new_word, *p++);
	}
	free(tok->word);
	tok->word = NULL;
	tok->word = new_word;
	remove_quote(tok->next);
}

/* ************************************************************************** */
static void	remove_single_quote(char **dst, char **rest, char *p)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		p++;
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed single quote");
			append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected single quote");
}

/* ************************************************************************** */
static void	remove_double_quote(char **dst, char **rest, char *p)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		p++;
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed double quote");
			append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected double quote");
}
