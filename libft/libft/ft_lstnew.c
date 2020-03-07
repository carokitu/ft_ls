/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:20:54 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/24 18:40:07 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;
	const void	*contenu;
	size_t		taille;

	if (!(new = malloc(sizeof(t_list))))
		return (0);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		taille = content_size;
		contenu = content;
		if (!(new->content = ft_memalloc(taille)))
		{
			free(new);
			return (NULL);
		}
		new->content = ft_memcpy(new->content, contenu, taille);
		new->content_size = taille;
	}
	new->next = NULL;
	return (new);
}
