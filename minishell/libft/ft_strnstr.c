/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
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
The strnstr() function locates the first occurrence of the null-terminated
string needle in the string haystack, where not more than len characters are
searched.  Characters that appear after a `\0' character are not searched.
Since the strnstr() function is a FreeBSD specific API, it should only be
used when portability is not a concern.

RETURN VALUES
If needle is an empty string, haystack is returned; if needle occurs nowhere
in haystack, NULL is returned; otherwise a pointer to the first character of
the first occurrence of needle is returned.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (1)
	{
		if (len < 1)
			return (NULL);
		if (*haystack == '\0')
			return (NULL);
		if (needle_len > len)
			return (NULL);
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			break ;
		len--;
		haystack++;
	}
	return ((char *)haystack);
}
