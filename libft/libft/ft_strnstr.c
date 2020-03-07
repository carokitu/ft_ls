/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:46:09 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/23 17:23:13 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	int		a;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && (i < n))
	{
		a = 0;
		if ((haystack[i] == needle[a]) && (i + a < n))
		{
			while ((haystack[i + a] == needle[a]) && (i + a < n))
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
