/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 00:47:16 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include "minishell.h"

t_node	*new_node(t_node_kind new_kind);
t_token	*tokdup(t_token *tok);
void	append_tok(t_token **tok, t_token *elm);
bool	equal_op(t_token *tok, char *op);

/* ************************************************************************** */
t_node	*new_node(t_node_kind new_kind)
{
	t_node	*node;

	node = xcalloc(1, sizeof(*node));
	node->kind = new_kind;
	return (node);
}

/* ************************************************************************** */
t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = xstrdup(tok->word);
	return (new_token(word, tok->kind));
}

/* ************************************************************************** */
void	append_tok(t_token **tok, t_token *elm)
{
	if (*tok == NULL)
	{
		*tok = elm;
		return ;
	}
	append_tok(&(*tok)->next, elm);
}

/* ************************************************************************** */
bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind == TOKEN_WORD || tok->kind == TOKEN_NULL)
		return (false);
	return (ft_strcmp(tok->word, op) == 0);
}
