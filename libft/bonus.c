/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:49:55 by cde-moul          #+#    #+#             */
/*   Updated: 2019/04/09 13:31:08 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		get_largeur_tab(t_buffin *all, t_flags *flags)
{
	int i;

	i = 0;
	while (flags->cflag[i])
		i++;
	while (i < 11)
	{
		if (all->ret >= BUF_SIZE - 1)
			prepare_buf(all);
		all->buf[all->curseur++] = ' ';
		all->ret++;
		i++;
	}
}

static void		ft_tab(t_buffin *all, t_flags *flags)
{
	largeur2(all, flags);
	init_cflags(flags);
	flags->fcurse = 0;
}

void			ft_tab_int(t_buffin *all, t_flags *flags)
{
	int		**tab;
	int		i;
	int		size_tab;

	i = 0;
	tab = va_arg(all->ap, int **);
	size_tab = va_arg(all->ap, int);
	while (i < size_tab)
	{
		ft_strcpy(flags->cflag, "l'int de tab[");
		ft_tab(all, flags);
		nbr_to_char(flags, i);
		ft_tab(all, flags);
		ft_strcpy(flags->cflag, "] est : ");
		ft_tab(all, flags);
		nbr_to_char(flags, (*tab)[i]);
		get_largeur_tab(all, flags);
		ft_tab(all, flags);
		ft_strcpy(flags->cflag, "\n");
		ft_tab(all, flags);
		i++;
	}
}

void			ft_tab_str(t_buffin *all, t_flags *flags)
{
	char	***tab;
	int		i;
	int		size_tab;

	i = 0;
	tab = va_arg(all->ap, char ***);
	size_tab = va_arg(all->ap, int);
	while (i < size_tab)
	{
		ft_strcpy(flags->cflag, "l'int de tab[");
		ft_tab(all, flags);
		nbr_to_char(flags, i);
		ft_tab(all, flags);
		ft_strcpy(flags->cflag, "] est : ");
		ft_tab(all, flags);
		if ((*tab)[i])
			ft_strcpy(flags->cflag, (*tab)[i]);
		else
			ft_strcpy(flags->cflag, "(null)");
		ft_tab(all, flags);
		ft_strcpy(flags->cflag, "\n");
		ft_tab(all, flags);
		i++;
	}
}

void			nbr_to_char_extreme(t_flags *flags, long long a)
{
	if (flags->cflag[0] == '0' && a != 0 && (flags->flag & DOUBLE_L))
	{
		ft_strcpy(flags->cflag, "-9223372036854775808");
		flags->fcurse = 20;
	}
}
