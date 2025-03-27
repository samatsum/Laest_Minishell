/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stashfd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:16:52 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/26 18:35:42 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include "xlib.h"
#include "minishell.h"

int			stashfd(int fd);
static bool	is_valid_fd(int fd);

/* ************************************************************************** */
int	stashfd(int fd)
{
	int	stashfd;

	if (!is_valid_fd(fd))
	{
		errno = EBADF;
		return (-1);
	}
	stashfd = 10;
	while (is_valid_fd(stashfd))
		stashfd++;
	stashfd = xdup2(fd, stashfd);
	xclose(fd);
	return (stashfd);
}

/* ************************************************************************** */
static bool	is_valid_fd(int fd)
{
	struct stat	st;

	if (fd < 0)
		return (false);
	errno = 0;
	if (fstat(fd, &st) < 0 && errno == EBADF)
		return (false);
	return (true);
}
