/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:55:59 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/24 18:59:25 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	count;
	char			*s1;

	if (dst == NULL && src == NULL)
		return (NULL);
	count = 0;
	s1 = (char *)dst;
	while (count < n)
	{
		s1[count] = *(char *)src;
		count++;
		src++;
	}
	return (dst);
}
