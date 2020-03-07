/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:56:42 by cde-moul          #+#    #+#             */
/*   Updated: 2019/03/22 10:54:39 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		ft_round2(t_buffin *all, t_flags *flags, int modify)
{
	if (flags->cflag[modify] == ' ')
	{
		ft_putchar(flags->sign);
		flags->sign = '\0';
		flags->cflag[modify] = '1';
		flags->fcurse = 0;
		largeur2(all, flags);
		prepare_buf(all);
		return ;
	}
	all->buf[all->curseur++] = '1';
	all->ret++;
	ft_putchar(flags->sign);
	flags->sign = '\0';
	largeur2(all, flags);
	prepare_buf(all);
}

static void		largeur3(t_buffin *all, t_flags *flags)
{
	flags->fcurse = 0;
	if (flags->cflag[flags->fcurse] == ' ')
		ft_putchar(flags->cflag[flags->fcurse++]);
	ft_putchar(flags->sign);
	while (flags->cflag[flags->fcurse] != '\0')
	{
		if (all->ret == BUF_SIZE - 1)
			prepare_buf(all);
		all->buf[all->curseur] = flags->cflag[flags->fcurse];
		flags->fcurse++;
		all->curseur++;
		all->ret++;
	}
}

static void		ft_round(t_buffin *all, t_flags *flags, int round)
{
	int		modify;

	modify = ft_sizeofres(flags->cflag) - 1;
	if (round < 5)
	{
		flags->fcurse = 0;
		largeur3(all, flags);
		prepare_buf(all);
		return ;
	}
	while (flags->cflag[modify] == '9' || flags->cflag[modify] == '.')
	{
		if (flags->cflag[modify] == '9')
			flags->cflag[modify] = '0';
		modify--;
	}
	if (flags->cflag[modify] <= '9' && flags->cflag[modify] >= '0')
	{
		flags->cflag[modify]++;
		flags->fcurse = 0;
		largeur3(all, flags);
		prepare_buf(all);
	}
	else
		ft_round2(all, flags, modify);
}

void			ft_decimal_float(t_buffin *all, t_flags *flags, long double a)
{
	int b;
	int round;
	int prec;

	prec = flags->precision;
	round = 0;
	b = 0;
	while (prec-- > 0)
	{
		if (flags->fcurse >= BUF_SIZE - 1)
		{
			flags->fcurse = 0;
			largeur2(all, flags);
			flags->fcurse = 0;
			init_cflags(flags);
		}
		a *= 10;
		b = (int)ft_intpart_double(a);
		flags->cflag[flags->fcurse++] = b + 48;
		a = a - b;
	}
	a *= 10;
	round = (int)ft_intpart_double(a);
	a = all->curseur;
	ft_round(all, flags, round);
}
