/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:35:39 by cde-moul          #+#    #+#             */
/*   Updated: 2018/11/23 17:05:11 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*first;
	t_list	*tmp;

	tmp = f(lst);
	if (!(res = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	first = res;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		if (!(res->next = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		res = res->next;
		lst = lst->next;
	}
	return (first);
}
