/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:11:17 by cde-moul          #+#    #+#             */
/*   Updated: 2019/03/28 15:16:50 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_sizeofres_diese(t_flags *flags)
{
	int i;

	i = ft_sizeofres(flags->cflag);
	if (flags->flag & DIESE)
	{
		if (flags->flag & OCTAL)
			i++;
		else if (flags->flag & BIG_HEX || flags->flag & SMALL_HEX)
			i = i + 2;
	}
	return (1);
}

void		largeur2(t_buffin *all, t_flags *flags)
{
	char	c;

	c = 0;
	flags->fcurse = 0;
	if (flags->flag & CHAR && (flags->cflag[flags->fcurse] == '\0'))
	{
		prepare_buf(all);
		write(1, &c, 1);
		all->end++;
		init_cflags(flags);
		flags->fcurse = 0;
	}
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

static void	largeur_ext(t_buffin *all, t_flags *flags)
{
	all->buf[all->curseur++] = flags->cflag[0];
	flags->fcurse++;
	all->ret++;
	flags->fcurse = 0;
	while (flags->cflag[flags->fcurse + 1])
	{
		flags->cflag[flags->fcurse] = flags->cflag[flags->fcurse + 1];
		flags->fcurse++;
	}
	flags->cflag[flags->fcurse] = '\0';
}

static void	largeuur(t_buffin *all, t_flags *flags, int nb)
{
	while (nb > 0)
	{
		if (all->ret == BUF_SIZE - 1)
			prepare_buf(all);
		if (flags->flag & ZERO)
			all->buf[all->curseur] = '0';
		else
			all->buf[all->curseur] = ' ';
		nb--;
		all->curseur++;
		all->ret++;
	}
}

void		largeur(t_buffin *all, t_flags *flags)
{
	int		nb;

	if ((flags->flag & CHAR) && (flags->cflag[0] == '\0'))
		flags->largeur--;
	nb = flags->largeur - ft_sizeofres(flags->cflag);
	flags->fcurse = 0;
	if (flags->flag & MOINS)
		largeur2(all, flags);
	else if ((flags->cflag[0] == '-' || flags->cflag[0] == '+')
			&& flags->flag & ZERO)
		largeur_ext(all, flags);
	else if (flags->flag & SPACE && (flags->largeur == 0) &&
			(all->ret++ >= 0) && !(flags->cflag[0] == '-'
				|| flags->cflag[0] == '+'))
		all->buf[all->curseur++] = ' ';
	largeuur(all, flags, nb);
	if (!(flags->flag & MOINS))
		largeur2(all, flags);
}
