/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noconv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:36:58 by cde-moul          #+#    #+#             */
/*   Updated: 2019/03/27 10:30:50 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_noconv(t_buffin *all, t_flags *flags, char c)
{
	flags->fcurse = 0;
	init_cflags(flags);
	flags->cflag[0] = c;
	if (flags->cflag[0] == '%')
		flags->flag &= ~SPACE;
	largeur(all, flags);
}
