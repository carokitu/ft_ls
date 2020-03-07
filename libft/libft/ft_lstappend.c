/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:06:43 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/24 14:07:08 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list *list, t_list *new)
{
	t_list	*app;

	if (list && new)
	{
		app = list;
		while (app->next != NULL)
			app = app->next;
		app->next = new;
		new->next = NULL;
	}
}
