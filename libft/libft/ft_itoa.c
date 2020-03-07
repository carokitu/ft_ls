/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 10:18:43 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/22 13:21:07 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
		n = n * -1;
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char		*ft_else(int sign, int n)
{
	int		len;
	char	*nbr;

	len = ft_len(n);
	if (!(nbr = (char *)malloc(sizeof(char) * (len + sign))))
		return (NULL);
	if (sign != 1)
		nbr[0] = '-';
	nbr[len + sign - 1] = '\0';
	len--;
	while (len + sign - 1 >= 0 && n > 0)
	{
		nbr[len + sign - 1] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (nbr);
}

char			*ft_itoa(int n)
{
	char	*nbr;
	int		len;
	int		i;
	int		sign;
	int		a;

	a = 0;
	sign = 1;
	i = 0;
	len = ft_len(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return ("0");
	if (n < 0)
	{
		sign = 2;
		n = n * -1;
	}
	nbr = ft_else(sign, n);
	return (nbr);
}
