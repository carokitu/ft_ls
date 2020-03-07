/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:46:40 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/15 12:35:15 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] == '\t') || (str[i] == '\v') || (str[i] == '\n')\
	|| (str[i] == '\r') || (str[i] == '\f') || (str[i] == ' '))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	res = res * sign;
	return (res);
}
