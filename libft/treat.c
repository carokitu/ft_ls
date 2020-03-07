/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:42:19 by cde-moul          #+#    #+#             */
/*   Updated: 2019/04/03 12:14:29 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void			recup_arg2(const char *format, int *count, t_buffin *all)
{
	int	flag_count;

	flag_count = -1;
	while ((all->flags->cflag)[++flag_count] != '\0')
		(all->flags->cflag)[++flag_count] = '\0';
	flag_count = -1;
	while (format[++(*count)] && ft_strchr(ALL_CONV, format[*count]) != NULL)
	{
		(all->flags->cflag)[++(flag_count)] = format[*count];
		if (ft_strchr(CONV, format[*count]) != NULL)
		{
			(all->flags->cflag)[++flag_count] = '\0';
			ft_conv(all);
			return ;
		}
	}
	if (ft_strchr(CONV, format[*count]) == NULL)
	{
		if (format[*count])
			(all->flags->cflag)[++flag_count] = format[*count];
		(all->flags->cflag)[++flag_count] = '\0';
		ft_conv(all);
	}
	else
		(all->flags->cflag)[++flag_count] = '\0';
}

static void			recup_arg(const char *format, int *count, t_buffin *all)
{
	t_flags a_flag[1];

	initflags(a_flag);
	all->flags = a_flag;
	recup_arg2(format, count, all);
	return ;
}

static void			ft_printf2(t_buffin *all, char c)
{
	(all->buf)[all->curseur] = c;
	all->ret++;
	all->curseur++;
}

int					ft_printf(const char *format, ...)
{
	int			count;
	t_buffin	all[1];

	va_start(all->ap, format);
	all->curseur = -1;
	all->ret = -1;
	all->end = 0;
	count = 0;
	prepare_buf(all);
	while (format[count] != '\0')
	{
		if (all->ret >= BUF_SIZE - 1)
			prepare_buf(all);
		if (format[count] != '%')
			ft_printf2(all, format[count]);
		else if (format[count] == '%')
			recup_arg(format, &count, all);
		count++;
	}
	all->end += ft_strlen(all->buf);
	ft_putstr(all->buf);
	return (all->end);
}
