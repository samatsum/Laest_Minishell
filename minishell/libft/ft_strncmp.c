/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cnt;

	if (s1 == s2 || n == 0)
		return (0);
	cnt = 0;
	while ((*s1 || *s2) && cnt < n)
	{
		if (*s1 != *s2)
			return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
		s1++;
		s2++;
		cnt++;
	}
	return (0);
}
