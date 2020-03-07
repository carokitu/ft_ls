/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:42:32 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/14 18:08:45 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tab;

	tab = (unsigned char *)b;
	while (len)
	{
		*tab = (unsigned char)c;
		len--;
		tab++;
	}
	return (b);
}
