/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:22:51 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 12:13:15 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "xlib.h"

int	xpipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret < 0)
		fatal_error("xpipe");
	return (ret);
}
