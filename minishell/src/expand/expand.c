/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:45:23 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/27 15:34:05 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "xlib.h"
#include "minishell.h"
#include <ctype.h>

void	expand(t_node *node, t_context *ctx);

/* ************************************************************************** */
void	expand(t_node *node, t_context *ctx)
{
	expand_parameter(node, ctx);
	expand_word_splitting(node, ctx);
	expand_quote_removal(node);
}
