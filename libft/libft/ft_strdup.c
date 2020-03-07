/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:44:35 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/25 13:56:21 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		t;

	t = 0;
	while (s1[t])
		t++;
	if (!(str = ((char *)malloc(sizeof(char) * (t + 1)))))
		return (NULL);
	t = 0;
	while (s1[t])
	{
		str[t] = s1[t];
		t++;
	}
	str[t] = '\0';
	return (str);
}
