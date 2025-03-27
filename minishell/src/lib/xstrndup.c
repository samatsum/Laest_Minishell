/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrndup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:41:34 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 11:54:20 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include "minishell.h"

char	*xstrndup(const char *s1, size_t size)
{
	char	*ret;

	ret = ft_strndup(s1, size);
	if (ret == NULL)
		fatal_error("xstrndup");
	return (ret);
}
