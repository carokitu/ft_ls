/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convdec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:57:34 by cde-moul          #+#    #+#             */
/*   Updated: 2019/04/03 17:24:29 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		nbr_to_char2(t_flags *flags, long long *a, int *count)
{
	if (*a < 0)
	{
		*a = *a * -1;
		flags->cflag[0] = '-';
	}
	else
		flags->cflag[0] = '+';
	(*count)++;
}

void			nbr_to_char(t_flags *flags, long long a)
{
	long long	cp;
	int			count;

	count = 0;
	if ((a < 0) || (a >= 0 && (flags->flag & PLUS)))
		nbr_to_char2(flags, &a, &count);
	cp = a;
	if (a == 0)
		count++;
	while (cp > 0)
	{
		cp = cp / 10;
		count++;
	}
	flags->cflag[count] = '\0';
	while (a > 9)
	{
		flags->cflag[--count] = (a % 10) + 48;
		a = a / 10;
	}
	flags->cflag[--count] = a + 48;
	nbr_to_char_extreme(flags, a);
}

static void		unbr_to_char(t_flags *flags, unsigned long long a)
{
	unsigned long long	cp;
	int					count;

	count = 0;
	cp = a;
	if (a == 0)
		count++;
	while (cp > 0)
	{
		cp = cp / 10;
		count++;
	}
	flags->cflag[count] = '\0';
	while (a > 9)
	{
		flags->cflag[--count] = (a % 10) + 48;
		a = a / 10;
	}
	flags->cflag[--count] = a + 48;
}

void			ft_sidec(t_buffin *all, t_flags *flags)
{
	long long	a;

	if (flags->flag & LONE_H)
		a = (long long)(short int)va_arg(all->ap, int);
	else if (flags->flag & LONE_L)
		a = (long long)va_arg(all->ap, long);
	else if (flags->flag & BIG_L)
		a = (long long)(double long)va_arg(all->ap, int);
	else if (flags->flag & DOUBLE_H)
		a = (long long)(char)va_arg(all->ap, int);
	else if (flags->flag & DOUBLE_L)
		a = va_arg(all->ap, long long);
	else
		a = (long long)va_arg(all->ap, int);
	nbr_to_char(flags, a);
	if (flags->cflag[0] == '0' && flags->precision == 0)
		init_cflags(flags);
	if (flags->precision >= 0)
		precisint(all, flags);
	else
		largeur(all, flags);
}

void			ft_un_dec(t_buffin *all, t_flags *flags)
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
	if (flags->flag & PLUS)
		flags->flag &= ~PLUS;
	if (flags->flag & SPACE)
		flags->flag &= ~SPACE;
	unbr_to_char(flags, a);
	if (flags->precision >= 0)
		precisint(all, flags);
	else
		largeur(all, flags);
}
