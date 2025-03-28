/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:19:12 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 20:58:33 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

void		setup_signal(void);
void		reset_signal(void);
static void	sigint_handler(int signum);

/* ************************************************************************** */
void	setup_signal(void)
{
	extern int	_rl_echo_control_chars;
	struct sigaction	sa;

	_rl_echo_control_chars = 1;
	rl_outstream = stdout;
	
	/* Set up SIGINT handler directly for prompt */
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_error("sigaction");
		
	ignore_sig(SIGQUIT);
}

/* ************************************************************************** */
void	reset_signal(void)
{
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
	reset_sig(SIGPIPE);
}

/* ************************************************************************** */
static void sigint_handler(int signum)
{
	/* シグナル受信を記録 */
	g_signal_received = signum;
	
	/* readlineのポイント位置を取得 - カーソルの位置を示す */
	int point = rl_point;
	int end = rl_end;
	
	/* 入力がある場合のみ改行を出力（ポイント位置が0でない場合） */
	/* または編集中の行の長さが0でない場合 */
	if (point > 0 || end > 0) {
		write(STDOUT_FILENO, "\n", 1);
	}
	
	/* readlineを終了させる */
	rl_replace_line("", 0);
	rl_done = 1;
}

/* ************************************************************************** */

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   signal.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/12 12:19:12 by samatsum          #+#    #+#             */
// /*   Updated: 2025/03/28 20:45:22 by samatsum         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>
// #include <readline/readline.h>
// #include "minishell.h"

// void		setup_signal(void);
// void		reset_signal(void);
// static int	check_state(void);

// /* ************************************************************************** */
// void	setup_signal(void)
// {
// 	extern int	_rl_echo_control_chars;

// 	_rl_echo_control_chars = 1;
// 	rl_outstream = stdout;
// 	if (isatty(STDIN_FILENO))
// 		rl_event_hook = check_state;
// 	ignore_sig(SIGQUIT);
// 	handle_sig(SIGINT);
// }

// /* ************************************************************************** */
// void	reset_signal(void)
// {
// 	reset_sig(SIGQUIT);
// 	reset_sig(SIGINT);
// 	reset_sig(SIGPIPE);
// }

// /* ************************************************************************** */
// static int	check_state(void)
// {
// 	if (g_signal_received == 0)
// 		return (0);
// 	else if (g_signal_received == SIGINT)
// 	{
// 		g_signal_received = 0;
// 		rl_replace_line("", 0);
// 		rl_done = 1;
// 		return (0);
// 	}
// 	return (0);
// }
