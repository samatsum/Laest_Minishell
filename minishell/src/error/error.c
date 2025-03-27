/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:35:17 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 15:32:23 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"
#include "minishell.h"

#define ERROR_PREFIX "minishell: "

void	perror_prefix(void);
void	xperror2(const char *s1, const char *err_msg);
void	xperror3(const char *s1, const char *s2, const char *err_msg);
void	xperror_invalid_identifier(const char *s, const char *identifier);

/* ************************************************************************** */
void	perror_prefix(void)
{
	ft_dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

/* ************************************************************************** */
void	xperror2(const char *s1, const char *err_msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s1);
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		perror(NULL);
}

/* ************************************************************************** */
void	xperror3(const char *s1, const char *s2, const char *err_msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s1);
	ft_dprintf(STDERR_FILENO, "%s: ", s2);
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		perror(NULL);
}

/* ************************************************************************** */
void	xperror_invalid_identifier(const char *s, const char *identifier)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s);
	ft_dprintf(STDERR_FILENO, "`%s': ", identifier);
	ft_dprintf(STDERR_FILENO, "not a valid identifier\n");
}
