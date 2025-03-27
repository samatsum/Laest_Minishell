/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:15:43 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 14:21:02 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int			builtin_export(char **argv, t_context *ctx);
static void	print_allenv(t_context *ctx);

/* ************************************************************************** */
int	builtin_export(char **argv, t_context *ctx)
{
	size_t	i;
	int		status;

	if (argv[1] == NULL)
	{
		print_allenv(ctx);
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_put(ctx->envmap, argv[i], true, ATTR_EXPORT) < 0)
		{
			xperror_invalid_identifier("export", argv[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}

/* ************************************************************************** */
static void	print_allenv(t_context *ctx)
{
	t_item	*cur;

	cur = ctx->envmap->item_head.next;
	while (cur)
	{
		if (!item_exported(cur))
			;
		else if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->name, cur->value);
		else
			printf("declare -x %s\n", cur->name);
		cur = cur->next;
	}
}
