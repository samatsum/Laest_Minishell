/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	fmt_clear_spec(t_fmt *fmt);
void	fmt_init(t_fmt *fmt, const char *format);

void	fmt_clear_spec(t_fmt *fmt)
{
	fmt->conversion = 0;
	fmt->width = 0;
	fmt->precision = 0;
	fmt->flags = 0;
	fmt->sign_c = 0;
	fmt->buf_len = 0;
}

void	fmt_init(t_fmt *fmt, const char *format)
{
	ft_bzero(fmt, sizeof(t_fmt));
	fmt->format = format;
}
