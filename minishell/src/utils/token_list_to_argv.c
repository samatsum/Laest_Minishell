/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_to_argv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:41:32 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 01:04:20 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include "minishell.h"

char			**token_list_to_argv(t_token *tok);
static size_t	argv_len(t_token *tok);

/* ************************************************************************** */
char	**token_list_to_argv(t_token *tok)
{
	char	**argv;
	size_t	i;

	argv = xcalloc(argv_len(tok) + 1, sizeof(char *));
	i = 0;
	while (tok && !at_eof(tok))
	{
		argv[i] = xstrdup(tok->word);
		i++;
		tok = tok->next;
	}
	return (argv);
}

/* ************************************************************************** */
static size_t	argv_len(t_token *tok)
{
	size_t	len;

	len = 0;
	while (tok && !at_eof(tok))
	{
		len++;
		tok = tok->next;
	}
	return (len);
}
