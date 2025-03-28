/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prepare_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:25:45 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 15:32:00 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "xlib.h"
#include "minishell.h"

void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

/* ************************************************************************** */
void	prepare_pipe(t_node *node)
{
	if (node->next == NULL)
		return ;
	xpipe(node->inter_process_pipe);
	node->next->input_fd = node->inter_process_pipe[0];
}

/* ************************************************************************** */
void	prepare_pipe_child(t_node *node)
{
	if (node->input_fd != STDIN_FILENO)
	{
		xdup2(node->input_fd, STDIN_FILENO);
		xclose(node->input_fd);
	}
	if (node->next)
	{
		xclose(node->inter_process_pipe[0]);
		xdup2(node->inter_process_pipe[1], STDOUT_FILENO);
		if (node->inter_process_pipe[1] != STDOUT_FILENO)
			xclose(node->inter_process_pipe[1]);
	}
}

/* ************************************************************************** */
void	prepare_pipe_parent(t_node *node)
{
	if (node->input_fd != STDIN_FILENO)
		xclose(node->input_fd);
	if (node->next)
		xclose(node->inter_process_pipe[1]);
}
