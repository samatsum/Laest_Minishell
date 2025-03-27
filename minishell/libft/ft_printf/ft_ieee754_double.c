/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ieee754_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ieee754.h"

bool	is_d_negative(t_ieee754_double d)
{
	return (d.ieee.negative == 1);
}

bool	is_d_inf(t_ieee754_double d)
{
	return (d.ieee.exponent == 0x7ff && d.ieee.mantissa == 0);
}

bool	is_d_nan(t_ieee754_double d)
{
	return (d.ieee.exponent == 0x7ff && d.ieee.mantissa > 0);
}

bool	is_d_denormalized(t_ieee754_double d)
{
	return (d.ieee.exponent == 0);
}
