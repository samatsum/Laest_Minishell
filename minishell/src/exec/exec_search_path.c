/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_search_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:15:29 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 15:38:37 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "xlib.h"
#include "minishell.h"

char		*search_path(const char *filename_token, t_context *ctx);
static void	set_path(char *path, size_t pathsize, const char *filename_token, \
	char **envpath);
static char	*search_path_mode(const char *filename_token, int mode, \
	t_context *ctx);

/* ************************************************************************** */
char	*search_path(const char *filename_token, t_context *ctx)
{
	char	*path;

	path = search_path_mode(filename_token, X_OK, ctx);
	if (path)
		return (path);
	path = search_path_mode(filename_token, F_OK, ctx);
	return (path);
}

/* ************************************************************************** */
static void	set_path(char *path, size_t pathsize, const char *filename_token, \
	char **envpath)
{
	size_t	len;
	char	buf[PATH_MAX];
	char	*end;

	ft_bzero(path, pathsize);
	end = ft_strchr(*envpath, ':');
	if (*envpath == end)
		len = ft_strlcpy(path, ".", pathsize);
	else if (end)
	{
		len = ft_strlcpy(buf, *envpath, end - *envpath + 1);
		ft_strlcpy(path, buf, pathsize);
	}
	else
		len = ft_strlcpy(path, *envpath, pathsize);
	len += ft_strlcat(path, "/", pathsize);
	len += ft_strlcat(path, filename_token, pathsize);
	if (len > pathsize - 1)
		path[0] = '\0';
	if (end == NULL)
		*envpath = NULL;
	else
		*envpath = end + 1;
}

/* ************************************************************************** */
static char	*search_path_mode(const char *filename_token, int mode, \
	t_context *ctx)
{
	char	path[PATH_MAX];
	char	*envpath;
	char	*dup;

	envpath = xgetenv("PATH", ctx);
	while (envpath && *envpath)
	{
		set_path(path, PATH_MAX, filename_token, &envpath);
		if (access(path, mode) == 0)
		{
			dup = xstrdup(path);
			return (dup);
		}
	}
	return (NULL);
}
