/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:19:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 22:51:05 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		reset_sig(int signum);
void		ignore_sig(int signum);
void		handle_sig(int signum);
static void	handler(int signum);

/* ************************************************************************** */
void	reset_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_DFL;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

/* ************************************************************************** */
void	ignore_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

/* ************************************************************************** */
void	handle_sig(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(signum, &sa, NULL) < 0)
		fatal_error("sigaction");
}

/* ************************************************************************** */
static void	handler(int signum)
{
	g_signal_received = signum;
}
