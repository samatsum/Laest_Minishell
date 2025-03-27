/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argparse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:36 by samatsum          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:08 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARGPARSE_H
# define FT_ARGPARSE_H

# define AP_NONEG	01	
# define AP_GT_0	02	

# define AP_ANY_BASE	0100	
# define AP_BASE_8		0200	
# define AP_BASE_16		0400	

long	ft_argparse_long(const char *arg, int flags, const char *var_name);
int		ft_argparse_int(const char *arg, int flags, const char *var_name);

#endif
