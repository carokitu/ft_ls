/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:18:09 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/15 16:09:38 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*str;

	if (size == 0)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	while (size--)
		str[size] = 0;
	return ((void *)str);
}
