/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:45:59 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/24 18:34:36 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	lettre;
	char			*tour;
	int				i;
	int				a;

	i = 0;
	a = -1;
	tour = (char *)s;
	lettre = (char)c;
	while (tour[i] != '\0')
	{
		if (tour[i] == lettre)
			a = i;
		s++;
		i++;
	}
	if (c == 0)
		a = i;
	if (a == -1)
		tour = NULL;
	else
		return (tour + a);
	return (tour);
}
