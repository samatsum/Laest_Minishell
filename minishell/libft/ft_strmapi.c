/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// s: not protected (difference between "" and NULL is important)
// f: not protected (strmapi should not know about f)
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	new = ft_strdup(s);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (*(new + i))
	{
		*(new + i) = f(i, *(new + i));
		i++;
	}
	return (new);
}
