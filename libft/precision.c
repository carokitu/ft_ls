/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:09:15 by cde-moul          #+#    #+#             */
/*   Updated: 2019/04/01 13:25:40 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			largint(t_buffin *all, t_flags *flags, int size)
{
	char c;

	c = ' ';
	if (flags->flag & ZERO && !(flags->flag & MOINS)
			&& (flags->precision == -1))
		c = '0';
	if (flags->flag & OCTAL && flags->cflag[0] == '0' && flags->largeur == 0)
		flags->flag &= ~DIESE;
	while (flags->largeur > size)
	{
		if (all->ret >= BUF_SIZE - 1)
			prepare_buf(all);
		all->buf[all->curseur++] = c;
		flags->largeur--;
		all->ret++;
	}
	if (flags->largeur > 0 && flags->cflag[0] == '0'
			&& flags->flag & DIESE && flags->flag & OCTAL && (++all->ret > -1))
		all->buf[all->curseur++] = ' ';
	if (flags->flag & OCTAL && flags->flag & MOINS)
		init_cflags(flags);
	flags->largeur = 0;
}

static void		ft_prec(t_buffin *all, t_flags *flags, int size)
{
	flags->fcurse = 0;
	if (flags->cflag[0] == '-' || flags->cflag[0] == '+'
			|| flags->cflag[0] == ' ')
	{
		flags->fcurse++;
		all->buf[all->curseur++] = flags->cflag[0];
		all->ret++;
	}
	quick_check(flags);
	while ((flags->precision-- - size) > 0)
	{
		if (all->ret >= BUF_SIZE - 1)
			prepare_buf(all);
		all->buf[all->curseur++] = '0';
		all->ret++;
	}
	while (flags->cflag[flags->fcurse] != '\0')
	{
		if (all->ret >= BUF_SIZE - 1)
			prepare_buf(all);
		all->buf[all->curseur++] = flags->cflag[flags->fcurse++];
		all->ret++;
	}
	init_cflags(flags);
}

static void		large_int(t_buffin *all, t_flags *flags, int size)
{
	int	i;

	largint(all, flags, size);
	i = ft_sizeofres(flags->cflag);
	if ((flags->cflag[0] == '-') || (flags->cflag[0] == ' ')
			|| (flags->cflag[0] == '+'))
		i--;
	ft_prec(all, flags, i);
}

static void		large_int2(t_buffin *all, t_flags *flags, int size)
{
	int size2;

	size2 = ft_sizeofres(flags->cflag);
	if (flags->cflag[0] == '-' || flags->cflag[0] == '+'
			|| flags->cflag[0] == ' ')
	{
		size2--;
		size++;
	}
	ft_prec(all, flags, size2);
	largint(all, flags, size);
}

void			precisint(t_buffin *all, t_flags *flags)
{
	int i;

	i = 0;
	if (!(flags->flag & MOINS) && !(flags->flag & SPACE))
		large_int(all, flags, get_size2(flags));
	else if (flags->flag & SPACE)
	{
		if (!(flags->cflag[0] == '-') && flags->largeur <= get_size(flags))
		{
			i = ft_sizeofres(flags->cflag);
			i--;
			while (flags->cflag[i])
			{
				flags->cflag[i + 1] = flags->cflag[i];
				i--;
			}
			flags->cflag[0] = ' ';
		}
		large_int(all, flags, get_size2(flags));
	}
	else
		large_int2(all, flags, get_size(flags));
}
