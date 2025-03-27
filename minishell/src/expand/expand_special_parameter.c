/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special_parameter.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:34:26 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 15:34:36 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		expand_special_parameter_str(char **dst, char **rest, char *p, \
	t_context *ctx);
static void	append_num(char **dst, unsigned int num);
bool		is_special_parameter(char *s);

/*
   Special Parameters
	   The shell treats several parameters specially.  These parameters may
	   only be referenced; assignment to them is not allowed.
	   *      Expands to the positional parameters, starting from one.  When
			  the expansion occurs within double quotes, it expands to a single
			  word with the value of each parameter separated by the first
			  character of the IFS special variable.  That is, "$*" is
			  equivalent to "$1c$2c...", where c is the first character of the
			  value of the IFS variable.  If IFS is unset, the parameters are
			  separated by spaces.  If IFS is null, the parameters are joined
			  without intervening separators.
	   @      Expands to the positional parameters, starting from one.  When
			  the expansion occurs within double quotes, each parameter expands
			  to a separate word.  That is, "$@" is equivalent to "$1" "$2" ...
			  If the double-quoted expansion occurs within a word, the
			  expansion of the first parameter is joined with the beginning
			  part of the original word, and the expansion of the last
			  parameter is joined with the last part of the original word.
			  When there are no positional parameters, "$@" and $@ expand to
			  nothing (i.e., they are removed).
       #      Expands to the number of positional parameters in decimal.
	   ?      Expands to the status of the most recently executed foreground
	          pipeline.
	   -      Expands to the current option flags as specified upon invocation,
			  by the set builtin cmd_node, or those set by the shell itself
			  (such as the -i option).
	   $      Expands to the process ID of the shell.  In a () subshell, it
			  expands to the process ID of the current shell, not the subshell.
	   !      Expands to the process ID of the most recently executed
	          background (asynchronous) cmd_node.
	   0      Expands to the name of the shell or shell script.  This is set at
			  shell initialization.  If bash is invoked with a file of
			  commands, $0 is set to the name of that file.  If bash is started
			  with the -c option, then $0 is set to the first argument after
			  the string to be executed, if one is present.  Otherwise, it is
			  set to the file name used to invoke bash, as given by argument
			  zero.
	   _      At shell startup, set to the absolute pathname used to invoke the
			  shell or shell script being executed as passed in the environment
			  or argument list.  Subsequently, expands to the last argument to
			  the previous cmd_node, after expansion.  Also set to the full
			  pathname used to invoke each cmd_node executed and placed in the
			  environment exported to that cmd_node.  When checking mail, this
			  parameter holds the name of the mail file currently being
			  checked.
*/

/* ************************************************************************** */
void	expand_special_parameter_str(char **dst, char **rest, char *p, \
	t_context *ctx)
{
	if (!is_special_parameter(p))
		assert_error("Expected special parameter");
	p += 2;
	append_num(dst, ctx->last_status);
	*rest = p;
}

/* ************************************************************************** */
static void	append_num(char **dst, unsigned int num)
{
	if (num == 0)
	{
		append_char(dst, '0');
		return ;
	}
	if (num / 10 != 0)
		append_num(dst, num / 10);
	append_char(dst, '0' + (num % 10));
}

/* ************************************************************************** */
bool	is_special_parameter(char *s)
{
	return (s[0] == '$' && s[1] == '?');
}
