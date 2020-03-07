/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:09:15 by cde-moul          #+#    #+#             */
/*   Updated: 2019/04/03 13:46:27 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			ft_change_base2(t_buffin *all, t_flags *flags, char **base)
{
	if (flags->flag & OCTAL)
		*base = BASE_OCTAL;
	else if (flags->flag & SMALL_HEX)
		*base = BASE_SHEX;
	else if (flags->flag & BINAIRE)
	{
		*base = BASE_BIN;
		flags->precision = 0;
	}
	else if (flags->flag & CHOOSE_BASE)
		*base = va_arg(all->ap, char *);
	else
		*base = BASE_BHEX;
}

static void		ft_prec(t_buffin *all, t_flags *flags, int size)
{
	flags->fcurse = 0;
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
	if (!(flags->flag & OCTAL && flags->flag & MOINS))
		init_cflags(flags);
}

static void		large_int(t_buffin *all, t_flags *flags, int size)
{
	int	i;

	if ((flags->flag & DIESE) && ((flags->flag & SMALL_HEX ||
					flags->flag & BIG_HEX || flags->flag & ADDRESS)))
		size = size + 2;
	else if ((flags->flag & DIESE) && (flags->flag & OCTAL))
		size++;
	if ((flags->flag & DIESE) && (flags->flag & ZERO)
			&& (flags->precision == -1))
		ft_diese(all, flags);
	largint(all, flags, size);
	i = ft_sizeofres(flags->cflag);
	if ((flags->flag & DIESE) && (!(flags->flag & ZERO)
				|| (flags->flag & ZERO && flags->precision != -1)))
		ft_diese(all, flags);
	ft_prec(all, flags, i);
}

static void		large_int2(t_buffin *all, t_flags *flags, int size)
{
	if (flags->flag & DIESE)
	{
		if (flags->flag & OCTAL)
			size++;
		else if ((flags->flag & SMALL_HEX) || (flags->flag & BIG_HEX))
			size = size + 2;
		ft_diese(all, flags);
	}
	ft_prec(all, flags, ft_sizeofres(flags->cflag));
	largint(all, flags, size);
}

void			precibase(t_buffin *all, t_flags *flags)
{
	int i;

	i = 0;
	if (flags->flag & DIESE && (flags->flag & OCTAL)
			&& flags->cflag[0] != '0' && flags->precision > 0)
		flags->precision--;
	if (flags->cflag[0] == '0' && flags->precision == 0)
		flags->cflag[0] = '\0';
	if (!(flags->flag & MOINS) && !(flags->flag & SPACE))
		large_int(all, flags, get_size2(flags));
	else
		large_int2(all, flags, get_size(flags));
}
