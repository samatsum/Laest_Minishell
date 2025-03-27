/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:23:51 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 15:35:36 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, t_context *ctx);

/* ************************************************************************** */
int	builtin_unset(char **argv, t_context *ctx)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_unset(ctx->envmap, argv[i]) < 0)
		{
			xperror_invalid_identifier("unset", argv[i]);
			status = 1;
		}
		else
			status = 0;
		i++;
	}
	return (status);
}
