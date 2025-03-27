/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INT_MAX
#include <limits.h>
#include "libft.h"
#include "ft_printf.h"

void	print(t_fmt *fmt, char *str, size_t len);

void	printf_c(t_fmt *fmt);
void	printf_s(t_fmt *fmt);

void	printf_c(t_fmt *fmt)
{
	char	c;

	c = (char)va_arg(fmt->ap, int);
	(fmt->format)++;
	print(fmt, &c, 1);
}

static size_t	ft_strnlen(char *str, size_t n)
{
	size_t	cnt;

	cnt = 0;
	while (*str && cnt < n)
	{
		cnt++;
		str++;
	}
	return (cnt);
}

void	printf_s(t_fmt *fmt)
{
	char	*s;
	size_t	len;

	s = va_arg(fmt->ap, char *);
	if (s == NULL)
		s = "(null)";
	(fmt->format)++;
	if ((fmt->flags & PRECISION_FLG))
		len = ft_strnlen(s, (size_t)fmt->precision);
	else
		len = ft_strlen(s);
	if (len > INT_MAX)
		fmt->out_size = -1;
	print(fmt, s, len);
}
