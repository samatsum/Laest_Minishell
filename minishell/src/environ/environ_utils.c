/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/28 19:03:21 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		is_identifier(const char *s);
bool		item_exported(t_item *item);
t_item		*map_get(t_map *map, const char *name);
int			map_unset(t_map *map, const char *name);
static void	free_cur(t_item *cur);
/*
DEFINITIONS
	   The following definitions are used throughout the rest of this document.
	   blank  A space or tab.
	   word   A sequence of characters considered as a single unit by the
			  shell.  Also known as a token.
	   name   A word consisting only of alphanumeric characters and
			  underscores, and beginning with an alphabetic character or an
			  underscore.  Also referred to as an identifier.
	   metacharacter
			  A character that, when unquoted, separates words.  One of the
			  following:
			  |  & ; ( ) < > space tab
	   control operator
			  A token that performs a control function.  It is one of the
			  following symbols:
			  || & && ; ;; ( ) | <newline>
*/

/* ************************************************************************** */
bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}

/* ************************************************************************** */
bool	item_exported(t_item *item)
{
	return (item->attributes & ATTR_EXPORT);
}

/* ************************************************************************** */
t_item	*map_get(t_map *map, const char *name)
{
	t_item	*cur;

	if (name == NULL)
		return (NULL);
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

/* ************************************************************************** */
int	map_unset(t_map *map, const char *name)
{
	t_item	*cur;
	t_item	*prev;

	if (name == NULL)
		return (-1);
	if (!is_identifier(name))
		return (0);
	prev = &map->item_head;
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			prev->next = cur->next;
			free_cur(cur);
			return (0);
		}
		prev = prev->next;
		cur = cur->next;
	}
	return (0);
}

static void	free_cur(t_item *cur)
{
	free(cur->name);
	cur->name = NULL;
	free(cur->value);
	cur->value = NULL;
	free(cur);
	cur = NULL;
}
