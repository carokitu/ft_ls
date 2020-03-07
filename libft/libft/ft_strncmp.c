/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:26:13 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/15 15:05:34 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		a;

	a = 0;
	while ((s1[a] == s2[a]) && s1[a] && (a < n - 1))
		a++;
	if (((s2[a] == '\0') && (s1[a] == '\0')) || (n == 0))
		return (0);
	else
		return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}
