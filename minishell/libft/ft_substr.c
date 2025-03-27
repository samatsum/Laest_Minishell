/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// Returns empty string if start is larger than length of s.
// like Python. (And it was difficult to cause crash like index out of range)
// s: not protected
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	new_len;
	char	*new;

	new_len = 1;
	if (start < ft_strlen(s))
		new_len = ft_strlen(s) - start + 1;
	if (new_len > len)
		new_len = len + 1;
	new = malloc(new_len);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, s + start, new_len - 1);
	new[new_len - 1] = '\0';
	return (new);
}
