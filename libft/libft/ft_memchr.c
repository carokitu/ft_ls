/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 09:39:25 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/14 18:45:21 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*src;

	src = (unsigned char *)s;
	while (n)
	{
		if (*src == (unsigned char)c)
			return (src);
		n--;
		src++;
	}
	return (NULL);
}
