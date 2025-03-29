/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:52:53 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/29 13:11:11 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include "minishell.h"

void		wait_pipeline(pid_t last_pid, int *status);
static void	handle_signal_termination(int wstatus, int *status);

/* ************************************************************************** */
void	wait_pipeline(pid_t last_pid, int *status)
{
	pid_t	wait_result;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
			handle_signal_termination(wstatus, status);
		if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
}

/* ************************************************************************** */
static void	handle_signal_termination(int wstatus, int *status)
{
	int	signal;

	if (WIFSIGNALED(wstatus))
	{
		signal = WTERMSIG(wstatus);
		if (signal == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		if (signal == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 20);
		*status = 0x80 + signal;
	}
	else if (WIFEXITED(wstatus))
		*status = WEXITSTATUS(wstatus);
	else
		*status = 42;
}
