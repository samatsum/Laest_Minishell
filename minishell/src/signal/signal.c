/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:19:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 10:18:27 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

void		setup_signal(void);
void		reset_signal(void);
static int	check_state(void);

/* ************************************************************************** */
void	setup_signal(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 1;
	rl_outstream = stdout;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	ignore_sig(SIGQUIT);
	handle_sig(SIGINT);
}

/* ************************************************************************** */
void	reset_signal(void)
{
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
	reset_sig(SIGPIPE);
}

/* ************************************************************************** */
static int	check_state(void)
{
	if (g_signal_received == 0)
		return (0);
	else if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		rl_replace_line("", 0);
		rl_done = 1;
		return (0);
	}
	return (0);
}
