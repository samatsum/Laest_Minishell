/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_map_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:43:31 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 20:58:33 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "xlib.h"
#include "minishell.h"

/* ************************************************************************** */
int				map_set_attr(t_map *map, const char *name, const char *value, \
	int attr);
int				map_set(t_map *map, const char *name, const char *value);
static void		item_update(t_item *item, const char *value);
static void		map_insert(t_map *map, const char *name, const char *value);
static t_item	*item_new(char *name, char *value, int attributes);

/* ************************************************************************** */
int	map_set_attr(t_map *map, const char *name, const char *value, int attr)
{
	t_item	*cur;

	if (map_set(map, name, value) < 0)
		return (-1);
	cur = map_get(map, name);
	if (cur == NULL)
		assert_error("map_set_attr");
	cur->attributes = attr;
	return (0);
}

/* ************************************************************************** */
int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*item;

	if (name == NULL || !is_identifier(name))
		return (-1);
	item = map_get(map, name);
	if (item)
		item_update(item, value);
	else
		map_insert(map, name, value);
	return (0);
}

/* ************************************************************************** */
static void	item_update(t_item *item, const char *value)
{
	free(item->value);
	item->value = NULL;
	if (value != NULL)
		item->value = xstrdup(value);
}

/* ************************************************************************** */
static void	map_insert(t_map *map, const char *name, const char *value)
{
	t_item	*item;

	if (value == NULL)
		item = item_new(xstrdup(name), NULL, 0);
	else
		item = item_new(xstrdup(name), xstrdup(value), 0);
	item->next = map->item_head.next;
	map->item_head.next = item;
}

/* ************************************************************************** */
static t_item	*item_new(char *name, char *value, int attributes)
{
	t_item	*item;

	item = xcalloc(1, sizeof(*item));
	item->name = name;
	item->value = value;
	item->attributes = attributes;
	return (item);
}
