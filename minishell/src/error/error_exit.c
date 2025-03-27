/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torinoue <torinoue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 22:33:17 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/26 01:27:44 by torinoue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "minishell.h"
#include <stdio.h>

void	fatal_error(const char *msg)__attribute__((noreturn));
void	assert_error(const char *msg)__attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status)\
		__attribute__((noreturn));
void	todo(const char *msg)__attribute__((noreturn));

/* ************************************************************************** */
void	fatal_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	perror(NULL);
	exit(1);
}

/* ************************************************************************** */
void	assert_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

/* ************************************************************************** */
void	err_exit(const char *location, const char *msg, int status)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: %s\n", location, msg);
	exit(status);
}

/* ************************************************************************** */
void	todo(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}
