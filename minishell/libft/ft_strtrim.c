/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*find_head(char const *s, char const *set)
{
	char const	*head;

	head = s;
	while (ft_strchr(set, *head))
		head++;
	return (head);
}

static const char	*find_tail(char const *s, char const *set)
{
	char const	*tail;

	tail = NULL;
	while (*s)
	{
		if (ft_strchr(set, *s) == NULL)
			tail = s;
		s++;
	}
	return (tail);
}

// s1: not protected
// set: not protected
char	*ft_strtrim(char const *s1, char const *set)
{
	const char		*head;
	const char		*tail;
	unsigned int	start;
	size_t			len;

	head = find_head(s1, set);
	tail = find_tail(s1, set);
	if (tail < head)
		return (ft_strdup(""));
	start = (unsigned int)(head - s1);
	len = (size_t)(tail - head + 1);
	return (ft_substr(s1, start, len));
}
