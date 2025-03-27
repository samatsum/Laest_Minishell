/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:21:21 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 20:54:37 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "xlib.h"
#include "minishell.h"

void	expand_variable_str(char **dst, char **rest, char *p, t_context *ctx);
bool	is_variable(char *s);

/*
PARAMETERS
	A parameter is an entity that stores values.  It can be a variable_name, a
	   number, or one of the special characters listed below under Special
Parameters.  A variable is a parameter denoted by a variable_name.  A variable
	   has a value and zero or more attributes.  Attributes are assigned using
	   the declare builtin cmd_node (see declare below in SHELL BUILTIN
	   COMMANDS).

	   A parameter is set if it has been assigned a value.  The null string is
	   a valid value.  Once a variable is set, it may be unset only by using
	   the unset builtin cmd_node (see SHELL BUILTIN COMMANDS below).

	   A variable may be assigned to by a statement of the form

              variable_name=[value]

	   If value is not given, the variable is assigned the null string.  All
	   values undergo tilde expansion, parameter and variable expansion,
	   cmd_node substitution, arithmetic expansion, and quote removal (see
	   EXPANSION below).  If the variable has its integer attribute set, then
	   value is evaluated as an arithmetic expression even if the $((...))
	   expansion is not used (see Arithmetic Expansion below).  Word splitting
	   is not performed, with the exception of "$@" as explained below under
Special Parameters.  Pathvariable_name expansion is not performed.  Assignment
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
void	expand_variable_str(char **dst, char **rest, char *p, t_context *ctx)
{
	char	*variable_name;
	char	*value;

	variable_name = xcalloc(1, sizeof(char));
	if (*p != '$')
		assert_error("Expected dollar sign");
	p++;
	if (!is_alpha_under(*p))
		assert_error("Variable must starts with alphabets or underscore.");
	append_char(&variable_name, *p++);
	while (is_alpha_num_under(*p))
		append_char(&variable_name, *p++);
	value = xgetenv(variable_name, ctx);
	free(variable_name);
	variable_name = NULL;
	if (value)
		while (*value)
			append_char(dst, *value++);
	else
		*dst = NULL;
	*rest = p;
}

/* ************************************************************************** */
bool	is_variable(char *s)
{
	return (s[0] == '$' && is_alpha_under(s[1]));
}
