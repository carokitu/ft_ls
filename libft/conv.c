/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:14:54 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:55:55 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	ft_precision(t_buffin *all, t_flags *flags)
{
	if (flags->precision != 0)
		flags->precision = 0;
	flags->fcurse++;
	if (flags->cflag[flags->fcurse] == '*')
	{
		flags->precision = va_arg(all->ap, int);
		return ;
	}
	while (ft_strchr(LARGEUR, flags->cflag[flags->fcurse]) != NULL)
	{
		flags->precision = (flags->precision * 10)\
			+ ((flags->cflag[flags->fcurse]) - 48);
		flags->fcurse++;
	}
	flags->fcurse--;
}

static void	ft_flags2(t_flags *flags, int a)
{
	if ((flags->flag & LONE_H) || (flags->flag & LONE_L)\
			|| (flags->flag & BIG_L) || (flags->flag & DOUBLE_H)\
			|| (flags->flag & DOUBLE_L))
		return ;
	else if (a == 5 && flags->cflag[flags->fcurse + 1] == 'h')
		flags->flag |= (1 << 18);
	else if (a == 6 && flags->cflag[flags->fcurse + 1])
		flags->flag |= (1 << 19);
	else
		flags->flag |= (1 << a);
}

static void	ft_flags(t_flags *flags)
{
	int		a;

	a = ft_chrpos(FLAGS, flags->cflag[flags->fcurse]);
	while (a != -1)
	{
		if ((a == 1 && (flags->flag & ZERO))\
			|| (a == 2 && (flags->flag & SPACE)))
		{
			if (a == 1)
				flags->flag &= ~(1 << 0);
			if (a == 2)
				flags->flag &= ~(1 << 3);
			flags->flag |= (1 << a);
		}
		if (a <= 7 && a >= 5)
			ft_flags2(flags, a);
		else if (!(a == 0 && (flags->flag & MOINS))\
				&& !(a == 3 && (flags->flag & PLUS)))
			flags->flag |= (1 << a);
		flags->fcurse++;
		a = ft_chrpos(FLAGS, flags->cflag[flags->fcurse]);
	}
	flags->fcurse--;
}

static void	ft_largeur(t_buffin *all, t_flags *flags)
{
	if (flags->largeur != 0)
		flags->largeur = 0;
	if (flags->cflag[flags->fcurse] == '*')
	{
		flags->largeur = va_arg(all->ap, int);
		return ;
	}
	while (ft_strchr(LARGEUR, flags->cflag[flags->fcurse]) != NULL)
	{
		flags->largeur = (flags->largeur * 10)\
			+ ((flags->cflag[flags->fcurse]) - 48);
		flags->fcurse++;
	}
	flags->fcurse--;
}

void		ft_conv(t_buffin *all)
{
	int		*flag_count;

	all->flags->fcurse = 0;
	if (all->flags->flag != 0)
		all->flags->flag = 0;
	flag_count = &all->flags->fcurse;
	while ((all->flags->cflag)[*flag_count])
	{
		if (ft_strchr(FLAGS, (all->flags->cflag)[*flag_count]) != NULL)
			ft_flags(all->flags);
		else if (ft_strchr(LARGEUR, (all->flags->cflag)[*flag_count]) != NULL)
			ft_largeur(all, all->flags);
		else if (ft_strchr(PRECISION, (all->flags->cflag)[*flag_count]) != NULL)
			ft_precision(all, all->flags);
		else if (ft_strchr(CONV, (all->flags->cflag)[*flag_count]) != NULL)
			ft_conversion(all, all->flags);
		else if (ft_strchr(ALL_CONV, all->flags->cflag[*flag_count]) == NULL)
			ft_noconv(all, all->flags, all->flags->cflag[*flag_count]);
		(*flag_count)++;
	}
}
