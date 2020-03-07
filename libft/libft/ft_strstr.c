/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:56:41 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/15 13:29:43 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		a;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		a = 0;
		if (haystack[i] == needle[a])
		{
			while (haystack[i + a] == needle[a])
			{
				a++;
				if (!(needle[a]))
					return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}
