/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:21:11 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 11:58:02 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xlib.h"

void	*xcalloc(size_t count, size_t size)
{
	void	*tmp;

	tmp = ft_calloc(count, size);
	if (tmp == NULL)
		fatal_error("xcalloc");
	return (tmp);
}
