/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ieee754.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/26 23:35:07 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IEEE754_H
# define FT_IEEE754_H

# include <stdbool.h>

typedef union u_ieee754_float
{
	float	f;

	struct s_ieee754_float {
		unsigned int	mantissa:23;
		unsigned int	exponent:8;
		unsigned int	negative:1;
	}	ieee;
}	t_ieee754_float;

# define IEEE754_FLOAT_BIAS				0x7f 
# define IEEE754_FLOAT_MAX_EXP			0xff 
# define IEEE754_FLOAT_MANTISSA_BITS	23 

typedef union u_ieee754_double
{
	double	d;

	struct s_ieee754_double {
		unsigned long long	mantissa:52;
		unsigned int		exponent:11;
		unsigned int		negative:1;
	}	ieee;
}	t_ieee754_double;

# define IEEE754_DOUBLE_BIAS			0x3ff 
# define IEEE754_DOUBLE_MAX_EXP			0x7ff 
# define IEEE754_DOUBLE_MANTISSA_BITS	52 

bool	is_negative(t_ieee754_float f);
bool	is_inf(t_ieee754_float f);
bool	is_nan(t_ieee754_float f);
bool	is_denormalized(t_ieee754_float f);

bool	is_d_negative(t_ieee754_double d);
bool	is_d_inf(t_ieee754_double d);
bool	is_d_nan(t_ieee754_double d);
bool	is_d_denormalized(t_ieee754_double d);
#endif 
