/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

/*
DESCRIPTION
The atoi() function converts the initial portion of the string pointed to by str
to int representation.

It is equivalent to:

(int)strtol(str, (char **)NULL, 10);

While the atoi() function uses the current locale, the atoi_l() function may be
passed a locale directly. See xlocale(3) for more information.

IMPLEMENTATION NOTES
The atoi() and atoi_l() functions are thread-safe and async-cancel-safe.

The strtol() and strtol_l() functions are recommended instead of atoi() and
atoi_l() functions, especially in new code.

ERRORS
The function atoi() need not affect the value of errno on an error.
*/
int	ft_atoi(const char *str)
{
	return ((int)ft_strtol(str, NULL, 10));
}
