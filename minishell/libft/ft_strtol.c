/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>
#include "libft.h"

static BOOL	is_cut(unsigned long current, unsigned long next,
	unsigned long base, BOOL isneg)
{
	unsigned long	cutoff;
	unsigned long	cutlim;

	cutoff = (LONG_MAX + isneg) / base;
	cutlim = (LONG_MAX + isneg) % base;
	if (current > cutoff || (current == cutoff && next > cutlim))
		return (TRUE);
	else
		return (FALSE);
}

static void	preprocess_strtol(const char **str, int *base, BOOL *isneg)
{
	while (ft_isspace(**str))
		(*str)++;
	*isneg = FALSE;
	if (**str == '-')
		*isneg = TRUE;
	if (**str == '-' || **str == '+')
		(*str)++;
	if ((base == 0 || *base == 16)
		&& (ft_strncmp(*str, "0x", 2) == 0 || ft_strncmp(*str, "0X", 2) == 0))
	{
		*str += 2;
		*base = 16;
	}
	if (*base == 0 && **str == '0')
		*base = 8;
	else if (base == 0)
		*base = 10;
}

// RETURNS TRUE if OVERFLOW
static BOOL	internal_strtol(const char **str, int base,
	unsigned long *ul_val, BOOL *isneg)
{
	BOOL	overflow;

	overflow = FALSE;
	preprocess_strtol(str, &base, isneg);
	*ul_val = 0;
	while (ft_isdigit(**str))
	{
		if (is_cut(*ul_val, (unsigned long)**str - '0', base, *isneg))
			overflow = TRUE;
		if (!overflow)
			*ul_val = (*ul_val) * (unsigned long)base
				+ (unsigned long)(**str - '0');
		(*str)++;
	}
	return (overflow);
}

// Original strtol takes endptr and base
// 	long strtol(const char *restrict str, char **restrict endptr, int base);
// This time, only implemented the pattern of (endptr: NULL, base: 10).
long	ft_strtol(const char *str, char **endptr, int base)
{
	unsigned long	ul_val;
	BOOL			isneg;
	BOOL			err;

	err = internal_strtol(&str, base, &ul_val, &isneg);
	if (endptr)
		*endptr = (char *)str;
	if (err)
	{
		if (isneg == TRUE)
			ul_val = (unsigned long)LONG_MIN;
		else
			ul_val = (unsigned long)LONG_MAX;
		errno = ERANGE;
	}
	else if (isneg == TRUE)
		ul_val = -ul_val;
	return ((long)ul_val);
}
