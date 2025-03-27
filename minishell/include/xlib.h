/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:50:04 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLIB_H
# define XLIB_H

# include <signal.h>
# include <sys/stat.h>

// src/lib/
void	*xmalloc(size_t size);
void	*xcalloc(size_t count, size_t size);
char	*xstrdup(const char *s1);
char	*xstrndup(const char *s1, size_t size);
int		xclose(int fd);
int		xdup2(int fildes, int fildes2);
int		xpipe(int fildes[2]);

#endif
