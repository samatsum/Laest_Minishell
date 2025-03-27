/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:43:23 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 20:53:24 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "xlib.h"
#include "minishell.h"

void		expand_word_splitting(t_node *node, t_context *ctx);
static void	expand_word_splitting_tok(t_token *tok, t_context *ctx);
static void	word_split(t_token *tok, t_context *ctx);
static void	insert_new_tok(char **new_word, t_token **rest, t_token *tok);
/*
   Word Splitting
	   The shell scans the results of parameter expansion, cmd_node
	   substitution, and arithmetic expansion that did not occur within double
	   quotes for word splitting.

	   The shell treats each character of IFS as a delimiter_token, and splits the
	   results of the other expansions into words on these characters.  If IFS
	   is unset, or its value is exactly <space><tab><newline>, the default,
	   then any sequence of IFS characters serves to delimit words.  If IFS has
	   a value other than the default, then sequences of the whitespace
	   characters space and tab are ignored at the beginning and end of the
	   word, as long as the whitespace character is in the value of IFS (an IFS
	   whitespace character).  Any character in IFS that is not IFS whitespace,
	   along with any adjacent IFS whitespace characters, delimits a field.  A
	   sequence of IFS whitespace characters is also treated as a delimiter_token.
	   If the value of IFS is null, no word splitting occurs.

	   Explicit null arguments ("" or '') are retained.  Unquoted implicit null
	   arguments, resulting from the expansion of parameters that have no
	   values, are removed.  If a parameter with no value is expanded within
	   double quotes, a null argument results and is retained.

	   Note that if no expansion occurs, no splitting is performed.
*/

/* ************************************************************************** */
void	expand_word_splitting(t_node *node, t_context *ctx)
{
	if (node == NULL)
		return ;
	expand_word_splitting_tok(node->args_token, ctx);
	expand_word_splitting_tok(node->filename_token, ctx);
	expand_word_splitting(node->redirects_node, ctx);
	expand_word_splitting(node->cmd_node, ctx);
	expand_word_splitting(node->next, ctx);
}

/* ************************************************************************** */
static void	expand_word_splitting_tok(t_token *tok, t_context *ctx)
{
	if (tok == NULL || tok->kind != TOKEN_WORD || tok->word == NULL)
		return ;
	if (tok->export_flag == 1 && tok->next && tok->next->word)
		if (is_alpha_under(tok->next->word[0]))
			tok->next->export_flag = 2;
	if (!tok->non_double_quote_valuable)
		return (expand_word_splitting_tok(tok->next, ctx));
	word_split(tok, ctx);
	expand_word_splitting_tok(tok->next, ctx);
}

static void	word_split(t_token *tok, t_context *ctx)
{
	char	*new_word;
	char	*p;

	if (tok->export_flag != 2)
		trim_ifs(&p, tok->word, ctx);
	else
		p = tok->word;
	new_word = xcalloc(1, sizeof(char));
	while (*p)
	{
		if (*p == SINGLE_QUOTE_CHAR)
			append_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			append_double_quote(&new_word, &p, p, ctx);
		else if (tok->export_flag != 2 && consume_ifs(&p, p, ctx) && *p)
			insert_new_tok(&new_word, &tok, tok);
		else
			append_char(&new_word, *p++);
	}
	free(tok->word);
	tok->word = NULL;
	tok->word = new_word;
}

/* ************************************************************************** */
static void	insert_new_tok(char **new_word, t_token **rest, t_token *tok)
{
	t_token	*new_tok;

	free(tok->word);
	tok->word = NULL;
	tok->word = *new_word;
	*new_word = xcalloc(1, sizeof(char));
	new_tok = new_token(NULL, TOKEN_WORD);
	new_tok->next = tok->next;
	tok->next = new_tok;
	*rest = tok->next;
}
