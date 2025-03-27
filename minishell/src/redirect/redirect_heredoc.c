/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:21:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 20:54:14 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "ft_printf.h"
#include "xlib.h"
#include "minishell.h"

int			read_heredoc(const char *delimiter_token, bool is_delim_unquoted, \
	t_context *ctx);
static void	readline_heredoc_loop(int pfd[2], const char *delimiter_token, \
	bool is_delim_unquoted, t_context *ctx);
static char	*expand_heredoc_line(char *line, t_context *ctx);
/*
   Here Documents
	   This type of redirection instructs the shell to read input from the
	   current source until a line containing only word (with no trailing
	   blanks) is seen.  All of the lines read up to that point are then used
	   as the standard input for a cmd_node.

	   The format of here-documents is:

              <<[-]word
                      here-document
              delimiter_token

	   No parameter expansion, cmd_node substitution, arithmetic expansion, or
	   pathname expansion is performed on word.  If any characters in word are
	   quoted, the delimiter_token is the result of quote removal on word, and the
	   lines in the here-document are not expanded.  If word is unquoted, all
	   lines of the here-document are subjected to parameter expansion, cmd_node
	   substitution, and arithmetic expansion.  In the latter case, the
	   character sequence \<newline> is ignored, and \ must be used to quote
	   the characters \, $, and `.

	   If the redirection operator is <<-, then all leading tab characters are
	   stripped from input lines and the line containing delimiter_token.  This
	   allows here-documents within shell scripts to be indented in a natural
	   fashion.
*/

/* ************************************************************************** */
int	read_heredoc(const char *delimiter_token, bool is_delim_unquoted, \
	t_context *ctx)
{
	int		pfd[2];

	xpipe(pfd);
	ctx->readline_interrupted = false;
	readline_heredoc_loop(pfd, delimiter_token, is_delim_unquoted, ctx);
	xclose(pfd[1]);
	if (ctx->readline_interrupted)
	{
		xclose(pfd[0]);
		return (-1);
	}
	return (pfd[0]);
}

/* ************************************************************************** */
static void	readline_heredoc_loop(int pfd[2], const char *delimiter_token,
		bool is_delim_unquoted, t_context *ctx)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || g_signal_received == SIGINT
			|| ft_strcmp(line, delimiter_token) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		if (is_delim_unquoted)
			line = expand_heredoc_line(line, ctx);
		ft_dprintf(pfd[1], "%s\n", line);
		free(line);
		line = NULL;
	}
}

/* ************************************************************************** */
static char	*expand_heredoc_line(char *line, t_context *ctx)
{
	char	*new_word;
	char	*p;

	p = line;
	new_word = xcalloc(1, sizeof(char));
	while (*p)
	{
		if (is_variable(p))
			expand_variable_str(&new_word, &p, p, ctx);
		else if (is_special_parameter(p))
			expand_special_parameter_str(&new_word, &p, p, ctx);
		else
			append_char(&new_word, *p++);
	}
	free(line);
	line = NULL;
	return (new_word);
}
