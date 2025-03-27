/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
	1. Why cursize?
	You need to be able to determine the original size of the memory block 
	pointed to by ptr, and there is no portable way to do so.
	
	2. Doesn't shrink?
	It's not required behaviour.
	
	cf.
	https://codereview.stackexchange.com/questions/151019/
*/
void	*ft_realloc(void *ptr, size_t newsize, size_t cursize)
{
	void	*newptr;

	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
		return (malloc(newsize));
	else if (newsize <= cursize)
		return (ptr);
	else
	{
		newptr = malloc(newsize);
		if (newptr)
		{
			ft_memmove(newptr, ptr, cursize);
			free(ptr);
		}
		return (newptr);
	}
}
