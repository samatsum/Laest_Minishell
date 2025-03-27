/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open_redir_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:11:42 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 14:13:02 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

int	open_redir_file(t_node *node, t_context *ctx);
int	openfd(t_node *node, t_context *ctx);

/* ************************************************************************** */
int	open_redir_file(t_node *node, t_context *ctx)
{
	if (node == NULL)
		return (0);
	if (node->kind == NODE_PIPELINE)
	{
		if (open_redir_file(node->cmd_node, ctx) < 0)
			return (-1);
		if (open_redir_file(node->next, ctx) < 0)
			return (-1);
		return (0);
	}
	else if (node->kind == NODE_SIMPLE_CMD)
		return (open_redir_file(node->redirects_node, ctx));
	node->filefd = openfd(node, ctx);
	if (node->filefd < 0)
	{
		if (node->kind == NODE_REDIR_OUT || node->kind == NODE_REDIR_APPEND \
			|| node->kind == NODE_REDIR_IN)
			xperror2(node->filename_token->word, NULL);
		return (-1);
	}
	node->filefd = stashfd(node->filefd);
	return (open_redir_file(node->next, ctx));
}

/* ************************************************************************** */
int	openfd(t_node *node, t_context *ctx)
{
	if (node->kind == NODE_REDIR_OUT)
		return (open(node->filename_token->word, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (node->kind == NODE_REDIR_IN)
		return (open(node->filename_token->word, O_RDONLY));
	else if (node->kind == NODE_REDIR_APPEND)
		return (open(node->filename_token->word,
				O_CREAT | O_WRONLY | O_APPEND, 0644));
	else if (node->kind == NODE_REDIR_HEREDOC)
		return (read_heredoc(node->delimiter_token->word, \
			node->is_delim_unquoted, ctx));
	else
		assert_error("open_redir_file");
}
