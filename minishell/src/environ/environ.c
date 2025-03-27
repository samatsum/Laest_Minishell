/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:11:27 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 13:25:14 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "xlib.h"
#include "minishell.h"

/* ************************************************************************** */
void			initenv(t_context *ctx);
static t_map	*map_new(void);
static void		envmap_init(t_map *map, char **ep);

/* ************************************************************************** */
void	initenv(t_context *ctx)
{
	extern char	**environ;

	ctx->envmap = map_new();
	envmap_init(ctx->envmap, environ);
}

/* ************************************************************************** */
static t_map	*map_new(void)
{
	t_map	*map;

	map = xcalloc(1, sizeof(*map));
	return (map);
}

/* ************************************************************************** */
static void	envmap_init(t_map *map, char **ep)
{
	char	cwd[PATH_MAX];

	while (*ep)
	{
		map_put(map, *ep, false, ATTR_EXPORT);
		ep++;
	}
	if (map_get(map, "SHLVL") == NULL)
		map_set_attr(map, "SHLVL", "1", ATTR_EXPORT);
	if (map_get(map, "PWD") == NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			xperror3("shell-init", "getcwd", NULL);
		else
			map_set_attr(map, "PWD", cwd, ATTR_EXPORT);
	}
	if (map_get(map, "OLDPWD") == NULL)
		map_set_attr(map, "OLDPWD", NULL, ATTR_EXPORT);
	if (map_get(map, "IFS") == NULL)
		map_set_attr(map, "IFS", " \t\n", 0);
}
