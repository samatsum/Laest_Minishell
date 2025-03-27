/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_map_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:32:54 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 20:59:20 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "xlib.h"
#include "minishell.h"

/* ************************************************************************** */
int			map_put(t_map *map, const char *string, bool allow_empty, int attr);
static void	set_name_value(const char *string, char **name, char **value);

/* ************************************************************************** */
int	map_put(t_map *map, const char *string, bool allow_empty, int attr)
{
	int		result;
	char	*name;
	char	*value;

	set_name_value(string, &name, &value);
	if (value == NULL && !allow_empty)
	{
		free(name);
		name = NULL;
		return (-1);
	}
	result = map_set_attr(map, name, value, attr);
	free(name);
	name = NULL;
	free(value);
	value = NULL;
	return (result);
}

/* ************************************************************************** */
static void	set_name_value(const char *string, char **name, char **value)
{
	char	*name_end;

	name_end = ft_strchr(string, '=');
	if (name_end == NULL)
	{
		*name = xstrdup(string);
		*value = NULL;
	}
	else
	{
		*name = xstrndup(string, name_end - string);
		*value = xstrdup(name_end + 1);
	}
}
