/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xgetenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:34:48 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 13:43:55 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
char	*xgetenv(const char *name, t_context *ctx)
{
	t_item	*item;

	item = map_get(ctx->envmap, name);
	if (item == NULL)
		return (NULL);
	return (item->value);
}
