/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_px.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print(t_fmt *fmt, char *str, size_t len);
void	puthex(unsigned long long n, int capitals, char *prefix, t_fmt *fmt);

void	printf_p(t_fmt *fmt);
void	printf_x_lower(t_fmt *fmt);
void	printf_x_upper(t_fmt *fmt);

void	printf_p(t_fmt *fmt)
{
	unsigned long long	p;

	(fmt->format)++;
	p = va_arg(fmt->ap, unsigned long long);
	puthex(p, 0, "0x", fmt);
}

void	printf_x_lower(t_fmt *fmt)
{
	unsigned int	x;
	char			*prefix;

	(fmt->format)++;
	x = va_arg(fmt->ap, unsigned int);
	prefix = "";
	if ((fmt->flags & ALT_FLG) && x > 0)
		prefix = "0x";
	puthex(x, 0, prefix, fmt);
}

void	printf_x_upper(t_fmt *fmt)
{
	unsigned int	x;
	char			*prefix;

	(fmt->format)++;
	x = va_arg(fmt->ap, unsigned int);
	prefix = "";
	if ((fmt->flags & ALT_FLG) && x > 0)
		prefix = "0X";
	puthex(x, 16, prefix, fmt);
}
