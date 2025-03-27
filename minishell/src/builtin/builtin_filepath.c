/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_filepath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:25:13 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 00:05:40 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"

bool			consume_path(char **rest, char *path, char *elm);
void			delete_last_path_elm(char *path);
void			append_path_elm(char *dst, size_t dstsize, char **rest, \
																	char *src);
static size_t	strlncpy(char *dst, char *src, size_t n, size_t dstsize);

/* ************************************************************************** */
bool	consume_path(char **rest, char *path, char *elm)
{
	size_t	elm_len;

	elm_len = ft_strlen(elm);
	if (ft_strncmp(path, elm, elm_len) == 0)
	{
		if (path[elm_len] == '\0' || path[elm_len] == '/')
		{
			*rest = path + elm_len;
			return (true);
		}
	}
	return (false);
}

/* ************************************************************************** */
void	delete_last_path_elm(char *path)
{
	char	*start;
	char	*last_slash_ptr;

	start = path;
	last_slash_ptr = NULL;
	while (*path)
	{
		if (*path == '/')
			last_slash_ptr = path;
		path++;
	}
	if (last_slash_ptr != start)
		*last_slash_ptr = '\0';
}

/* ************************************************************************** */
void	append_path_elm(char *dst, size_t dstsize, char **rest, char *src)
{
	char	buf[PATH_MAX];
	size_t	elm_len;

	elm_len = 0;
	while (src[elm_len] && src[elm_len] != '/')
		elm_len++;
	if (strlncpy(buf, src, elm_len, PATH_MAX) >= PATH_MAX)
		assert_error("This will not happen");
	if (dst[ft_strlen(dst) - 1] != '/')
		if (ft_strlcat(dst, "/", dstsize) >= dstsize)
			assert_error("This will not happen");
	if (ft_strlcat(dst, buf, dstsize) >= dstsize)
		assert_error("This will not happen");
	*rest = src + elm_len;
}

/* ************************************************************************** */
static size_t	strlncpy(char *dst, char *src, size_t n, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && n > 0 && *src)
	{
		dst[i] = *src;
		src++;
		i++;
		n--;
	}
	dst[i] = '\0';
	while (n > 0 && *src)
	{
		i++;
		n--;
		src++;
	}
	return (i);
}
