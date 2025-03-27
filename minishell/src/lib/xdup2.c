/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:13:21 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/26 23:30:17 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	xdup2(int fildes, int fildes2)
{
	int	fd;

	fd = dup2(fildes, fildes2);
	if (fd < 0)
	{
		if (fildes2 == STDIN_FILENO)
			fd = dup2(0, fildes2);
		else if (fildes2 == STDOUT_FILENO)
			fd = dup2(1, fildes2);
		exit(1);
	}
	return (fd);
}
