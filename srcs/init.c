/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:14:25 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/06 11:46:45 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ls_init_flags(t_infos *flags, int i)
{
	if (i == 0)
		i++;
	flags->flags = 0;
	flags->nbr_error = 0;
	if (!(flags->path = (char **)malloc(sizeof(char *) * (i + 1))))
	{
		free(flags);
		return (-1);
	}
	if (!(flags->error = (char **)malloc(sizeof(char *) * i)))
	{
		free(flags);
		free(flags->path);
		return (-1);
	}
	return (0);
}

void			ls_free_flags(t_infos *flags, int i)
{
	int a;

	a = -1;
	i++;
	while (flags->path[++a])
		free(flags->path[a]);
	free(flags->error);
	free(flags->path);
	free(flags);
}
