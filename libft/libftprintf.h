/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:42:32 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 12:36:10 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include "libft/libft.h"

# define ALL_CONV "0-+ #hlLcspfdiuoxX*0123456789.bkae"
# define ALL_FLAGS "lhL#0+- 0123456789.*"
# define CONV "cspfdiuoxXbkae"
# define FLAGS "0-+ #hlL"
# define PRECISION "."
# define LARGEUR "0123456789*"
# define BUF_SIZE 1600

# define BASE_OCTAL "01234567"
# define BASE_SHEX "0123456789abcdef"
# define BASE_BHEX "0123456789ABCDEF"
# define BASE_DEC "0123456789"
# define BASE_BIN "01"

# define ZERO (1 << 0)
# define MOINS (1 << 1)
# define PLUS (1 << 2)
# define SPACE (1 << 3)
# define DIESE (1 << 4)

# define LONE_H (1 << 5)
# define LONE_L (1 << 6)
# define BIG_L (1 << 7)

# define CHAR (1 << 8)
# define STRING (1 << 9)
# define ADDRESS (1 << 10)

# define DOUBLE (1 << 11)
# define SI_DEC1 (1 << 12)
# define SI_DEC2 (1 << 13)
# define UN_DEC (1 << 14)
# define OCTAL (1 << 15)
# define SMALL_HEX (1 << 16)
# define BIG_HEX (1 << 17)

# define DOUBLE_H (1 << 18)
# define DOUBLE_L (1 << 19)
# define BINAIRE (1 << 20)
# define CHOOSE_BASE (1 << 21)
# define TAB_INT (1 << 22)
# define TAB_STR (1 << 23)

typedef struct			s_flags
{
	char				cflag[BUF_SIZE + 1];
	int					flag;
	int					largeur;
	int					precision;
	int					fcurse;
	char				sign;
}						t_flags;

typedef struct			s_buffin
{
	char				buf[BUF_SIZE + 1];
	int					curseur;
	int					ret;
	va_list				ap;
	struct s_flags		*flags;
	int					end;
}						t_buffin;

/*
** treat.c
*/

int						ft_printf(const char *format, ...);

/*
** init.c
*/

void					prepare_buf(t_buffin *all);
void					initflags(t_flags *a_flag);
int						ft_chrpos(const char *s, int c);
void					init_cflags(t_flags *flags);
int						get_size(t_flags *flags);

/*
** conv.c
*/

void					ft_conv(t_buffin *all);

/*
** conv2.c
*/

void					ft_conversion(t_buffin *all, t_flags *flags);

/*
** no_conv.c
*/

void					ft_noconv(t_buffin *all, t_flags *flags, char c);

/*
** largeur.c
*/

void					largeur(t_buffin *all, t_flags *flags);
void					largeur2(t_buffin *all, t_flags *flags);
int						ft_sizeofres_diese(t_flags *flags);

/*
** precision.c
*/

void					precisint(t_buffin *all, t_flags *flags);
void					largint(t_buffin *all, t_flags *flags, int size);

/*
** convdec.c
*/

void					ft_sidec(t_buffin *all, t_flags *flags);
void					ft_un_dec(t_buffin *all, t_flags *flags);
void					nbr_to_char(t_flags *flags, long long a);

/*
** conv_base.c
*/

void					ft_conv_base(t_buffin *all, t_flags *flags);
void					ft_conv_base2(t_buffin *all, t_flags *flags,
						unsigned long long a);
void					ft_diese(t_buffin *all, t_flags *flags);

/*
** double.c
*/

void					quick_check(t_flags *flags);
void					ft_double(t_buffin *all, t_flags *flags);
void					largeur2_float(t_buffin *all, t_flags *flags,
						long double a, int size);
int						ft_sizeofres(char *str);
int						get_size2(t_flags *flags);

/*
**	precision_base.c
*/

void					precibase(t_buffin *all, t_flags *flags);
void					ft_change_base2(t_buffin *all, t_flags *flags,
						char **base);

/*
** double_to_char.c
*/

void					double_to_char(t_buffin *all, t_flags *flags,
						double long a);
long long				ft_intpart_double(long double a);

/*
** largeur_float.c
*/

void					ft_largeur_float(t_buffin *all, t_flags *flags,
						long double a);

/*
** precision_double.c
*/

void					ft_decimal_float(t_buffin *all, t_flags *flags,
						long double a);

/*
**	bonus.c
*/

void					ft_tab_int(t_buffin *all, t_flags *flags);
void					ft_tab_str(t_buffin *all, t_flags *flags);
void					nbr_to_char_extreme(t_flags *flags, long long a);

#endif
