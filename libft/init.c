/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:29:07 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/04 14:21:09 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			get_size(t_flags *flags)
{
	int		nb;

	nb = ft_sizeofres(flags->cflag);
	if (flags->precision > nb)
		return (flags->precision);
	return (nb);
}

void		prepare_buf(t_buffin *all)
{
	if (all->curseur == -1)
	{
		all->end = 0;
		all->ret = 0;
		all->curseur = 0;
		ft_memset(all->buf, '\0', BUF_SIZE + 1);
	}
	else
	{
		all->end += ft_strlen(all->buf);
		ft_putstr(all->buf);
		ft_memset(all->buf, '\0', BUF_SIZE);
		all->ret = 0;
		all->curseur = 0;
	}
	return ;
}

void		initflags(t_flags *a_flag)
{
	a_flag->flag = 0;
	a_flag->largeur = 0;
	a_flag->precision = -1;
	a_flag->sign = '\0';
	init_cflags(a_flag);
	return ;
}

int			ft_chrpos(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (s[i]);
	return (-1);
}

void		init_cflags(t_flags *flags)
{
	int	size;

	size = 0;
	while (flags->cflag[size] != '\0')
	{
		flags->cflag[size] = '\0';
		size++;
	}
}
