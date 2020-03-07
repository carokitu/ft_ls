/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:56:28 by cde-moul          #+#    #+#             */
/*   Updated: 2019/04/03 13:33:44 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	ft_diese2(t_buffin *all, t_flags *flags)
{
	char	c;

	if (flags->flag & SMALL_HEX)
		c = 'x';
	else
		c = 'X';
	all->buf[all->curseur++] = '0';
	all->buf[all->curseur++] = c;
	all->ret = all->ret + 2;
	if (all->ret >= BUF_SIZE - 1)
		prepare_buf(all);
}

void		ft_diese(t_buffin *all, t_flags *flags)
{
	if (flags->flag & OCTAL)
	{
		if (flags->cflag[0] != '0')
		{
			all->buf[all->curseur++] = '0';
			all->ret++;
		}
		if (all->ret >= BUF_SIZE - 1)
			prepare_buf(all);
	}
	else if ((flags->flag & SMALL_HEX) || (flags->flag & BIG_HEX))
		ft_diese2(all, flags);
}

static void	ft_change_base(t_buffin *all, t_flags *flags, unsigned long long a)
{
	char				*base;
	int					size;
	unsigned long long	cp;

	cp = a;
	ft_change_base2(all, flags, &base);
	size = ft_sizeofres(base);
	while (cp / size > 0)
	{
		flags->fcurse++;
		cp = cp / size;
	}
	flags->cflag[flags->fcurse] = '\0';
	while (a / size > 0)
	{
		flags->cflag[flags->fcurse--] = base[a % size];
		a = a / size;
	}
	flags->cflag[flags->fcurse--] = base[a % size];
	flags->cflag[flags->fcurse] = '\0';
}

void		ft_conv_base2(t_buffin *all, t_flags *flags, unsigned long long a)
{
	flags->fcurse = 0;
	if (a == 0 && (!(flags->flag & OCTAL || flags->flag & ADDRESS)))
	{
		if (flags->precision != 0
				|| (flags->precision == 0
					&& (flags->flag & BIG_HEX || flags->flag & SMALL_HEX)))
			flags->flag &= ~DIESE;
	}
	ft_change_base(all, flags, a);
	precibase(all, flags);
	largeur(all, flags);
}

void		ft_conv_base(t_buffin *all, t_flags *flags)
{
	unsigned long long	a;

	if (flags->flag & LONE_H)
		a = (unsigned long long)(unsigned short int)
			va_arg(all->ap, unsigned int);
	else if (flags->flag & LONE_L)
		a = (unsigned long long)va_arg(all->ap, unsigned long);
	else if (flags->flag & BIG_L)
		a = (unsigned long long)(double long)va_arg(all->ap, unsigned int);
	else if (flags->flag & DOUBLE_H)
		a = (unsigned long long)(unsigned char)va_arg(all->ap, unsigned int);
	else if (flags->flag & DOUBLE_L)
		a = va_arg(all->ap, unsigned long long);
	else
		a = (unsigned long long)va_arg(all->ap, unsigned int);
	ft_conv_base2(all, flags, a);
}
