/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:40:24 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:58:56 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		ft_c(t_buffin *all, t_flags *flags)
{
	flags->fcurse = 0;
	flags->cflag[0] = va_arg(all->ap, int);
	flags->cflag[1] = '\0';
	largeur(all, flags);
}

static char		*ft_precistr(t_flags *flags, char *str)
{
	char	srr[BUF_SIZE + 1];
	int		i;

	i = 0;
	if ((flags->precision > -1) && (flags->precision <= ft_sizeofres(str)))
	{
		while (flags->precision > 0)
		{
			srr[i] = str[i];
			i++;
			flags->precision--;
		}
		srr[i] = '\0';
		str = NULL;
		str = srr;
		return (str);
	}
	return (str);
}

static void		ft_str(t_buffin *all, t_flags *flags)
{
	char	*str;
	int		i;

	i = -1;
	flags->fcurse = 0;
	str = va_arg(all->ap, char *);
	if (str == NULL)
		str = "(null)";
	str = ft_precistr(flags, str);
	if (!(flags->flag & MOINS))
		largint(all, flags, ft_sizeofres(str));
	while (str[++i])
	{
		if (all->ret >= BUF_SIZE - 1)
			prepare_buf(all);
		all->buf[all->curseur++] = str[i];
		all->ret++;
	}
	if (flags->flag & MOINS)
		largint(all, flags, ft_sizeofres(str));
}

static void		ft_address(t_buffin *all, t_flags *flags)
{
	void			*addr;
	unsigned long	a;

	addr = va_arg(all->ap, void *);
	a = (unsigned long)addr;
	flags->flag |= DIESE;
	flags->flag |= SMALL_HEX;
	ft_conv_base2(all, flags, (unsigned long long)a);
}

void			ft_conversion(t_buffin *all, t_flags *flags)
{
	int		a;
	void	(*fonction[14])(t_buffin *all, t_flags *flags);

	fonction[0] = ft_c;
	fonction[1] = ft_str;
	fonction[2] = ft_address;
	fonction[3] = ft_double;
	fonction[4] = ft_sidec;
	fonction[5] = ft_sidec;
	fonction[6] = ft_un_dec;
	fonction[7] = ft_conv_base;
	fonction[8] = ft_conv_base;
	fonction[9] = ft_conv_base;
	fonction[10] = ft_conv_base;
	fonction[11] = ft_conv_base;
	fonction[12] = ft_tab_int;
	fonction[13] = ft_tab_str;
	a = ft_chrpos(CONV, flags->cflag[flags->fcurse]);
	if (a >= 10)
		flags->flag |= (1 << (10 + a));
	else
		flags->flag |= (1 << (a + 8));
	init_cflags(flags);
	flags->fcurse = 0;
	fonction[a](all, flags);
}
