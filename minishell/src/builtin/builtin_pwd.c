/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:45:42 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 14:20:22 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include "minishell.h"

int			builtin_pwd(char **argv, t_context *ctx);
static bool	equal_to_cwd(const char *path);

/* ************************************************************************** */
int	builtin_pwd(char **argv, t_context *ctx)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)argv;
	pwd = xgetenv("PWD", ctx);
	if (pwd == NULL || !equal_to_cwd(pwd))
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			xperror3("pwd", "getcwd", NULL);
			return (1);
		}
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
}

/* ************************************************************************** */
static bool	equal_to_cwd(const char *path)
{
	struct stat	st1;
	struct stat	st2;

	ft_memset(&st1, 0, sizeof(st1));
	ft_memset(&st2, 0, sizeof(st2));
	if (stat(path, &st1) < 0)
		return (false);
	if (stat(".", &st2) < 0)
		fatal_error("stat");
	return (st1.st_ino == st2.st_ino);
}
