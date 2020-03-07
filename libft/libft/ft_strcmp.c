/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:07:56 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/15 11:48:46 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int		a;

	a = 0;
	while ((s1[a] == s2[a]) && s1[a])
		a++;
	if ((s2[a] == '\0') && (s1[a] == '\0'))
		return (0);
	else
		return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}
