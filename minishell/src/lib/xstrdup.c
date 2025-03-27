/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:21:54 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 11:54:54 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*xstrdup(const char *s1)
{
	char	*tmp;

	if (!s1)
		return (NULL);
	tmp = ft_strdup(s1);
	if (tmp == NULL)
		fatal_error("xstrdup");
	return (tmp);
}
