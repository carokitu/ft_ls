/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 11:57:37 by cde-moul          #+#    #+#             */
/*   Updated: 2019/04/01 13:33:22 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				ft_sizeofres(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int				get_size2(t_flags *flags)
{
	int	nb;

	nb = ft_sizeofres(flags->cflag);
	if (flags->precision >= nb)
	{
		if (!(flags->cflag[0] == '-') && !(flags->cflag[0] == ' ')
				&& !(flags->cflag[0] == '+'))
			return (flags->precision);
		nb = flags->precision + 1;
	}
	return (nb);
}

void			quick_check(t_flags *flags)
{
	if (flags->precision == 0)
	{
		if (flags->cflag[0] == '0')
			flags->cflag[0] = '\0';
		else if ((flags->cflag[0] == '-' || flags->cflag[0] == '+'
					|| flags->cflag[0] == ' ')
				&& (flags->cflag[1] == '0'))
			flags->cflag[1] = '\0';
	}
	return ;
}

void			largeur2_float(t_buffin *all, t_flags *flags,
		long double a, int size)
{
	a *= 10;
	while ((a /= 10) >= 10)
		size++;
	size++;
	size = size + flags->precision;
	while ((flags->largeur - size) > 0)
	{
		if (all->ret >= BUF_SIZE - 1)
			prepare_buf(all);
		all->buf[all->ret] = ' ';
		all->ret++;
		size++;
	}
}

void			ft_double(t_buffin *all, t_flags *flags)
{
	long double	a;

	prepare_buf(all);
	if (flags->flag & BIG_L)
		a = va_arg(all->ap, long double);
	else
		a = (long double)va_arg(all->ap, double);
	if (flags->precision == -1)
		flags->precision = 6;
	double_to_char(all, flags, a);
}
