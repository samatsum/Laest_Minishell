/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	cnt;

	if (dstsize == 0 || ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen(src));
	if (ft_strlen(src) == 0)
		return (ft_strlen(dst));
	cnt = 0;
	while (*dst && cnt < dstsize - 1)
	{
		dst++;
		cnt++;
	}
	while (*src && cnt < dstsize - 1)
	{
		*dst = *src;
		dst++;
		src++;
		cnt++;
	}
	*dst = '\0';
	while (*src++)
		cnt++;
	return (cnt);
}
