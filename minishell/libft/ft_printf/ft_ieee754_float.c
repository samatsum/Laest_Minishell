/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ieee754_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ieee754.h"

bool	is_negative(t_ieee754_float f)
{
	return (f.ieee.negative == 1);
}

bool	is_inf(t_ieee754_float f)
{
	return (f.ieee.exponent == 0xff && f.ieee.mantissa == 0);
}

bool	is_nan(t_ieee754_float f)
{
	return (f.ieee.exponent == 0xff && f.ieee.mantissa > 0);
}

bool	is_denormalized(t_ieee754_float f)
{
	return (f.ieee.exponent == 0);
}
