/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:07:37 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/24 14:07:57 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *begin_list)
{
	int size;

	size = 0;
	if (begin_list)
	{
		while (begin_list)
		{
			size++;
			begin_list = begin_list->next;
		}
	}
	return (size);
}
