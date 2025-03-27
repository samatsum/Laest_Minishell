/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DECIMAL_H
# define FT_DECIMAL_H

# define DOUBLE_MAX_INT 310
# define DOUBLE_MAX_FRACT 1075

// t_decimal can store a number in decimal format
typedef struct s_decimal {
	char	int_digits[DOUBLE_MAX_INT];
	char	fract_digits[DOUBLE_MAX_FRACT];
	int		precision;
}	t_decimal;

t_decimal	new_decimal(unsigned long long num);
t_decimal	mul_decimal(t_decimal decimal, int n);
t_decimal	div_decimal(t_decimal decimal, int n);
void		decimal_to_str(t_decimal decimal, char *res, int precision);
#endif
