/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:47:52 by cde-moul          #+#    #+#             */
/*   Updated: 2019/04/03 12:48:44 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		ll_to_char(t_flags *flags, long long i)
{
	long long	cp;
	int			count;

	count = 0;
	if (i < 0)
		i *= -1;
	cp = i;
	if (i == 0)
		count++;
	while (cp >= 1 && count++ >= 0)
		cp = cp / 10;
	count = flags->fcurse + count;
	flags->fcurse = count;
	flags->cflag[count] = '\0';
	while (i > 9)
	{
		flags->cflag[--count] = (i % 10) + 48;
		i = i / 10;
	}
	flags->cflag[--count] = i + 48;
}

long long		ft_intpart_double(long double a)
{
	long long	i;
	long double	power;

	i = 0;
	power = 1;
	while (a / power >= 10 || a / power <= -10)
		power *= 10;
	while (power >= 1)
	{
		i = i * 10 + a / power;
		if (a >= 0)
		{
			while (a >= power)
				a -= power;
		}
		else
		{
			while (a <= -power)
				a += power;
		}
		power /= 10;
	}
	return (i);
}

static int		ft_sign(t_buffin *all, t_flags *flags, long double a)
{
	if (all->ret >= BUF_SIZE - 1)
		prepare_buf(all);
	if (a < 0)
		flags->sign = '-';
	else if ((flags->flag & PLUS) && a > 0)
		flags->sign = '+';
	else
	{
		flags->sign = '\0';
		return (0);
	}
	return (1);
}

static void		ft_precifloat(t_flags *flags, int *size)
{
	if (flags->precision == 0 && (!(flags->flag & DIESE)))
		return ;
	flags->cflag[flags->fcurse++] = '.';
	(*size)++;
}

void			double_to_char(t_buffin *all, t_flags *flags, long double a)
{
	long long	i;
	int			size;

	size = 0;
	i = ft_intpart_double(a);
	size = ft_sign(all, flags, a);
	if ((flags->largeur > 0) && !(flags->flag & MOINS))
		ft_largeur_float(all, flags, a);
	ll_to_char(flags, i);
	size = ft_sign(all, flags, a);
	if (a < 0)
		a *= -1;
	if (i < 0)
		i *= -1;
	a = a - i;
	ft_precifloat(flags, &size);
	ft_decimal_float(all, flags, a);
	if ((flags->flag & MOINS) && (flags->largeur > 0))
		largeur2_float(all, flags, a + i, size);
}
