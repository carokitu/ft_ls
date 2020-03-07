/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:25:59 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/25 13:46:12 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		len;
	int		i;
	int		a;
	char	*cpy;

	a = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) - 1;
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
		len--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		len--;
	}
	if (len + 1 <= 0)
		len = 0;
	if (!(cpy = (char *)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	while (a < len + 1)
		cpy[a++] = s[i++];
	cpy[a] = '\0';
	return (cpy);
}
