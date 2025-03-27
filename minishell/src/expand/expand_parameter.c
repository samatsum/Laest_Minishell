/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:35:11 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 00:05:22 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "xlib.h"
#include "minishell.h"

void		expand_parameter(t_node *node, t_context *ctx);
static void	expand_parameter_tok(t_token *tok, t_context *ctx);
/*
PARAMETERS
	   A parameter is an entity that stores values.  It can be a name, a
	   number, or one of the special characters listed below under Special
	   Parameters.  A variable is a parameter denoted by a name.  A variable
	   has a value and zero or more attributes.  Attributes are assigned using
	   the declare builtin cmd_node (see declare below in SHELL BUILTIN
	   COMMANDS).

	   A parameter is set if it has been assigned a value.  The null string is
	   a valid value.  Once a variable is set, it may be unset only by using
	   the unset builtin cmd_node (see SHELL BUILTIN COMMANDS below).

	   A variable may be assigned to by a statement of the form

			  name=[value]

	   If value is not given, the variable is assigned the null string.  All
	   values undergo tilde expansion, parameter and variable expansion,
	   cmd_node substitution, arithmetic expansion, and quote removal (see
	   EXPANSION below).  If the variable has its integer attribute set, then
	   value is evaluated as an arithmetic expression even if the $((...))
	   expansion is not used (see Arithmetic Expansion below).  Word splitting
	   is not performed, with the exception of "$@" as explained below under
	   Special Parameters.  Pathname expansion is not performed.  Assignment
	   statements may also appear as arguments to the alias, declare, typeset,
	   export, readonly, and local builtin commands.

	   In the context where an assignment statement is assigning a value to a
	   shell variable or array index, the += operator can be used to append to
	   or add to the variable's previous value.  When += is applied to a
	   variable for which the integer attribute has been set, value is
	   evaluated as an arithmetic expression and added to the variable's
	   current value, which is also evaluated.  When += is applied to an array
	   variable using compound assignment (see Arrays below), the variable's
	   value is not unset (as it is when using =), and new values are appended
	   to the array beginning at one greater than the array's maximum index.
	   When applied to a string-valued variable, value is expanded and appended
	   to the variable's value.
*/

/* ************************************************************************** */
void	expand_parameter(t_node *node, t_context *ctx)
{
	if (node == NULL)
		return ;
	expand_parameter_tok(node->args_token, ctx);
	expand_parameter_tok(node->filename_token, ctx);
	expand_parameter(node->redirects_node, ctx);
	expand_parameter(node->cmd_node, ctx);
	expand_parameter(node->next, ctx);
}

/* ************************************************************************** */
static void	expand_parameter_tok(t_token *tok, t_context *ctx)
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
			append_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			append_double_quote(&new_word, &p, p, ctx);
		else if (is_variable(p))
			(expand_variable_str(&new_word, &p, p, ctx), \
			tok->non_double_quote_valuable = true);
		else if (is_special_parameter(p))
			expand_special_parameter_str(&new_word, &p, p, ctx);
		else
			append_char(&new_word, *p++);
	}
	free(tok->word);
	tok->word = NULL;
	tok->word = new_word;
	expand_parameter_tok(tok->next, ctx);
}
