/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 23:11:01 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 11:57:19 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "minishell.h"

int	xclose(int fd)
{
	if (fd < 0)
		return (-1);
	if (close(fd) < 0)
		fatal_error("xclose");
	return (0);
}
