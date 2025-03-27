/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:22:34 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 21:03:49 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_node(t_node *node);
void	free_tok(t_token *tok);
void	free_argv(char **argv);

/* ************************************************************************** */
void	free_node(t_node *node)
{
	if (node == NULL)
		return ;
	free_tok(node->args_token);
	free_tok(node->filename_token);
	free_tok(node->delimiter_token);
	free_node(node->redirects_node);
	free_node(node->next);
	free_node(node->cmd_node);
	free(node);
	node = NULL;
}

/* ************************************************************************** */
void	free_tok(t_token *tok)
{
	if (tok == NULL)
		return ;
	if (tok->word)
	{
		free(tok->word);
		tok->word = NULL;
	}
	free_tok(tok->next);
	free(tok);
	tok = NULL;
}

/* ************************************************************************** */
void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		argv[i] = NULL;
		i++;
	}
	free(argv);
	argv = NULL;
}
