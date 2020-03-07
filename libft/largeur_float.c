/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   largeur_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:50:25 by cde-moul          #+#    #+#             */
/*   Updated: 2019/04/03 12:49:28 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		ft_get_size_float(t_flags *flags, long double a)
{
	int	size;
	int	i;

	i = 1;
	size = 0;
	if (a < 0 || flags->flag & PLUS)
		size++;
	while (a / i <= -10 || a / i >= 10)
	{
		size++;
		i = i * 10;
	}
	size++;
	if ((flags->precision == 0 && flags->flag & DIESE) || flags->precision != 0)
		size++;
	size = size + flags->precision;
	return (size);
}

static void		ft_largeur2_float(t_buffin *all,
		t_flags *flags, char c, int size)
{
	prepare_buf(all);
	init_cflags(flags);
	flags->fcurse = 0;
	if (size == 1)
	{
		flags->cflag[flags->fcurse] = c;
		flags->fcurse++;
	}
	return ;
}

void			ft_largeur_float(t_buffin *all, t_flags *flags, long double a)
{
	int		i;
	int		size;
	char	c;

	i = 0;
	c = ' ';
	if (flags->flag & ZERO)
		c = '0';
	size = flags->largeur - ft_get_size_float(flags, a);
	while (size > 1)
	{
		if (all->ret >= BUF_SIZE - 1)
			prepare_buf(all);
		all->buf[all->curseur++] = c;
		all->ret++;
		size--;
	}
	if (!(flags->flag & MOINS))
	{
		ft_largeur2_float(all, flags, c, size);
		return ;
	}
	all->buf[all->curseur++] = c;
	all->ret++;
}
