/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 13:46:26 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/24 14:08:58 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_convert_base(long long int nbr, char *base, int taillebase)
{
	if (nbr >= 0 && nbr < taillebase)
		ft_putchar(base[nbr]);
	else if (nbr < 0)
	{
		ft_putchar('-');
		ft_convert_base(nbr * (-1), base, taillebase);
	}
	else
	{
		ft_convert_base(nbr / taillebase, base, taillebase);
		ft_convert_base(nbr % taillebase, base, taillebase);
	}
}

void			ft_putnbr_base(int nbr, char *base)
{
	int i;
	int j;
	int taillebase;

	i = 0;
	taillebase = 0;
	while (base[i] && base[i] != '-' && base[i] != '+' && base[i] >= 32)
	{
		j = i - 1;
		while (base[i] != base[j] && j >= 0)
			j--;
		if (j == -1)
			i++;
		else
			break ;
	}
	if (!base[i])
		taillebase = i;
	if (taillebase > 1)
		ft_convert_base(nbr, base, taillebase);
}
