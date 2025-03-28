/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
DESCRIPTION
The memcmp() function compares byte string s1 against byte string s2.  Both
strings are assumed to be n bytes long.

RETURN VALUES
The memcmp() function returns zero if the two strings are identical, other-
wise returns the difference between the first two differing bytes (treated
as unsigned char values, so that `\200' is greater than `\0', for example).
Zero-length strings are always identical.  This behavior is not required by
C and portable code should only depend on the sign of the returned value.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				cnt;
	const unsigned char	*str1;
	const unsigned char	*str2;

	if (s1 == s2)
		return (0);
	cnt = 0;
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (cnt++ < n)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}
