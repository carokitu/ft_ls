/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:14:32 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/24 18:15:42 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbr_w(char const *s, char c)
{
	int i;
	int res;

	res = 0;
	i = 0;
	if (!s[i])
		return (0);
	if (s[i] != c)
	{
		res++;
		while (s[i] != c && s[i])
			i++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			res++;
		i++;
	}
	return (res);
}

static int		ft_nbr_let(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static char		**ft_full(char **rep, char const *s, char c)
{
	int		i;
	int		a;
	int		b;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c)
		{
			b = 0;
			a = ft_nbr_let(s, c);
			if (!(rep[i] = (char *)malloc(sizeof(char) * (a + 1))))
				return (NULL);
			while (a-- != 0)
				rep[i][b++] = *s++;
			rep[i][b] = '\0';
			i++;
		}
	}
	return (rep);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**rep;
	int		d;

	if (s == NULL)
		return (NULL);
	d = ft_nbr_w(s, c);
	if (!(rep = (char **)malloc(sizeof(char *) * (d + 1))))
		return (NULL);
	rep = ft_full(rep, s, c);
	rep[d] = NULL;
	return (rep);
}
