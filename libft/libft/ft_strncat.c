/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:22:40 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/24 19:00:28 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	int		i;
	size_t	a;

	i = 0;
	a = 0;
	while (dst[i])
		i++;
	while (src[a] && (a < len))
	{
		dst[i] = src[a];
		a++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
